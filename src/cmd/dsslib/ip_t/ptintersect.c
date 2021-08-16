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
 * return the table intersection of a and b
 */

Pt_t*
ptintersect(Pt_t* a, Pt_t* b)
{
	Pt_t*	t;
	Ptprefix_t*	ap;
	Ptprefix_t*	bp;

	if (!(t = ptopen(a->disc)))
		return 0;
	ap = (Ptprefix_t*)dtfirst(a->dict);
	bp = (Ptprefix_t*)dtfirst(b->dict);
	while (ap && bp)
	{
		if (ap->max < bp->min)
			ap = (Ptprefix_t*)dtnext(a->dict, ap);
		else if (ap->min > bp->max)
			bp = (Ptprefix_t*)dtnext(b->dict, bp);
		else
		{
			if (!ptinsert(t, (ap->min > bp->min) ? ap->min : bp->min, (ap->max < bp->max) ? ap->max : bp->max))
				break;
			if (ap->max < bp->max)
				ap = (Ptprefix_t*)dtnext(a->dict, ap);
			else if (ap->max > bp->max)
				bp = (Ptprefix_t*)dtnext(b->dict, bp);
			else
			{
				ap = (Ptprefix_t*)dtnext(a->dict, ap);
				bp = (Ptprefix_t*)dtnext(b->dict, bp);
			}
		}
	}
	return t;
}
