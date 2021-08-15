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
 * ccmapc(c, CC_NATIVE, CC_ASCII) and strncmp
 */

#include <ast.h>
#include <ccode.h>

#if _lib_strnacmp

NoN(strnacmp)

#else

#include <ctype.h>

int
strnacmp(const char* a, const char* b, size_t n)
{
#if CC_NATIVE == CC_ASCII
	return strncmp(a, b, n);
#else
	register unsigned char*	ua = (unsigned char*)a;
	register unsigned char*	ub = (unsigned char*)b;
	register unsigned char*	ue;
	register unsigned char*	m;
	register int		c;
	register int		d;

	m = ccmap(CC_NATIVE, CC_ASCII);
	ue = ua + n;
	while (ua < ue)
	{
		c = m[*ua++];
		if (d = c - m[*ub++])
			return d;
		if (!c)
			return 0;
	}
	return 0;
#endif
}

#endif
