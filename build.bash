#!/bin/bash

ESC="\e["
COLOR_OFF=$ESC"0m"
COLOR_RED=$ESC"31m"
COLOR_GRN=$ESC"32;1m"
COLOR_YLW=$ESC"33;1m"
COLOR_MGN=$ESC"35;1m"
COLOR_CYN=$ESC"36;1m"

ASAN_OPTIONS=symbolize=1
ASAN_SYMBOLIZER_PATH=$(which llvm-symbolizer)
export ASAN_SYMBOLIZER_PATH
export ASAN_OPTIONS


function ee () { echo -e "$@"; }

# if you think this makefile is scary, wait til you see a real project's
read -rd '' SKELE_MAKE << 'EOF'

FILENAME := $(shell basename `pwd`)
ARCH := $(shell uname -m)
OUT_FILENAME := $(FILENAME)

DEBUG_OPTS := -Wall -Wextra -Wfloat-equal -Wundef -Werror -fverbose-asm -Wint-to-pointer-cast -Wshadow -Wpointer-arith -Wcast-align -Wstrict-prototypes -Wcast-qual -Wmissing-prototypes -Wunreachable-code -Wstrict-overflow=5 -Wwrite-strings -Wconversion --pedantic-errors -std=gnu11 -ggdb -Wredundant-decls

MEM_OPTS := -fstack-protector -fsanitize=address -fsanitize=undefined -fno-omit-frame-pointer

OPTS := ../fnv-hash/libfnv.a -std=gnu11 -lm

ifeq ($(CC), gcc)
  DEBUG_OPTS += -Wsuggest-attribute=pure -Wsuggest-attribute=const -Wsuggest-attribute=noreturn
  MEM_OPTS += -static-libasan -static-libtsan -static-liblsan -static-libubsan -lasan -lubsan
endif
ifeq ($(CC), cc)
  DEBUG_OPTS += -Wsuggest-attribute=pure -Wsuggest-attribute=const -Wsuggest-attribute=noreturn
  MEM_OPTS += -static-libasan -static-libtsan -static-liblsan -static-libubsan -lasan -lubsan
endif

CMD_ARGS ?=

FILES := $(FILENAME).c $(FILENAME).h

OPTIONAL = $(if $(wildcard test_$(FILENAME).c), test, )

all: normal debug mem $(OPTIONAL)

spec: arm optifine

normal: $(FILES)
	$(CC) $(FILENAME).c $(CMD_ARGS) $(OPTS) -o ./bin/$(OUT_FILENAME)
	@echo

debug: $(FILES)
	$(CC) $(FILENAME).c $(CMD_ARGS) $(DEBUG_OPTS) $(OPTS) -o ./bin/debug_$(OUT_FILENAME)
	@echo

optifine: $(FILES)
	$(CC) $(FILENAME).c $(CMD_ARGS) $(DEBUG_OPTS) $(OPTS) -o ./bin/optifine_$(OUT_FILENAME) -O3
	@echo

mem: $(FILES)
	$(CC) $(FILENAME).c $(CMD_ARGS) $(MEM_OPTS) $(DEBUG_OPTS) $(OPTS) -o ./bin/memdebug_$(OUT_FILENAME)
	@echo

test: test_$(FILENAME).c
	$(CC) test_$(FILENAME).c $(CMD_ARGS) $(OPTS) -o ./bin/test_$(OUT_FILENAME) -lcriterion
	@echo

arm: $(FILES)
	arm-linux-gnueabi-gcc $(CMD_ARGS) -DARM -static -march=armv7-a $(FILENAME).c -lm -o ./bin/$(FILENAME)_armo -O3
	@echo

clean:
	(rm core *core* a.out 2>/dev/null; echo)
	$(shell find . -type f -executable -regextype sed -iregex '\./[^.]*' | xargs rm)
	@echo

EOF

DIRS=$(find . -maxdepth 1 -regextype sed -type d -iregex '\./[^\.].*' -exec echo {} +)

function build_targets () {

  targets="$1"
  # if there are none, set some defaults
  if [[ "$targets" == "" ]]; then
    targets=( clean all )
  fi

  # just so it can be quoted below
  make_args="$2"
  if [[ "$make_args" == "" ]]; then
    make_args=( NOOP=0 )
  fi

  ee "$COLOR_CYN\btargets: $COLOR_YLW${targets[*]} $COLOR_OFF"

  for dir in $DIRS; do

    if [[ "$dir" = "./old" ]] ; then continue ; fi

    ee "$COLOR_CYN\nMaking $dir...$COLOR_OFF\n"

    pushd "$dir" # || ( ee "$COLOR_RED\nFatally failed $dir...$COLOR_OFF\n"; exit )

    if [[ "$dir" = "./fnv-hash" ]] ; then
      make -j8
      popd
      continue
    fi

    echo "$SKELE_MAKE" > Makefile

    for tgt in ${targets[*]}; do
      ee "$COLOR_CYN\nMaking $COLOR_YLW$tgt$COLOR_CYN in $dir...$COLOR_OFF\n\n"

      ee "$COLOR_MGN"
      make -j8 ${make_args[*]} "$tgt"
      OK=$?
      ee "$COLOR_OFF"

      if [[ $OK == 0 ]]; then
        ee "$COLOR_GRN\nSuccessfully made $COLOR_YLW$tgt$COLOR_GRN in $dir.$COLOR_OFF\n"
      else
        ee "$COLOR_RED\nFailed to make $COLOR_YLW$tgt$COLOR_RED in $dir.$COLOR_OFF\n"
        sleep 1
      fi
    done

    popd

  done
}

ARGS=$(python3 -c "
x = '$*'
y = x.split('--')
for i in y: print(i.strip())
")


TARGETS=$(echo "$ARGS" | head -1)
TARGETS_ARR=($TARGETS)

MAKE_ARGS=$(echo "$ARGS" | tail -1)
MAKE_ARGS_ARR=($MAKE_ARGS)

build_targets "${TARGETS_ARR[*]}" "${MAKE_ARGS_ARR[*]}"
