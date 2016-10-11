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
