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
/*
 * realpath implementation
 */

#define realpath	______realpath
#define resolvepath	______resolvepath

#include <ast.h>

#undef	realpath
#undef	resolvepath

#undef	_def_map_ast
#include <ast_map.h>

extern int		resolvepath(const char*, char*, size_t);

#if defined(__EXPORT__)
#define extern	__EXPORT__
#endif

extern char*
realpath(const char* file, char* path)
{
	/* @lkoutsofios path may be NULL */
	if (!path) {
		if (!(path = malloc (PATH_MAX))) {
			return NULL;
		}
	}
	return resolvepath(file, path, PATH_MAX) > 0 ? path : (char*)0;
}
