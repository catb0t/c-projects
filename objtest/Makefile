FILENAME := $(shell basename `pwd`)
ARCH := $(shell uname -m)
OUT_FILENAME := $(FILENAME)

DEBUG_OPTS := -Wall -Wextra -Wfloat-equal -Winline -Wundef -Werror -fverbose-asm -Wint-to-pointer-cast -Wshadow -Wpointer-arith -Wcast-align  -Wcast-qual -Wunreachable-code -Wstrict-overflow=5 -Wwrite-strings -Wconversion --pedantic-errors -ggdb -Wredundant-decls

MEM_OPTS := -fstack-protector -fsanitize=address -fsanitize=undefined -fno-omit-frame-pointer

OPTS := -lm ../fnv-hash/libfnv.a
ifeq ($(CCPLUS), 1)
	OPTS += -std=c++14
	CC := c++
else
	OPTS += -std=gnu11
	DEBUG_OPTS += -Wstrict-prototypes -Wmissing-prototypes
endif

ifeq ($(CC), g++)
	MEM_OPTS += -static-libasan -static-libtsan -static-liblsan -static-libubsan -lasan -lubsan
endif
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

all: normal mem test

normal: $(FILES)
	$(CC) $(FILENAME).c $(CMD_ARGS) $(OPTS) -o ./bin/$(OUT_FILENAME)
	@echo

mem: $(FILES)
	$(CC) $(FILENAME).c $(CMD_ARGS) $(MEM_OPTS) $(DEBUG_OPTS) $(OPTS) -o ./bin/memdebug_$(OUT_FILENAME)
	@echo

test:
	$(CC) _test_array.c -lcriterion ../fnv-hash/libfnv.a -o bin/test_array
	$(CC) _test_array.c -lcriterion ../fnv-hash/libfnv.a -o bin/test_array
	$(CC) _test_fixwid.c -lcriterion ../fnv-hash/libfnv.a -o bin/test_fixwid
	$(CC) _test_func.c -lcriterion ../fnv-hash/libfnv.a -o bin/test_func
	$(CC) _test_hash.c -lcriterion ../fnv-hash/libfnv.a -o bin/test_hash
	$(CC) _test_object.c -lcriterion ../fnv-hash/libfnv.a -o bin/test_object
	$(CC) _test_pair.c -lcriterion ../fnv-hash/libfnv.a -o bin/test_pair
	$(CC) _test_string.c -lcriterion ../fnv-hash/libfnv.a -o bin/test_string
	@echo

clean:
	(rm core *core* a.out 2>/dev/null; echo)
	$(shell find . -type f -executable -regextype sed -iregex '\./[^.]*' | xargs rm)
	@echo
