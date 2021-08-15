/***********************************************************************
*                                                                      *
*               This software is part of the ast package               *
*          Copyright (c) 1989-2011 AT&T Intellectual Property          *
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
*                   Eduardo Krell <ekrell@adexus.cl>                   *
*                                                                      *
***********************************************************************/
#pragma prototyped

#include "3d.h"

#ifdef fsync3d

int
fsync3d(int fd)
{
#if FS
	Mount_t*	mp;

	if (!fscall(NiL, MSG_fsync, 0, fd))
		return(state.ret);
	mp = monitored();
#endif
	if (FSYNC(fd))
		return(-1);
#if FS
	if (mp)
		fscall(mp, MSG_fsync, 0, fd);
	for (mp = state.global; mp; mp = mp->global)
		if (fssys(mp, MSG_fsync))
			fscall(mp, MSG_fsync, 0, fd);
#endif
	return(0);
}

#else

NoN(fsync)

#endif
