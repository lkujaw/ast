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

/*	Close a sorting context
**
**	Written by Kiem-Phong Vo (07/18/96)
*/

#if __STD_C
int rsclose(Rs_t* rs)
#else
int rsclose(rs)
Rs_t*	rs;
#endif
{
	reg int	rv;

	while (rsdisc(rs, NIL(Rsdisc_t*), RS_POP));
	if ((rv = RSNOTIFY(rs,RS_CLOSE,0,0,rs->disc)) < 0)
		return rv;

	if(rs->vm)
		vmclose(rs->vm);
	if(rs->methdata)
		vmfree(Vmheap,rs->methdata);
	vmfree(Vmheap,rs);

	return 0;
}
