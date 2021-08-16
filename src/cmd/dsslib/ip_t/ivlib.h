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

#ifndef _IVHDR_H
#define _IVHDR_H	1

#if _PACKAGE_ast || _PACKAGE_astsa
#include		<ast.h>
#else

extern void*		malloc _ARG_((size_t));
extern void*		calloc _ARG_((size_t, size_t));
extern void		free _ARG_((void*));

extern void		abort _ARG_((void));

#endif

#include		<iv.h>
#include		<ivmethods.h>
#include		<cdt.h>

#ifndef NIL
#define NIL(t)		((t)0)
#endif

#ifndef OFFSET
#define OFFSET(t,e)	((size_t)(&(((t*)0)->e)) )
#endif

#ifndef ASSERT
#ifdef DEBUG
#define	ASSERT(p)	((p) ? 0 : (abort(),0))
#else
#define ASSERT(p)
#endif
#endif

#endif /* _IVHDR_H */
