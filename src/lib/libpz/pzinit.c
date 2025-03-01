/***********************************************************************
*                                                                      *
*               This software is part of the ast package               *
*          Copyright (c) 1998-2011 AT&T Intellectual Property          *
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
 * initialize a pzip discipline library
 */

#include "pzlib.h"

const char*
pzinit(register Pz_t* pz, register const char* name, Pzinit_f initf)
{
	const char*		options;
	const char*		usage;
	char*			id;

	options = pz->disc->options;
	if (!(usage = (*initf)(pz, pz->disc)))
	{
		if (pz->disc && pz->disc->errorf)
		{
			if (id = strchr((char*)state.id, ':'))
				id++;
			else
				id = (char*)state.id;
			(*pz->disc->errorf)(pz, pz->disc, 2, "%s: %s_init: initialization function error", name, id);
		}
		return 0;
	}
	optget(NiL, usage);
	if (pz->disc->options != options)
	{
		if (!pz->disc->options)
			pz->options = 0;
		else if (!(pz->options = vmstrdup(pz->vm, pz->disc->options)))
		{
			pznospace(pz);
			return 0;
		}
	}
	if (pz->options && pzoptions(pz, pz->part, pz->options, 0) < 0)
		return 0;
	return usage;
}
