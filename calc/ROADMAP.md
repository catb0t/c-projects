# Mouse

(again)

---

## Endpoint: a self-hosting, bootstrapping compiler.

How:
* the lexer `lex.h` translates text into a walkable AST represented using objects from...
* the object system `object.h`, which is run (walked) by the interpreter in...
* the stack VM `stack.h`.
* the compiler, `compile.h`, translates an AST created by the lexer into C code compiled and linked against `libmouse.a` lke this:

* using `string_eval()` and its associated operator (TODO), a self-hosting interpreter is possible, which is then compiled into a standalone binary.

* make libmouse like:
  ```
  cc object/object.h -c -o object.o
  cc lex/lex.h -c -o lex.o
  cc stack/stack.h -c -o stack.o
  ar rv libmouse.a object.o stack.o lex.o
  ```

* libmouse.a's location must be given as an arg if it's not in the current directory

## Syntax ideas

* long and short form
* whitespace separates tokens in long form but is ignored in short form
  * could uselessly increment an accumulator, like whitespace
* dereference -- pushes a func_t's underlying quot, no-op(?) on other vals

short form:
```
!             repr
?             if
\             dereference
:             assignment of top val to preceding name
" "           string literal
[ ]           quotation (function) literal
{ 1 2 }       array literal (whitespace between indexes)
{ 1 ; 2 }     pair literal (cons cell)
{ { 1 ; 2 } } hashtable literal ( array<pair> )
123.45        the real number 123.45
123           the integer 123
{{1;2}}1@!    prints value at 1
[9+]'f:       symbol f is a function adding 9, use it as f
```

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

* multiple dispatch
