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
 * dump table a on sp
 */

int
ptvdump(Ptv_t* a, Sfio_t* sp)
{
	Ptvprefix_t*	p;

	for (p = (Ptvprefix_t*)dtfirst(a->dict); p; p = (Ptvprefix_t*)dtnext(a->dict, p))
		sfprintf(sp, "%s %s %-24s %-24s\n", fmtfv(a->size, p->min, 16, 0, 0), fmtfv(a->size, p->max, 16, 0, 0), fmtip6(p->min, -1), fmtip6(p->max, -1));
	return sfsync(sp);
}
