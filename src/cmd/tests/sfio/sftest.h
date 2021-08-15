/***********************************************************************
*                                                                      *
*               This software is part of the ast package               *
*          Copyright (c) 1999-2011 AT&T Intellectual Property          *
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
*                                                                      *
***********************************************************************/
#include	"FEATURE/sfio"

#if !_PACKAGE_ast
#ifdef __STDC__
#include	<stdarg.h>
#else
#include	<varargs.h>
#endif
#endif

#if _SFIO_H_ONLY
#include	<sfio.h>
#else
#include	<sfio_t.h>
#endif

#if _PACKAGE_ast
#include	<ast.h>
#endif

#if _hdr_unistd
#include	<unistd.h>
#endif

#include	<errno.h>

#include	"terror.h"

#ifndef EINTR
#define EINTR	4
#endif
#ifndef EBADF
#define EBADF	9
#endif
#ifndef EAGAIN
#define EAGAIN	11
#endif
#ifndef ENOMEM
#define ENOMEM	12
#endif
#ifndef ESPIPE
#define ESPIPE	29
#endif

#if _hdr_math
#include	<math.h>
#endif

#if _hdr_float
#include	<float.h>
#endif
