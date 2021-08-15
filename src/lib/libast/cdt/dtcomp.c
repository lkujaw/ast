/***********************************************************************
*                                                                      *
*               This software is part of the ast package               *
*          Copyright (c) 1985-2011 AT&T Intellectual Property          *
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
*                   Phong Vo <kpv@research.att.com>                    *
*                                                                      *
***********************************************************************/
/*
 * backwards binary compatibility
 */

#include <cdt.h>

#if defined(__EXPORT__)
#define extern	__EXPORT__
#endif

#undef dtflatten
extern Dtlink_t* dtflatten(Dt_t* d)
{
	return (Dtlink_t*)(*(_DT(d)->searchf))((d),(Void_t*)(0),DT_FLATTEN);
}

#undef dtextract
extern Dtlink_t* dtextract(Dt_t* d)
{
	return (Dtlink_t*)(*(_DT(d)->searchf))((d),(Void_t*)(0),DT_EXTRACT);
}

#undef dtrestore
extern Dtlink_t* dtrestore(Dt_t* d, Void_t* l)
{
	return (Dtlink_t*)(*(_DT(d)->searchf))((d),(l),DT_RESTORE);
}

#undef dtsize
extern ssize_t dtsize(Dt_t* d)
{
	return (ssize_t)(*(_DT(d)->searchf))((d),(Void_t*)(0),DT_STAT);
}

#undef dtstat
extern ssize_t dtstat(Dt_t* d)
{
	return (ssize_t)(*(_DT(d)->searchf))((d),(Void_t*)(0),DT_STAT);
}
