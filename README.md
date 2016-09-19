# Exercises in C11

---

## `build.sh` usage

```
usage: build.sh [ <targets> ] [ -- <make-options> ]
  <targets> is any number of targets in the Makefile in build.sh.
    default targets are: all, normal, debug, mem, clean.
    targets are built in the order in which they are specified.

  <make-options> is any number of valid options to make(1).
    for example, CC=gcc compiles using gcc instead of clang.

  if <make-options> is present, it must be proceeded by "--";
  <targets> can be given without "--" if <make-options> is absent.

  if there are no arguments, or the only argument is "--",
  "clean all" will be made in that order.
```

To:

* Remove all binaries and make exercises: `./build.sh`

* Build all the exercises: `./build.sh all`.

* Remove all binaries: `./build.sh clean`

* Make one target in all directories: `./build.sh <target>`


* Remove all binaries and make exercises, giving arguments to make: `./build.sh -- CC=gcc NOOP=0`
* etc...

Read `build.sh` and the Makefile contained within for more information.
