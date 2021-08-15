/***********************************************************************
*                                                                      *
*               This software is part of the ast package               *
*          Copyright (c) 1990-2011 AT&T Intellectual Property          *
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
#pragma prototyped

/*
 * syscall message implementation interface
 */

#ifndef _MSGLIB_H
#define _MSGLIB_H

#define CS_INTERFACE	2

#include <ast.h>

#include "cs_lib.h"

#include <msg.h>
#include <ast_dir.h>
#include <errno.h>
#include <ls.h>

#ifndef D_FILENO
#define D_FILENO(d)	(1)
#endif

#ifndef errno
extern int	errno;
#endif

#endif
