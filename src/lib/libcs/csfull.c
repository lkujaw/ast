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
 * like csname() except `.' qualifications retained
 */

#include "cslib.h"

char*
csfull(register Cs_t* state, unsigned long addr)
{
	char*	s;

	state->flags |= CS_ADDR_FULL;
	s = csname(state, addr);
	state->flags &= ~CS_ADDR_FULL;
	messagef((state->id, NiL, -8, "full(%s) = %s", csntoa(state, addr), s));
	return s;
}

char*
_cs_full(unsigned long addr)
{
	return csfull(&cs, addr);
}
