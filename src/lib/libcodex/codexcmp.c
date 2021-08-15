/***********************************************************************
*                                                                      *
*               This software is part of the ast package               *
*          Copyright (c) 2003-2011 AT&T Intellectual Property          *
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
 * codex method name comparison
 * strcmp() semantics
 */

#include <codex.h>

int
codexcmp(register const char* s, register const char* t)
{
	for (;;)
	{
		if (!*s)
		{
			if (!*t || *t == '-' || *t == '+' || *t == '<' || *t == '>' || *t == '|' || *t == '^')
				return 0;
			break;
		}
		if (!*t)
		{
			if (*s == '-' || *s == '+' || *s == '<' || *s == '>' || *s == '|' || *s == '^')
				return 0;
			break;
		}
		if (*s != *t)
			break;
		s++;
		t++;
	}
	return *((unsigned char*)s) - *((unsigned char*)t);
}
