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

#if _nosys_utimets

NoN(utimets)

#else

#define atimeof(p)	(((p)+0)->tv_sec)
#define mtimeof(p)	(((p)+1)->tv_sec)

int
utimets3d(const char* path, const struct timespec* tms)
{
	register char*	sp;
	register int	r;
	time_t		atime;
	time_t		mtime;
#if FS
	Mount_t*	mp;
#endif

	if (state.in_2d)
		return(UTIMETS(path, tms));
	if (tms)
	{
		atime = atimeof(tms);
		mtime = mtimeof(tms);
	}
	else atime = mtime = time((time_t*)0);
#if FS
	if (!fscall(NiL, MSG_utime, 0, path, atime, mtime))
		return(state.ret);
	mp = monitored();
#endif
	if (!(sp = pathreal(path, P_TOP, NiL)))
		return(-1);
	r = UTIMETS(sp, tms);
#if FS
	if (!r)
	{
		if (mp)
			fscall(mp, MSG_utime, 0, path, atime, mtime);
		for (mp = state.global; mp; mp = mp->global)
			if (fssys(mp, MSG_utime))
				fscall(mp, MSG_utime, 0, path, atime, mtime);
	}
#endif
	return(r);
}

#endif
