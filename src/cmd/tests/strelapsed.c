/***********************************************************************
*                                                                      *
*               This software is part of the ast package               *
*          Copyright (c) 1999-2011 AT&T Intellectual Property          *
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
*                                                                      *
***********************************************************************/
#pragma prototyped

/*
 * AT&T Research
 *
 * test harness for strelapsed
 */

#include <ast.h>

int
main(int argc, char** argv)
{
	char*		s;
	char*		e;
	unsigned long	t;
	int		n;

	while (s = *++argv)
	{
		n = (int)strtol(s, &e, 0);
		if (*e)
		{
			sfprintf(sfstderr, "%s: number expected", s);
			break;
		}
		if (!(s = *++argv))
		{
			sfprintf(sfstderr, "elapsed time expression expected");
			break;
		}
		t = strelapsed(s, &e, n);
		sfprintf(sfstdout, "strelapsed   \"%s\" \"%s\" %lu %d\n", s, e, t, n);
	}
	return 0;
}
