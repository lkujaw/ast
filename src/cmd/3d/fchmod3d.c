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

#ifdef fchmod3d

int
fchmod3d(int fd, mode_t mode)
{
#if FS
	Mount_t*	mp;

	if (!fscall(NiL, MSG_fchmod, 0, fd, mode))
		return(state.ret);
	mp = monitored();
#endif
	if (FCHMOD(fd, mode))
		return(-1);
#if FS
	if (mp)
		fscall(mp, MSG_fchmod, 0, fd, mode);
	for (mp = state.global; mp; mp = mp->global)
		if (fssys(mp, MSG_fchmod))
			fscall(mp, MSG_fchmod, 0, fd, mode);
#endif
	return(0);
}

#else

NoN(fchmod)

#endif
