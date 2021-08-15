/***********************************************************************
*                                                                      *
*               This software is part of the ast package               *
*          Copyright (c) 1985-2011 AT&T Intellectual Property          *
*                      and is licensed under the                       *
*                 Eclipse Public License, Version 2.0                  *
*                    by AT&T Intellectual Property                     *
*                                                                      *
*                A copy of the License is available at                 *
*      https://www.eclipse.org/org/documents/epl-2.0/EPL-2.0.html      *
*         (with md5 checksum 84283fa8859daf213bdda5a9f8d1be1d)         *
*                                                                      *
*              Information and Software Systems Research               *
*                            AT&T Research                             *
*                           Florham Park NJ                            *
*                                                                      *
*                 Glenn Fowler <gsf@research.att.com>                  *
*                  David Korn <dgk@research.att.com>                   *
*                   Phong Vo <kpv@research.att.com>                    *
*                                                                      *
***********************************************************************/
#pragma prototyped
/*
 * <debug.h> support
 */

#include <ast.h>
#include <error.h>
#include <debug.h>

void
debug_fatal(const char* file, int line)
{
	error(2, "%s:%d: debug error", file, line);
	abort();
}

#if _sys_times

#include <times.h>
#include <sys/resource.h>

double
debug_elapsed(int set)
{	
	double		tm;
	struct rusage	ru;

	static double	prev;

	getrusage(RUSAGE_SELF, &ru);
	tm = (double)ru.ru_utime.tv_sec  + (double)ru.ru_utime.tv_usec/1000000.0;
	if (set)
		return prev = tm;
	return tm - prev;
}

#else

double
debug_elapsed(int set)
{
	return 0;
}

#endif
