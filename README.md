# AST

This is the AT&T Software Technology (AST) toolkit from AT&T Research.
It includes many tools and libraries, such as KSH, NMAKE, SFIO,
VMALLOC, and VCODEX.  It also includes more efficient replacements for
many of the POSIX tools.  It was designed to be portable across many
UNIX and UNIX-like systems and also works under [UWIN on Microsoft
Windows](https://github.com/att/uwin).

## Improvements and New Features

Compared to the [official AT&T repository](https://github.com/att/ast),
this repository features the following improvements and new features:

- NMAKE support for contemporary releases of Mac OS X, including TBD
  files and Clang-specific preprocessor features like __has_include_next.
- Restored support for classic UNIX systems like UNIXWARE and Solaris.
- Ada support for NMAKE (GNAT-only at this time).

## Licensing

The AT&T source code within this package is licensed under the
[Eclipse Public Licence, version 2.0](https://github.com/lkujaw/ast/commit/b2a8b30d1c2c9de3465d388f4f410169a3cb4df5),
without the GPL compatibility clause.
Please consider [supporting](https://github.com/att/ast/issues/1493)
the addition of said clause.

Newly written source code within this repository is released under the
terms of the MIT-0 license, which is compatible with both the EPL and
the GPL.  As there is no mechanism in place for copyright assignment
for contributions to the AST, the permissiveness of MIT-0 licensing will
hopefully facilitate any future re-licensing by AT&T.

## Platform Support

| Platform                   | Architecture   | Compiler               | Native Toolchain |
|----------------------------|----------------|------------------------|------------------|
| Apple Mac OS 10.15         | darwin.i386-64 | Xcode 11.7             | Yes              |
| SCO UNIXWARE 7             | unixware.i386  | UNIXWARE CCS 4.2       | Yes              |
| Sun Microsystems Solaris 8 | sol8.i386      | WorkShop Compilers 5.0 | Yes              |
| Red Hat Enterprise Linux 6 | linux.i386     | GNU GCC 4.4.7          | Yes              |

## Build

This software is used to build itself with NMAKE.  After cloning
this repository, `cd` to the top directory of it and run:

`./bin/package make`

Almost all the tools in this package (including the bin/package script are
self-documenting; run <tool> --man (or --html) for the man page for the tool.

(If you were used to the old AST packaging mechanism, on www.research.att.com,
this repository is equivalent to downloading the INIT and ast-open packages and
running `./bin/package read` on them).

### Mac OS X

If you are using a packaging system like MacPorts, Homebrew, or Fink,
you may need to adjust your path before compiling AST:

`export PATH=/usr/bin:/bin`

if you encounter errors like the following:

    Undefined symbols for architecture x86_64:
      "_iconv", referenced from:
          __ast_iconv_open in libast.a(iconv.o)

This is necessary because NMAKE is otherwise liable to link against
incompatible third-party libraries such as GNU libiconv.

## The Korn Shell (KSH)

If you are only looking for the Korn Shell from the AST toolkit,
please consider using the [ksh93 fork maintained by Martijn
Dekker](https://github.com/ksh93/ksh) instead.  Unfortunately, I
(@lkujaw) cannot devote the time that the AST (including the Korn
Shell) deserves.

## Help Needed

Help in the following areas would be greatly appreciated:

* Porting features and fixes from the AST beta releases made through
  2016.  Some stability issues in these releases were never addressed,
  so caution is warranted.
* Porting applicable fixes made to
  [Martijn Dekker's ksh93 fork](https://github.com/ksh93/ksh).
  Some adjustments will likely be necessary due to feature divergence
  (e.g., COSHELL support is continued here for NMAKE).
* Testing on other UNIX and UNIX-like systems, especially the BSDs.
* Adapting AST to work with Microsoft's Services for UNIX, Cygwin, and DJGPP.
  To the best of my knowledge, UWIN has never supported PC DOS nor has it
  been maintained for quite some time.
