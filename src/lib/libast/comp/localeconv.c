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
 * localeconv() intercept
 */

#include "lclib.h"

#undef	localeconv

static char	null[] = "";

static struct lconv	debug_lconv =
{
	",",
	".",
	&null[0],
	&null[0],
	&null[0],
	&null[0],
	&null[0],
	&null[0],
	&null[0],
	&null[0],
	CHAR_MAX,
	CHAR_MAX,
	CHAR_MAX,
	CHAR_MAX,
	CHAR_MAX,
	CHAR_MAX,
	CHAR_MAX,
	CHAR_MAX,
};

static struct lconv	default_lconv =
{
	".",
	&null[0],
	&null[0],
	&null[0],
	&null[0],
	&null[0],
	&null[0],
	&null[0],
	&null[0],
	&null[0],
	CHAR_MAX,
	CHAR_MAX,
	CHAR_MAX,
	CHAR_MAX,
	CHAR_MAX,
	CHAR_MAX,
	CHAR_MAX,
	CHAR_MAX,
};

#if !_lib_localeconv

struct lconv*
localeconv(void)
{
	return &default_lconv;
}

#endif

/*
 * localeconv() intercept
 */

struct lconv*
_ast_localeconv(void)
{
	if ((locales[AST_LC_MONETARY]->flags | locales[AST_LC_NUMERIC]->flags) & LC_debug)
		return &debug_lconv;
	if ((locales[AST_LC_NUMERIC]->flags & (LC_default|LC_local)) == LC_local)
		return locales[AST_LC_NUMERIC]->territory == &lc_territories[0] ? &default_lconv : &debug_lconv;
	return localeconv();
}
