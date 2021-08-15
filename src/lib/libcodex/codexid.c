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
 * identify encoding given first block of encoded data
 * not all encodings are expected to self-identify
 */

#include <codex.h>

Codexmeth_t*
codexid(const void* head, size_t headsize, char* name, size_t namesize)
{
	register Codexmeth_t*	meth;

	for (meth = codexlist(NiL); meth; meth = codexlist(meth))
		if (meth->identf && (*meth->identf)(meth, head, headsize, name, namesize))
			return meth;
	return 0;
}
