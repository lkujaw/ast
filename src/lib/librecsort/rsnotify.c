/***********************************************************************
*                                                                      *
*               This software is part of the ast package               *
*          Copyright (c) 1996-2011 AT&T Intellectual Property          *
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
*                   Phong Vo <kpv@research.att.com>                    *
*                 Glenn Fowler <gsf@research.att.com>                  *
*                                                                      *
***********************************************************************/
#include	"rshdr.h"

/*	Discipline event notification.
*/

#if __STD_C
int rsnotify(Rs_t* rs, int op, Void_t* data, Void_t* arg, reg Rsdisc_t* disc)
#else
int rsnotify(rs, op, data, arg, disc)
Rs_t*		rs;
int		op;
Void_t*		data;
Void_t*		arg;
reg Rsdisc_t*	disc;
#endif
{
	int	r;

	r = 0;
	if (rs->events & op)
		for (; disc; disc = disc->disc)
			if ((disc->events & op) &&
			    (r = (*disc->eventf)(rs, op, data, arg, disc)))
				break;
	return r;
}
