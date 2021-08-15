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
 * Glenn Fowler
 * AT&T Research
 */

#include <ast.h>
#include <hashkey.h>

long
strkey(register const char* s)
{
	register long	x = 0;
	register int	n = 0;
	register int	c;

	while (n++ < HASHKEYMAX)
	{
		c = *s;
		if (c >= 'a' && c <= 'z')
			x = HASHKEYPART(x, c);
		else if (c >= '0' && c <= '9')
			x = HASHKEYPART(x, HASHKEYN(c));
		else break;
		s++;
	}
	return x;
}
