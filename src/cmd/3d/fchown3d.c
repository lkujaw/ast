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

#ifdef fchown3d

int
fchown3d(int fd, uid_t uid, gid_t gid)
{
#if FS
	Mount_t*	mp;

	if (!fscall(NiL, MSG_fchown, 0, fd, uid, gid))
		return state.ret;
	mp = monitored();
#endif
	if (FCHOWN(fd, uid, gid))
		return -1;
#if FS
	if (mp)
		fscall(mp, MSG_fchown, 0, fd, uid, gid);
	for (mp = state.global; mp; mp = mp->global)
		if (fssys(mp, MSG_fchown))
			fscall(mp, MSG_fchown, 0, fd, uid, gid);
#endif
	return 0;
}

#else

NoN(fchown)

#endif
