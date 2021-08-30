# ast nmake panic tests
#
# these tests may throw nmake into a panic
#
# panic messages still to be fixed are listed
# as FIXME: instead of panic: so they show up
# as regression test failures

INCLUDE test.def

TEST 01 'local generated stdio.h'

	EXEC	--silent --nojobs
		INPUT Makefile $'all : t.c stdio.h
stdio.h : stdio
	cp $(*) $(<)
'
		STDIO_H=`echo '#include <stdio.h>' | cpp - | grep '/stdio.h' | cut -d \" -f2 | head -n 1`
		INPUT t.c $'#include "'"${STDIO_H:-/usr/include/stdio.h}"'"'
		INPUT stdio

	EXEC	--silent --nojobs
