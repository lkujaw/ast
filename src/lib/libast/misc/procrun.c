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
 *
 * procopen() + procclose()
 * no env changes
 * no modifications
 * effective=real
 * parent ignores INT & QUIT
 */

#include "proclib.h"

int
procrun(const char* path, char** argv, int flags)
{
#if __OBSOLETE__ < 20090101
	flags &= argv ? PROC_ARGMOD : PROC_CHECK;
#endif
	if (flags & PROC_CHECK)
	{
		char	buf[PATH_MAX];

		return pathpath(path, NiL, PATH_REGULAR|PATH_EXECUTE, buf, sizeof(buf)) ? 0 : -1;
	}
	return procclose(procopen(path, argv, NiL, NiL, flags|PROC_FOREGROUND|PROC_GID|PROC_UID));
}
