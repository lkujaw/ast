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
/*
 * integer tuple list cx internal/external interface
 *
 * Glenn Fowler
 * AT&T Research
 */

#ifndef _ITL_H
#define _ITL_H

#include <cx.h>

#if _BLD_itl && defined(__EXPORT__)
#define extern		__EXPORT__
#endif

extern ssize_t		itl1external(Cx_t*, Cxtype_t*, int, int, int, const char*, Cxformat_t**, Cxvalue_t*, char*, size_t, Cxdisc_t*);
extern ssize_t		itl2external(Cx_t*, Cxtype_t*, int, int, int, const char*, Cxformat_t**, Cxvalue_t*, char*, size_t, Cxdisc_t*);
extern ssize_t		itl4external(Cx_t*, Cxtype_t*, int, int, int, const char*, Cxformat_t**, Cxvalue_t*, char*, size_t, Cxdisc_t*);

extern ssize_t		itl1internal(Cx_t*, Cxvalue_t*, int, int, int, const char*, size_t, Vmalloc_t*, Cxdisc_t*);
extern ssize_t		itl2internal(Cx_t*, Cxvalue_t*, int, int, int, const char*, size_t, Vmalloc_t*, Cxdisc_t*);
extern ssize_t		itl4internal(Cx_t*, Cxvalue_t*, int, int, int, const char*, size_t, Vmalloc_t*, Cxdisc_t*);

#undef	extern

#endif
