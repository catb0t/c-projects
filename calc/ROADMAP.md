# Mouse

(again)

---

## Endpoint: a self-hosting, bootstrapping compiler.

How:
* the lexer `lex.h` translates text into a walkable AST represented using objects from...
* the object system `object.h`, which is run (walked) by the interpreter in...
* the stack VM `stack.h`.
* the compiler, `compile.h`, translates an AST created by the lexer into C code compiled and linked against `libmouse.a`; see compile/compile.h.
* using `string_eval()` and its associated operator (TODO), a self-hosting interpreter is possible, which is then compiled into a standalone binary.
* make libmouse like:
  
  ```
  cc object/object.h -c -o object.o
  cc lex/lex.h -c -o lex.o
  cc stack/stack.h -c -o stack.o
  ar rv libmouse.a object.o stack.o lex.o
  ```
  
* libmouse.a's location must be given as an arg if it's not in the current directory
* text gets translated into bytecode, which either gets run by the VM or translated into C

## Syntax ideas

* long and short form
* short form is bytecode interpreted by VM

long form:

```
.                    repr
\                    deref
:                    assignment
" "                  string literal
[ ]                  quotation (function) literal
{ }                  array literal
p{ 1 2 }             pair literal
h{ { 1 2 } }         hashtable literal
123.45               a real number
1,234.5              also a real
h{ { 1 2 } } 1 at .  prints value at 1
[ 9 + ] 'f :         defines symbol f as a function adding 9
```

* multiple dispatch of identifiers
