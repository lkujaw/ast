/***********************************************************************
*                                                                      *
*               This software is part of the ast package               *
*          Copyright (c) 1990-2011 AT&T Intellectual Property          *
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
*               Glenn Fowler <glenn.s.fowler@gmail.com>                *
*                                                                      *
***********************************************************************/
#pragma prototyped
/*
 * Glenn Fowler
 * AT&T Research
 *
 * coshell procrun(3)
 */

#include "colib.h"

#include <proc.h>

int
coprocrun(const char* path, char** argv, int flags)
{
	register char*		s;
	register char**		a;
	register Sfio_t*	tmp;
	int			n;

	if (!(a = argv))
		return procclose(procopen(path, a, NiL, NiL, PROC_FOREGROUND|PROC_GID|PROC_UID|flags));
	if (!(tmp = sfstropen()))
		return -1;
	sfputr(tmp, path ? path : "sh", -1);
	while (s = *++a)
	{
		sfputr(tmp, " '", -1);
		coquote(tmp, s, 0);
		sfputc(tmp, '\'');
	}
	if (!(s = costash(tmp)))
		return -1;
	n = cosystem(s);
	sfstrclose(tmp);
	return n;
}
