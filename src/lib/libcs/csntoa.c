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
 * Glenn Fowler
 * AT&T Research
 *
 * return the string representation of addr
 */

#include "cslib.h"

char*
csntoa(register Cs_t* state, unsigned long addr)
{
	register unsigned char*	p;
	int32_t			a;

	a = addr;
	p = (unsigned char*)&a;
	if ((!addr || p[0] == 127 && p[1] == 0 && p[2] == 0 && p[3] <= 1) && !state->ntoa[sizeof(state->ntoa)-1])
	{
		state->ntoa[sizeof(state->ntoa)-1] = 1;
		addr = csaddr(state, NiL);
		state->ntoa[sizeof(state->ntoa)-1] = 0;
	}
	sfsprintf(state->ntoa, sizeof(state->ntoa), "%d.%d.%d.%d", p[0], p[1], p[2], p[3]);
	messagef((state->id, NiL, -8, "ntoa(%s) call", state->ntoa));
	return state->ntoa;
}

char*
_cs_ntoa(unsigned long addr)
{
	return csntoa(&cs, addr);
}
