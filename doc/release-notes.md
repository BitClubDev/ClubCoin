1.2.0 Change Log
========================

C++11
------------------------

Various changes have been made to bring the codebase up to C++11.
This means that you will need a compiler with C++11 support, namely
GCC 4.7 or higher, or Clang 3.3 or higher.

When cross-compiling for a target that doesn't have C++11 libraries, configure with
`./configure --enable-glibc-back-compat ... LDFLAGS=-static-libstdc++`.
