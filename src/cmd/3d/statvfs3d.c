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

#if defined(statvfs3d) && defined(_sys_statvfs)

int
statvfs3d(const char* path, struct statvfs* fs)
{
	register char*	sp;
#if FS
	Mount_t*	mp;

	if (!fscall(NiL, MSG_statfs, 0, path, fs))
		return(state.ret);
	mp = monitored();
#endif
	if (!(sp = pathreal(path, 0, NiL)))
		return(-1);
	if (STATVFS(sp, fs))
		return(-1);
#if FS
	if (mp)
		fscall(mp, MSG_statfs, 0, state.path.name, fs);
	for (mp = state.global; mp; mp = mp->global)
		if (fssys(mp, MSG_statfs))
			fscall(mp, MSG_statfs, 0, state.path.name, fs);
#endif
	return(0);
}

#else

NoN(statvfs)

#endif
