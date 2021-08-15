/***********************************************************************
*                                                                      *
*               This software is part of the ast package               *
*          Copyright (c) 1985-2012 AT&T Intellectual Property          *
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
#ifndef _AST_COMMON_H
#define _AST_COMMON_H	1

#include <ast_sa.h>
#include <sys/types.h>

#define Void_t	void
#define _ARG_(x)	x
#define _BEGIN_EXTERNS_
#define _END_EXTERNS_
#define __STD_C		1

#if _hdr_stdint
#include <stdint.h>
#else
#include <inttypes.h>
#endif

#if _hdr_unistd
#include <unistd.h>
#endif

#define _typ_int32_t	1
#ifdef _ast_int8_t
#define _typ_int64_t	1
#endif

#endif
