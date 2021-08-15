/***********************************************************************
*                                                                      *
*               This software is part of the ast package               *
*          Copyright (c) 2007-2012 AT&T Intellectual Property          *
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

#include <ast.h>
#include <shcmd.h>

extern int	b_codex(int, char**, Shbltin_t*);

void
lib_init(int flag, void* context)
{
	if (!flag)
		sh_builtin(context, "codex", b_codex, 0); 
}

SHLIB(codex)
