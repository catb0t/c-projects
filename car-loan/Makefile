FILENAME := $(shell basename `pwd`)
ARCH := $(shell uname -m)
OUT_FILENAME := $(FILENAME)

DEBUG_OPTS := -Wall -Wextra -Wfloat-equal -Wundef -Werror -fverbose-asm -Wint-to-pointer-cast -Wshadow -Wpointer-arith -Wcast-align -Wstrict-prototypes -Wcast-qual -Wmissing-prototypes -Wstrict-overflow=5 -Wwrite-strings -Wconversion --pedantic-errors -std=gnu11 -ggdb -Wredundant-decls

MEM_OPTS := -fstack-protector -fsanitize=address -fsanitize=undefined -fno-omit-frame-pointer

OPTS := -std=gnu11 -lm

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

normal: $(FILES)
	$(CC) $(FILENAME).c $(CMD_ARGS) $(OPTS) -o $(OUT_FILENAME)
	@echo

debug: $(FILES)
	$(CC) $(FILENAME).c $(CMD_ARGS) $(DEBUG_OPTS) $(OPTS) -o debug_$(OUT_FILENAME)
	@echo

mem: $(FILES)
	$(CC) $(FILENAME).c $(CMD_ARGS) $(MEM_OPTS) $(DEBUG_OPTS) $(OPTS) -o memdebug_$(OUT_FILENAME)
	@echo

test: test_$(FILENAME).c
	$(CC) test_$(FILENAME).c $(CMD_ARGS) $(OPTS) -o test_$(OUT_FILENAME) -lcriterion
	@echo

clean:
	(rm core a.out 2>/dev/null; echo)
	$(shell find . -type f -executable -regextype sed -iregex '\./[^.]*' | xargs rm)
	@echo
