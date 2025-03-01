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
*                 Glenn Fowler <gsf@research.att.com>                  *
*                  David Korn <dgk@research.att.com>                   *
*                   Phong Vo <kpv@research.att.com>                    *
*                                                                      *
***********************************************************************/
#pragma prototyped

/*
 * return the codex method for name
 */

#include <codex.h>
#include <dlldefs.h>

Codexmeth_t*
codexmeth(const char* name)
{
	register Codexmeth_t*	meth;
	register const char*	s;
	register const char*	t;
	Codexmeth_t*		last;
	void*			dll;
	int			plugin;
	Codexlib_f		lib;
	char			tmp[CODEX_NAME];

	if (!name)
		return CODEXERROR->meth;
	plugin = 0;
	meth = codexstate.first;
	while (meth)
	{
		if (!codexcmp(name, meth->name))
			return meth;
		last = meth;
		if (!(meth = meth->next) && !plugin)
		{
			plugin = 1;
			for (s = name, t = 0; *s && *s != '+'; s++)
				if (*s == '-')
				{
					if (t)
						break;
					t = s;
				}
			do
			{
				sfsprintf(tmp, sizeof(tmp), "%-.*s", s - name, name);
				if (dll = dllplug("codex", tmp, NiL, RTLD_LAZY, NiL, 0))
				{
					if ((lib = (Codexlib_f)dlllook(dll, "codex_lib")) && (meth = (*lib)(name)))
						last->next = meth;
					break;
				}
			} while (s != t && (s = t));
		}
	}
	return meth;
}
