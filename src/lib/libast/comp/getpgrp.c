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
#pragma prototyped

#define getpgrp		______getpgrp

#include <ast_std.h>

#undef	getpgrp

/*
 * bsd		int getpgrp(int);
 * s5		int getpgrp(void);
 * posix	pid_t getpgrp(void);
 * user		SOL
 */

extern int	getpgrp(int);

#if defined(__EXPORT__)
#define extern	__EXPORT__
#endif

extern int
_ast_getpgrp(void)
{
	return getpgrp(0);
}
