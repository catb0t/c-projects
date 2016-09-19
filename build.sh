#!/bin/bash

ESC="\e["
COLOR_OFF=$ESC"0m"
COLOR_RED=$ESC"31m"
COLOR_GRN=$ESC"32;1m"
COLOR_YLW=$ESC"33;1m"
COLOR_MGN=$ESC"35;1m"
COLOR_CYN=$ESC"36;1m"

function ee () { echo -e "$@"; }

# if you think this makefile is scary, wait til you see a real project's one
read -rd '' SKELE_MAKE << 'EOF'
CC ?= clang

FILENAME := $(shell basename `pwd`)
ARCH := $(shell uname -m)
OUT_FILENAME := $(FILENAME)_$(ARCH)

DEBUG_OPTS := -Wall -Wextra -Wfloat-equal -Wundef -Werror -fverbose-asm -Wint-to-pointer-cast -Wshadow -Wpointer-arith -Wcast-align -Wstrict-prototypes -Wcast-qual -Wmissing-prototypes -Wstrict-overflow=5 -Wwrite-strings -Wconversion --pedantic-errors -std=gnu11 -ggdb

MEM_OPTS := -fstack-protector -fsanitize=address -fsanitize=undefined -fno-omit-frame-pointer

OPTS := -std=gnu11 -lm

FILES := $(FILENAME).c $(FILENAME).h

all: normal debug mem

normal: $(FILES)
	$(CC) $(OPTS) -o $(FILENAME) $(FILENAME).c
	@echo

debug: $(FILES)
	$(CC) $(DEBUG_OPTS) $(OPTS) -o debug_$(FILENAME) $(FILENAME).c
	@echo

mem: $(FILES)
	$(CC) $(MEM_OPTS) $(DEBUG_OPTS) $(OPTS) -o memdebug_$(FILENAME) $(FILENAME).c
	@echo

clean:
	(rm $(FILENAME) debug_$(FILENAME) memdebug_$(FILENAME) core; echo)
	@echo

EOF

DIRS=$(find . -regextype sed -type d -iregex '\./[^\.].*' -exec echo {} +)

function build_all () {

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

    ee "$COLOR_CYN\nMaking $dir...$COLOR_OFF\n"

    cd "$dir" || ( ee "$COLOR_RED\nFatally failed $dir...$COLOR_OFF\n"; exit )

    echo "$SKELE_MAKE" > Makefile

    for arg in ${targets[*]}; do
      ee "$COLOR_CYN\nMaking $COLOR_YLW$arg$COLOR_CYN in $dir...$COLOR_OFF\n\n"

      ee "$COLOR_MGN"
      make "${make_args[*]}" "$arg"
      OK=$?
      ee "$COLOR_OFF"

      if [[ $OK == 0 ]]; then
        ee "$COLOR_GRN\nSuccessfully made $COLOR_YLW$arg$COLOR_GRN in $dir.$COLOR_OFF\n"
      else
        ee "$COLOR_RED\nFailed to make $COLOR_YLW$arg$COLOR_RED in $dir.$COLOR_OFF\n"
        sleep 1
      fi
    done

    cd ..

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

build_all "${TARGETS_ARR[*]}" "${MAKE_ARGS_ARR[*]}"
