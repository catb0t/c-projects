# Exercises in C

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

* Remove all binaries and make release builds using the C++ toolchain: `./build.bash -- CMD_ARGS=-DNODEBUG CCPLUS=1` (you will probably need to `make CC=c++` inside `fnv-hash` first)

* Remove all binaries: `./build.bash clean`

* Make one target in all directories: `./build.bash <target>`

* Remove all binaries and make exercises, giving arguments to make: `./build.bash -- CC=gcc NOOP=0`
* etc...

Read `build.bash` and the Makefile contained within for more information.

---

## Dependencies

* One of:
 * a C11   C   compiler and `libc`   ( >= ISO/IEC C99   ) (Clang, GCC, not MSVC)
 * a C++14 C++ compiler and `libc++` ( >= ISO/IEC C++98 ) (MSVC will suffice)

  to which `cc` or `c++` is symlinked, respectively


* GNU-compatible `make`
* GNU `coreutils` (`rm`, `basename`, `pwd`...)
* a vaguely POSIX conformant shell (`bash`, `sh`, `ksh93`...)
* for `build.bash` to work:
  * GNU Bash
  * Python3


The `mem` target requires GCC or Clang's AddressSanitizer, and if you want line numbers in the output, `/usr/bin/llvm-symbolizer` to be installed and symlinked to `/usr/bin/llvm-symbolizer-3.8`.

On Debian-likes, you may be able to install the needed tools using

```bash
apt-get install build-essential bash coreutils make python3 clang llvm llvm-3.8*
```

or so, or a simliar with your favourite package manager.