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
