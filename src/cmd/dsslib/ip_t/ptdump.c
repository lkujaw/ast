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
 * dump table a on sp
 */

int
ptdump(Pt_t* a, Sfio_t* sp)
{
	Ptprefix_t*	p;

	for (p = (Ptprefix_t*)dtfirst(a->dict); p; p = (Ptprefix_t*)dtnext(a->dict, p))
		sfprintf(sp, "%0*I*x %0*I*x %-16s %-16s\n", sizeof(p->min) * 2, sizeof(p->min), p->min, sizeof(p->max) * 2, sizeof(p->max), p->max, fmtip4(p->min, -1), fmtip4(p->max, -1));
	return sfsync(sp);
}
