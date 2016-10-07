# Exercises in C11

---

## `build.bash` usage

```
usage: build.bash [ <targets> ] [ -- <make-options> ]
  <targets> is any number of targets in the Makefile in build.bash.
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

* **Remove all binaries and make release builds: `./build.bash -- CMD_ARGS=-DNODEBUG`**

* Build all the exercises: `./build.bash all`.

* Remove all binaries: `./build.bash clean`

* Make one target in all directories: `./build.bash <target>`

* Remove all binaries and make exercises, giving arguments to make: `./build.bash -- CC=gcc NOOP=0`
* etc...

Read `build.bash` and the Makefile contained within for more information.

---

## Dependencies

```
GNU(?) + POSIX C11 library
clang / gcc, or supply your GCC-compatible compiler: CC=compiler
make
bash
python3
other gnu coreutils (rm, pwd, basename, head / tail)
```

The `mem` target requires GCC's or clang's AddressSanitizer, and if you want line numbers in the output, `/usr/bin/llvm-symbolizer` to be installed and symlinked to `/usr/bin/llvm-symbolizer-3.8`.
if you don't want to or can't install these, just remove the `mem` target from the Makefile in `build.bash`. You will need these if you want to verify that there are no memory
leaks. Alternatively, you can just run the given `memdebug_*` binaries I build if you are using 64-bit linux.

You may be able to install the needed tools using

```bash
sudo apt-get install build-essential bash coreutils make python3 clang llvm llvm-3.8*
```

or so.