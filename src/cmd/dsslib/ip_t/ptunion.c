/***********************************************************************
*                                                                      *
*               This software is part of the ast package               *
*          Copyright (c) 2000-2011 AT&T Intellectual Property          *
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
*                   Phong Vo <kpv@research.att.com>                    *
*                                                                      *
***********************************************************************/
#pragma prototyped

#include "ptlib.h"

/*
 * return the table union of a and b
 */

Pt_t*
ptunion(Pt_t* a, Pt_t* b)
{
	Ptprefix_t*	bp;

	if (!(a = ptcopy(a)))
		return 0;
	for (bp = (Ptprefix_t*)dtfirst(b->dict); bp; bp = (Ptprefix_t*)dtnext(b->dict, bp))
		if (!ptinsert(a, bp->min, bp->max))
			break;
	return a;
}
