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

#if !defined(ACL3D) || !defined(SETACL)

#define aclent_t	char

#endif

#define MSG_facl	MSG_INIT(MSG_control, 051131, MSG_VAR_FILE)

int
facl3d(int fd, int cmd, int cnt, aclent_t* buf)
{
	register int	r;

#if FS
	register Mount_t*	mp;

	if (!fscall(NiL, MSG_facl, 0, fd, cmd, cnt, buf))
		return(state.ret);
	mp = monitored();
#endif
	r = FACL(fd, cmd, cnt, buf);
#if FS
	if (r >= 0)
	{
		if (mp)
			fscall(mp, MSG_facl, 0, fd, cmd, cnt, buf);
		for (mp = state.global; mp; mp = mp->global)
			if (fssys(mp, MSG_facl))
				fscall(mp, MSG_facl, 0, fd, cmd, cnt, buf);
	}
#endif
	return(r);
}
