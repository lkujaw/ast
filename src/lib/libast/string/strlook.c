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

/*
 * return pointer to name in tab with element size siz
 * where the first member of each element is a char*
 *
 * the last name in tab must be 0
 *
 * 0 returned if name not found
 */

void*
strlook(const void* tab, size_t siz, register const char* name)
{
	register char*	t = (char*)tab;
	register char*	s;
	register int	c = *name;

	for (; s = *((char**)t); t += siz)
		if (*s == c && !strcmp(s, name))
			return (void*)t;
	return 0;
}
