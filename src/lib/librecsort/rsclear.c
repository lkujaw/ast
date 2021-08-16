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

/*	Clear space in a region
**
**	Written by Kiem-Phong Vo (07/18/96)
*/

#if __STD_C
int rsclear(Rs_t* rs)
#else
int rsclear(rs)
Rs_t*	rs;
#endif
{
	reg uchar	*m, *endm;

	for(m = (uchar*)rs->methdata, endm = m+rs->meth->size; m < endm; ++m)
		*m = 0;

	if(rs->vm)
		vmclear(rs->vm);
	rs->c_size = 0;
	rs->type &= RS_TYPES;
	rs->free = rs->sorted = NIL(Rsobj_t*);

	return 0;
}
