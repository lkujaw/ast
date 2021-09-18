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
ADAFLAGS =
ADAFLAGS.LINT =
ADABIND = gnatbind
ADALS = gnatls
ADALIBRARIES = -lgnat

(ADA) (ADAFLAGS) (ADAFLAGS.LINT) (ADABIND) (ADALS) \
	(ADALIBRARIES) : .PARAMETER

.SUFFIX.ada = .adb
.SUFFIX.HEADER.ada = .ads
.SUFFIX.ada.m4 = .amb .ams

/* Make ADAKRUNCH an environmental variable. */
.EXPORT : ADAKRUNCH

/* Add the current directory to the search path. */
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

.GNAT.KRUNCH :FUNCTION: (ADAKRUNCH)
	if "$(ADAKRUNCH)" == ""
		return $(ADAKRUNCH)
	else
		return "-gnatk$(ADAKRUNCH)"
	end

.PROBE.INIT : .PKG.ADA.INIT

.PKG.ADA.INIT : .MAKE .VIRTUAL .FORCE .AFTER
	# Detect whether the GNAT compiler is present.
	if ! "$(PATH:/:/ /G:X=$(ADABIND):P=X)"
		error 3 $(ADABIND): Ada compiler not found -- required to build $(.RWD.:-$(PWD:B))
	end
	# Add the GNAT library path to the search list.
	.SOURCE.a : $(GNATPATH)
	# Depend on the binder-generated 'main' for Ada commands.
	.INSERT.%.COMMAND : $$(!:A=.SCAN.ada:@?b~.o??)
	# It is necessary to filter for the .SCAN.ada attribute as the
	#  modification of LDLIBRARIES affects the global scope (incl. C).
	LDLIBRARIES += $$(!:A=.SCAN.ada:@?$$(ADALIBRARIES)??)
	# '&=' adds a hidden component (i.e., non-state) to ADAFLAGS.
	ADAFLAGS &= $$(.INCLUDE. ada -I)

b~.o : .MAKE .VIRTUAL .REPEAT .FORCE .IGNORE
	local B
	B = $(<<:B)
	b~$(B).adb b~$(B).ads : .JOINT .SCAN.IGNORE $(B).ali (ADABIND)
		$(ADABIND) $(.INCLUDE. ada -I) $(>)
	b~$(B).o b~$(B).ali : .JOINT b~$(B).adb (ADA) (ADAFLAGS) (.GNAT.KRUNCH)
		$(ADA) -x ada $(.GNAT.KRUNCH) $(ADAFLAGS) -c $(>)
	$(B) : b~$(B).o

GNATPATH :COMMAND: (ADALS)
	$(SILENT) $(ADALS) -v|$(GREP) adalib|$(SED) -e 's:^ *::'
/* This instructs NMAKE to add a runpath for the GNAT library. */
LDRUNPATH=.

for .S. in $(.SUFFIX.ada) $(.SUFFIX.HEADER.ada)
	%.o %.ali : %$(.S.) (ADA) (ADAFLAGS) (ADAFLAGS.LINT) (.GNAT.KRUNCH)
		$(ADA) -x ada $(.GNAT.KRUNCH) $(ADAFLAGS) $(ADAFLAGS.LINT) -c $(>)
end

for .S. in b s
	%.ad$(.S.) : %.am$(.S.) (M4) (M4FLAGS)
		$(M4) $(M4FLAGS) $(!:N=*.m4) $(>) > $(<)
end

":ADA_LIBRARY:" : .MAKE .OPERATOR .PROBE.INIT
	local libraryName libraryVersion aliDirectory
	libraryName    := $(<:O=1)
	libraryVersion := $(<:O=2)
	aliDirectory   := "$$(LIBDIR)/$$(CC.PREFIX.SHARED)$(libraryName)/"
	# Delegate other library functions to ':LIBRARY:'.
	$(<) :LIBRARY: $(>)
	# Install GNAT Ada Library Information (ALI) files.
	#
	# These must be installed read-only to forestall updates by GNAT.
	$(aliDirectory) :INSTALLDIR: $(>:N=*.ad[bs]:B:S=.ali) mode=a-wx
