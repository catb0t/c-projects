# if OS was set on the command line, use that
OS ?= $(shell uname)

OPTS := -std=c11 -lm
LIBOPT := $(OPTS) -c -fPIC

RELEASE ?= 0
MEM		 ?= 1

ifeq ($(OS), Windows)
	ARCH	 := x86
	CC		 := i686-w64-mingw32-gcc
	BINEXT := .exe
endif
ARCH ?= $(shell uname -m)

PLTFM_LIBN := $(OS)_$(ARCH)_
O_FILENAME := bin/

ifeq ($(RELEASE), 0)
	DEBUG ?= -Wall -Wextra -Wfloat-equal -Wundef -Werror -fverbose-asm -Wint-to-pointer-cast -Wshadow -Wpointer-arith -Wcast-align -Wstrict-prototypes -Wcast-qual -Wmissing-prototypes -Wunreachable-code -Wstrict-overflow=5 -Wwrite-strings -Wconversion --pedantic-errors -std=gnu11 -ggdb -Wredundant-decls
	O_FILENAME := $(O_FILENAME)dbg
else
	OPTIMISE := -03
	O_FILENAME := $(O_FILENAME)rel
endif

ifeq ($(MEM), 1)
	MEM ?= -fstack-protector -fsanitize=address -fsanitize=undefined -fno-omit-frame-pointer
	O_FILENAME := $(O_FILENAME)mem
endif

O_FILENAME := $(O_FILENAME)_$(PLTFM_LIBN)calc$(BINEXT)

FNV_LIB := $(PLTFM_LIBN)libfnv.a
MSE_LIB := $(PLTFM_LIBN)libmouse.a

CMD_ARGS ?=

all: libmouse
	@echo Making $(FNV_LIB) $(MSE_LIB)
	@echo

libmouse:
	$(MAKE) object lex stack compile
	ar rv libmouse.a object.o lex.o stack.o compile.o

.PHONY: object
object: $@
	$(CC) $(FNV_LIB) $(OPTIMISE) $(CMD_ARGS) $(LIBOPT) $(DEBUG) $@/$@.h -o $@.o

.PHONY: lex
lex: $@
	$(CC) $(FNV_LIB) $(OPTIMISE) $(CMD_ARGS) $(LIBOPT) $(DEBUG) $@/$@.h -o $@.o

.PHONY: stack
stack: $@
	$(CC) $(FNV_LIB) $(OPTIMISE) $(CMD_ARGS) $(LIBOPT) $(DEBUG) $@/$@.h -o $@.o

.PHONY: compile 
compile: $@
	$(CC) $(FNV_LIB) $(OPTIMISE) $(CMD_ARGS) $(LIBOPT) $(DEBUG) $@/$@.h -o $@.o
