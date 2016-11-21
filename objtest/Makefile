FILENAME := $(shell basename `pwd`)
ARCH := $(shell uname -m)
OUT_FILENAME := $(FILENAME)

DEBUG_OPTS := -Wall -Wextra -Wfloat-equal -Winline -Wundef -Werror -fverbose-asm -Wint-to-pointer-cast -Wshadow -Wpointer-arith -Wcast-align  -Wcast-qual -Wunreachable-code -Wstrict-overflow=5 -Wwrite-strings -Wconversion --pedantic-errors -ggdb -Wredundant-decls


MEM_OPTS := -fstack-protector -fsanitize=address -fsanitize=undefined -fno-omit-frame-pointer

OPTS := -lm ../fnv-hash/libfnv.a -g -fprofile-arcs -ftest-coverage
ifeq ($(CCPLUS), 1)
	OPTS += -std=c++14
	CC := c++
else
	OPTS += -std=gnu11
	DEBUG_OPTS += -Wstrict-prototypes -Wmissing-prototypes
endif

ifeq ($(CC), g++)
	#MEM_OPTS += -static-libasan -static-libtsan -static-liblsan -static-libubsan -lasan -lubsan
endif
ifeq ($(CC), gcc)
  DEBUG_OPTS +=  -Werror=maybe-uninitialized#-Wsuggest-attribute=pure -Wsuggest-attribute=const -Wsuggest-attribute=noreturn
  MEM_OPTS += -static-libasan -static-libtsan -static-liblsan -static-libubsan -lasan -lubsan -Werror=maybe-uninitialized
endif
ifeq ($(CC), cc)
  DEBUG_OPTS +=  -Werror=maybe-uninitialized# -Wsuggest-attribute=pure -Wsuggest-attribute=const -Wsuggest-attribute=noreturn
	MEM_OPTS += -static-libasan -static-libtsan -static-liblsan -static-libubsan -lasan -lubsan  -Werror=maybe-uninitialized
endif

ifeq ($(CC), clang)
	DEBUG_OPTS +=  -Werror=uninitialized -Wno-language-extension-token
endif

CMD_ARGS ?=

FILES := $(FILENAME).c $(FILENAME).h

all: normal mem test

normal: $(FILES)
	./makememtest.sh
	$(CC) $(FILENAME).c $(CMD_ARGS) $(DEBUG_OPTS) $(OPTS) -o ./bin/$(OUT_FILENAME)
	@echo

mem: $(FILES)
	./makememtest.sh
	$(CC) $(FILENAME).c $(CMD_ARGS) $(MEM_OPTS) $(DEBUG_OPTS) $(OPTS) -o ./bin/memdebug_$(OUT_FILENAME)
	@echo

test:
	$(CC) $(CMD_ARGS) $(OPTS) _test_array.c -lcriterion ../fnv-hash/libfnv.a -o bin/test_array
	$(CC) $(CMD_ARGS) $(OPTS) _test_assoc.c -lcriterion ../fnv-hash/libfnv.a -o bin/test_assoc
	$(CC) $(CMD_ARGS) $(OPTS) _test_fixwid.c -lcriterion ../fnv-hash/libfnv.a -o bin/test_fixwid
	$(CC) $(CMD_ARGS) $(OPTS) _test_func.c -lcriterion ../fnv-hash/libfnv.a -o bin/test_func
	$(CC) $(CMD_ARGS) $(OPTS) _test_hash.c -lcriterion ../fnv-hash/libfnv.a -o bin/test_hash
	$(CC) $(CMD_ARGS) $(OPTS) _test_object.c -lcriterion ../fnv-hash/libfnv.a -o bin/test_object
	$(CC) $(CMD_ARGS) $(OPTS) _test_pair.c -lcriterion ../fnv-hash/libfnv.a -o bin/test_pair
	$(CC) $(CMD_ARGS) $(OPTS) _test_string.c -lcriterion ../fnv-hash/libfnv.a -o bin/test_string
	@echo

clean:
	(rm core *core* a.out *.o *.gch 2>/dev/null; echo)
	$(shell find . -type f -executable -regextype sed -iregex '\./[^.]*' | xargs rm)
	@echo
