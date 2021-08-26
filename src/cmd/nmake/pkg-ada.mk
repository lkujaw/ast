/*
 * GNAT Ada package for AT&T NMAKE.
 *
 * Use this package by writing 'include pkg-ada.mk' within the Makefile.
 *
 * Copyright (c) 2021, Lev Kujawski.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software")
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */

.PACKAGE.ada.dontcare := 1

ADA = gcc
ADABIND = gnatbind
ADALS = gnatls
ADALIBRARIES = -lgnat

freeze ADA

(ADAFLAGS) (ADAFLAGS.LINT) : .PARAMETER

.SUFFIX.ada = .adb
.SUFFIX.HEADER.ada = .ads
.SUFFIX.ada.m4 = .amb .ams

/* Make ADAKRUNCH an environmental variable. */
.EXPORT : ADAKRUNCH

/* Add the current directory to search path. */
.SOURCE.adb .SOURCE.ads : .INSERT .
.SOURCE.ali : $$(*.SOURCE.a)

.DEDUPLICATE :FUNCTION:
	return $(%:I=$(%))

.ADA.PATHS :FUNCTION:
	return $("$(*.SOURCE.adb) $(*.SOURCE.ads) $(*.SOURCE)":P=C:H>U:/^/-I/)

.SCAN.ada : .SCAN
	X|gnatscan "$$(%)" "$$(.ADA.PATHS)"
	F|M$$(?:N=*.ads:T=F)|

$("$(.SUFFIX.ada) $(.SUFFIX.HEADER.ada)":/^/.ATTRIBUTE.%/) : .SCAN.ada
$(.SUFFIX.ada.m4:/^/.ATTRIBUTE.%) : .SCAN.m4

.SOURCE.%.SCAN.ada : .FORCE $$(*.SOURCE.adb) $$(*.SOURCE.ads) $$(*.SOURCE)

.PROBE.INIT : .PKG.ADA.INIT

.PKG.ADA.INIT : .MAKE .VIRTUAL .FORCE .AFTER
	/* Detect whether GNAT is present. */
	if ! "$(PATH:/:/ /G:X=$(ADABIND):P=X)"
		error 3 $(ADABIND): Ada compiler not found -- required to build $(.RWD.:-$(PWD:B))
	end
	/* Add the GNAT library path to the search list. */
	.SOURCE.a : $(GNATPATH)
	/* Depend on the binder-generated 'main' for Ada commands. */
	.APPEND.%.COMMAND : $$(!:A=.SCAN.ada:@?b~$$(<).o??)

GNATPATH :COMMAND: (ADALS)
	$(ADALS) -v|grep adalib|sed -e 's:^ *::'
/* This instructs NMAKE to add a runpath for the GNAT library. */
LDRUNPATH=.

/* Note that this function affects the global scope (incl. C). */
.ADA.INIT : .MAKE .VIRTUAL .FORCE .IGNORE
	LDLIBRARIES += $$(!:A=.SCAN.ada:@?$$(ADALIBRARIES)??)

.GNAT.KRUNCH :FUNCTION: (ADAKRUNCH)
	if "$(ADAKRUNCH)" != ""
		return "-gnatk"$(ADAKRUNCH)
	else
		return $(ADAKRUNCH)
	end

ADAFLAGS += $$(.INCLUDE. ada -I)

for .S. in $(.SUFFIX.ada) $(.SUFFIX.HEADER.ada)
	%.o %.ali : %$(.S.) (ADA) (.GNAT.KRUNCH) (ADAFLAGS) (ADAFLAGS.LINT) .ADA.INIT
		$(ADA) -x ada $(.GNAT.KRUNCH) $(ADAFLAGS) $(ADAFLAGS.LINT) -c $(>)
end

/* Listing "" first forestalls infinite recursion within this metarule. */
b~%.adb b~%.ads : "" %.ali $$(!%.ali:B:S=.ali:T!=F) (ADABIND)
	$(ADABIND) -x $("$(.DEDUPLICATE $(!$(%).ali:B:S=.ali:T=F:D:H>U) $(*.SOURCE.a))":/^/-I/) $(*:N=$(%).ali)

b~%.o b~%.ali : b~%.adb (ADA) (ADAFLAGS)
	$(ADA) -x ada $(ADAFLAGS) -c $(>)

for .S. in b s
	%.ad$(.S.) : %.am$(.S.) (M4) (M4FLAGS)
		$(M4) $(M4FLAGS) $(!:N=*.m4) $(>) > $(<)
end

":ADA_LIBRARY:" : .MAKE .OPERATOR
	local libraryName libraryVersion aliDirectory
	libraryName    := $(<:O=1)
	libraryVersion := $(<:O=2)
	aliDirectory   := "$$(LIBDIR)/$$(CC.PREFIX.SHARED)$(libraryName)/"
	/* Delegate library installation to :LIBRARY:. */
	$(libraryName) $(libraryVersion) :LIBRARY: $(>)
	/*
	 * Install GNAT Ada Library Information (ALI) files.
	 *
	 * These must be installed read-only to prevent GNAT from attempting
	 * to update them.
	 */
	$(aliDirectory) :INSTALLDIR: $(>:N=*.ad[bs]:B:S=.ali) mode=a-wx
