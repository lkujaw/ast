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
 * AT&T Bell Laboratories
 *
 * generate ast traps for botched standard prototypes
 */

#include <sys/types.h>

#include "FEATURE/lib"
#include "FEATURE/sys"

#if _lib_getgroups
extern int		getgroups(int, gid_t*);
#endif

int
main()
{
#if _lib_getgroups
	if (sizeof(int) > sizeof(gid_t))
	{
		int	n;
		int	i;
		int	r;
		gid_t	groups[32 * sizeof(int) / sizeof(gid_t)];

		r = sizeof(int) / sizeof(gid_t);
		if ((n = getgroups((sizeof(groups) / sizeof(groups[0])) / r, groups)) > 0)
			for (i = 1; i <= n; i++)
			{
				groups[i] = ((gid_t)0);
				if (getgroups(i, groups) != i)
					goto botched;
				if (groups[i] != ((gid_t)0))
					goto botched;
				groups[i] = ((gid_t)-1);
				if (getgroups(i, groups) != i)
					goto botched;
				if (groups[i] != ((gid_t)-1))
					goto botched;
			}
	}
	return 0;
 botched:
	printf("#undef	getgroups\n");
	printf("#define getgroups	_ast_getgroups /* implementation botches gid_t* arg */\n");
#endif
	return 0;
}
