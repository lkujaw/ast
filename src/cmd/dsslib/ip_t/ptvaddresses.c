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
 * return the number of addresses covered by a
 */

int
ptvaddresses(Ptv_t* a, unsigned char* r)
{
	Ptvprefix_t*	ap;

	fvset(a->size, r, 0);
	fvset(a->size, a->r[1], 1);
	for (ap = (Ptvprefix_t*)dtfirst(a->dict); ap; ap = (Ptvprefix_t*)dtnext(a->dict, ap))
	{
		fvsub(a->size, a->r[0], ap->max, ap->min);
		fvadd(a->size, a->r[0], a->r[0], a->r[1]);
		fvadd(a->size, r, r, a->r[0]);
	}
	return 0;
}
