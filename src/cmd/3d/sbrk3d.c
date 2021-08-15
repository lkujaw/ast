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

#ifdef	sbrk3d

void*
sbrk3d(ssize_t i)
{
#if FS
	register Mount_t*	mp;
	void*			p;

	initialize();
	if ((p = SBRK(i)) != (void*)(-1))
		for (mp = state.global; mp; mp = mp->global)
			if (fssys(mp, MSG_break))
				fscall(mp, MSG_break, 0, p);
	return(p);
#else
	return(SBRK(i));
#endif
}

#else

NoN(sbrk)

#endif
