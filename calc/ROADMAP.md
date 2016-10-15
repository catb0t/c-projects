### Endpoint: a self-hosting, bootstrapping compiler.

How:
* the lexer `lex.h` translates text into a walkable AST represented using objects from...
* the object system `object.h`, which is run (walked) by the interpreter in...
* the stack VM `stack.h`.
* the compiler, `compile.h` (TODO), translates an AST created by the lexer into C code compiled and linked against `libmouse.a`.
* using `string_eval()` and its associated operator (TODO), a self-hosting interpreter is possible, which is then compiled into a standalone binary.