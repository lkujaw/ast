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
#if defined(_UWIN) && defined(_BLD_ast)

void _STUB_vmstrdup(){}

#else

#include "vmhdr.h"

/*
 * return a copy of s using vmalloc
 */

#if __STD_C
char* vmstrdup(Vmalloc_t* v, register const char* s)
#else
char* vmstrdup(v, s)
Vmalloc_t*	v;
register char*	s;
#endif
{
	register char*	t;
	register size_t	n;

	return (s && (t = vmalloc(v, n = strlen(s) + 1))) ? (char*)memcpy(t, s, n) : (char*)0;
}

#endif
