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
 * AT&T Bell Laboratories
 * disable preroot and open path relative to the real root
 */

#include <ast.h>
#include <preroot.h>

#if FS_PREROOT

int
realopen(const char* path, int mode, int perm)
{
	char		buf[PATH_MAX + 8];

	if (*path != '/' || !ispreroot(NiL)) return(-1);
	strcopy(strcopy(buf, PR_REAL), path);
	return(open(buf, mode, perm));
}

#else

NoN(realopen)

#endif
