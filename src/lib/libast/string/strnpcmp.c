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

#include <ast.h>

/*
 * path prefix strncmp(3) -- longest first!
 */

int
strnpcmp(register const char* a, register const char* b, size_t n)
{
	register const char*	e;

	e = a + n;
	for (;;)
	{
		if (a >= e)
			return 0;
		if (*a != *b)
			break;
		if (!*a++)
			return 0;
		b++;
	}
	if (*a == 0 && *b == '/')
		return 1;
	if (*a == '/' && *b == 0)
		return -1;
	return (a < b) ? -1 : 1;
}
