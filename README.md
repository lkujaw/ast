# AST

This is the Advanced Software Technology (AST) toolkit, originally
developed and released as [free software][1] by AT&T Research.  It
includes many tools and libraries, such as KSH, NMAKE, SFIO, VMALLOC,
and VCODEX.  It also includes more efficient replacements for many of
the POSIX tools.  It was designed to be portable across many UNIX and
UNIX-like systems and also works under [UWIN][4] on Microsoft Windows.

## Improvements and New Features

Compared to the official [AT&T repository][3], this repository
features the following improvements and new features:

### AST (General)

- Restored compatibility with classic UNIX systems like UNIXWARE and
  early releases of Solaris.

### NMAKE

- Ada language support, including automatic dependency scanning,
  installation of ALI files, and convenient operators like :ADA_LIBRARY:
  (GNAT-only at this time).
- New functionality to support contemporary releases of Mac OS X,
  including Xcode TBD files, Clang-specific preprocessor features like
  __has_include_next, and properly versioned ($VERSION.dylib) dynamic
  libraries.
- Enhanced build integrity.  In addition to file modification times,
  NMAKE now tracks the file sizes of built objects for determining
  whether a rebuild is necessary.
- Recognizes Makefile.nmk and makefile.nmk as Nmakefiles.  This should
  aid syntax-highlighting editors in selecting the proper Makefile
  dialect and complies with the 8.3 filename convention.

## Licensing

The AT&T source code within this package is licensed under the
[Eclipse Public License][2], [version 2.0][6], without the GPL
compatibility clause.  Please consider [supporting][7] the addition of
said clause.

Newly written source code within this repository is released under the
terms of the MIT-0 license, which is compatible with both the EPL and
the GPL.  As there is no mechanism in place for copyright assignment
for contributions to the AST, the permissiveness of MIT-0 licensing will
hopefully facilitate any future re-licensing by AT&T.

## Platform Support

The following platforms have been recently tested with the AST toolkit.

| Platform                   | Architecture   | Compiler               | Native Toolchain |
|----------------------------|----------------|------------------------|------------------|
| Ubuntu 20.04 LTS           | linux.i386-64  | GNU GCC 9.3.0          | Yes              |
| Red Hat Enterprise Linux 6 | linux.i386     | GNU GCC 4.4.7          | Yes              |
| Apple Mac OS 10.15         | darwin.i386-64 | Xcode 11.7             | Yes              |
| SCO UNIXWARE 7.1.4         | unixware.i386  | UNIXWARE CCS 4.2       | Yes              |
| Sun Microsystems Solaris 8 | sol8.i386      | WorkShop Compilers 5.0 | Yes              |

## Build

This software is used to build itself with NMAKE.  After cloning
this repository, `cd` to the top directory of it and run:

`./bin/package make`

For more information, run:

`./bin/package help`

After the completion of a successful build, binaries and supporting
files may be found within the arch/_platform_ directory.

Many of the packaged commands (including bin/package) self-document
via the --man (for the UNIX manual page) and --html options.

If you were accustomed to the old AST packaging mechanism, on
www.research.att.com, this repository is equivalent to downloading the
INIT and ast-open packages and running `./bin/package read` on them.

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
please consider using the [ksh93 fork][5] maintained by Martijn Dekker
instead.  Unfortunately, I (@lkujaw) cannot devote the time that the
AST (including the Korn Shell) deserves.

## Help Needed

Help in the following areas would be greatly appreciated:

* Porting features and fixes from the AST beta releases made through
  2016.  Some stability issues in these releases were never addressed,
  so caution is warranted.
* Porting applicable fixes made to Martijn Dekker's [ksh93 fork][5].
  Adjustments will likely be necessary due to feature divergence
  (e.g., COSHELL support is continued here for NMAKE).
* Testing on other UNIX and UNIX-like systems, especially the BSDs.
* Adapting AST to work with Microsoft's Services for UNIX, Cygwin, and DJGPP.
  To the best of my knowledge, [UWIN][4] has never supported PC DOS nor has it
  been maintained for quite some time.

[1]: https://www.gnu.org/philosophy/free-sw.en.html
[2]: https://www.eclipse.org/org/documents/epl-2.0/EPL-2.0.html
[3]: https://github.com/att/ast
[4]: https://github.com/att/uwin
[5]: https://github.com/ksh93/ksh
[6]: https://git.sr.ht/~lev/ast/commit/b2a8b30d1c2c9de3465d388f4f410169a3cb4df5
[7]: https://github.com/att/ast/issues/1493
