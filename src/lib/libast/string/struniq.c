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
 * struniq - uniq a sorted argv
 * 0 sentinel is neither expected nor restored
 *
 * Glenn Fowler
 * David Korn
 * AT&T Research
 */

#include <ast.h>

int
struniq(char** argv, int n)
{
	register char**	ao;
	register char**	an;
	register char**	ae;

	ao = an = argv;
	ae = ao + n;
	while (++an < ae)
	{
		while (streq(*ao, *an))
			if (++an >= ae)
				return ao - argv + 1;
		*++ao = *an;
	}
	return ao - argv + 1;
}
