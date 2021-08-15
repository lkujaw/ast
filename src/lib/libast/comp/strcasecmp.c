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

#if _lib_strcasecmp

NoN(strcasecmp)

#else

#include <ctype.h>

#undef	strcasecmp

int
strcasecmp(register const char* a, register const char* b)
{
	register int	ac;
	register int	bc;
	register int	d;

	for (;;)
	{
		ac = *a++;
		if (isupper(ac))
			ac = tolower(ac);
		bc = *b++;
		if (isupper(bc))
			bc = tolower(bc);
		if (d = ac - bc)
			return d;
		if (!ac)
			return 0;
	}
}

#endif
