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

#include "ptvlib.h"

/*
 * return non-zero if table a is a subset of table b
 */

int
ptvsubset(Ptv_t* a, Ptv_t* b)
{
	Ptvprefix_t*	ap;
	Ptvprefix_t*	bp;

	ap = (Ptvprefix_t*)dtfirst(a->dict);
	bp = (Ptvprefix_t*)dtfirst(b->dict);
	while (ap)
	{
		if (!bp || fvcmp(a->size, ap->max, bp->min) < 0 || fvcmp(a->size, ap->min, bp->min) < 0)
			return 0;
		if (fvcmp(a->size, ap->max, bp->max) < 0)
			ap = (Ptvprefix_t*)dtnext(a->dict, ap);
		else if (fvcmp(a->size, ap->max, bp->max) > 0)
			bp = (Ptvprefix_t*)dtnext(b->dict, bp);
		else
		{
			ap = (Ptvprefix_t*)dtnext(a->dict, ap);
			bp = (Ptvprefix_t*)dtnext(b->dict, bp);
		}
	}
	return 1;
}
