#!/bin/bash

ESC="\e["
COLOR_OFF=$ESC"0m"
COLOR_RED=$ESC"31m"
COLOR_GRN=$ESC"32;1m"
COLOR_YLW=$ESC"33;1m"
COLOR_MGN=$ESC"35;1m"
COLOR_CYN=$ESC"36;1m"

function ee () {
  echo -e "$@";
}

read -rd '' SKELE_MAKE << 'EOF'
FILENAME := $(shell basename `pwd`)

DEBUG_OPTS := -Wall -Wextra -Wfloat-equal -Wundef -Werror -fverbose-asm -Wint-to-pointer-cast -Wshadow -Wpointer-arith -Wcast-align -Wstrict-prototypes -Wcast-qual -Wmissing-prototypes -Wstrict-overflow=5 -Wwrite-strings -Wconversion --pedantic-errors -std=gnu11 -ggdb

MEM_OPTS := -fstack-protector -fsanitize=address -fsanitize=undefined -fno-omit-frame-pointer

OPTS := -std=gnu11 -lm

FILES := $(FILENAME).c $(FILENAME).h

all: normal debug mem

normal: $(FILES)
	clang $(OPTS) -o $(FILENAME) $(FILENAME).c
	@echo

debug: $(FILES)
	clang $(DEBUG_OPTS) $(OPTS) -o debug_$(FILENAME) $(FILENAME).c
	@echo

mem: $(FILES)
	clang $(MEM_OPTS) $(DEBUG_OPTS) $(OPTS) -o memdebug_$(FILENAME) $(FILENAME).c
	@echo

clean:
	(rm $(FILENAME) debug_$(FILENAME) memdebug_$(FILENAME) core; echo)
	@echo

EOF

DIRS=$(find . -regextype sed -type d -iregex '\./[^\.].*' -exec echo {} +)

function build_all () {
  # get all the args
  targets="$*"
  # if there are none, set some defaults
  if [[ "$targets" == "" ]]; then
    targets=(clean all)
  fi

  ee "$COLOR_CYN\btargets: $COLOR_YLW${targets[*]} $COLOR_OFF"

  for dir in $DIRS; do

    ee "$COLOR_CYN\nMaking $dir...$COLOR_OFF\n"

    cd "$dir" || ( ee "$COLOR_RED\nFatally failed $dir...$COLOR_OFF\n"; exit )

    echo "$SKELE_MAKE" > Makefile

    for arg in ${targets[*]}; do
      ee "$COLOR_CYN\nMaking $COLOR_YLW$arg$COLOR_CYN in $dir...$COLOR_OFF\n\n"

      ee "$COLOR_MGN"
      make "$arg"
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

build_all "$@"