/***********************************************************************
*                                                                      *
*               This software is part of the ast package               *
*          Copyright (c) 2003-2011 AT&T Intellectual Property          *
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
*                                                                      *
***********************************************************************/
#ifndef _VCHDR_H
#define _VCHDR_H	1

#if _PACKAGE_ast
#include	<ast.h>
#endif

#define _VCODEX_PRIVATE \
	Vcbuffer_t*	list;	/* allocated buffers	*/ \
	unsigned int	busy;	/* total buffer size 	*/ \
	unsigned int	nbuf;	/* number of buffers 	*/ 

#include	"vcodex.h"

#ifdef VMFL
#include	<vmalloc.h>
#endif

#include	<ctype.h>
#include	<stdlib.h>
#include	<string.h>

#if _sys_times
#include	<sys/times.h>
#endif
#if _hdr_unistd
#include	<unistd.h>
#endif
#if __STD_C
#include	<stdarg.h>
#else
#include	<varargs.h>
#endif

#if !_PACKAGE_ast && _WIN32 /* to do binary I/O on Windows */
#include	<fcntl.h>
#include	<io.h>
#ifndef _O_BINARY
#define _O_BINARY	0x8000
#endif
#ifndef O_BINARY
#define O_BINARY	_O_BINARY
#endif
#endif /*!_PACKAGE_ast && _WIN32*/

#include <debug.h>

#ifndef NIL
#define NIL(type)	((type)0)
#endif

#ifndef reg
#define reg		register
#endif

#ifdef isblank
#undef isblank
#endif
#define isblank(c)	((c) == ' ' || (c) == '\t')

#define TYPECAST(tp,p)	((tp)((unsigned long)(p)))

#define RL_ESC		255	/* default escape character	*/
#define RL_ZERO		254	/* (0,RL_ZERO) codes 0-runs	*/
#define RL_ONE		253	/* (1,RL_ONE) codes 1-runs	*/

_BEGIN_EXTERNS_
extern ssize_t		_vcrle2coder _ARG_((Vcodex_t*, ssize_t,
					    Vcchar_t*, ssize_t,
					    Vcchar_t*, ssize_t,
					    Vcchar_t**, ssize_t));

extern Vcmtarg_t*	_vcmtarg _ARG_((Vcmtarg_t*, char*, char*, ssize_t));

extern Void_t*		memcpy _ARG_((Void_t*, const Void_t*, size_t));
extern Void_t*		malloc _ARG_((size_t));
extern Void_t*		realloc _ARG_((Void_t*, size_t));
extern Void_t*		calloc _ARG_((size_t, size_t));
extern void		free _ARG_((Void_t*));
_END_EXTERNS_

#endif /*_VCHDR_H*/
