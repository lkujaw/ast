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
 * create bi-directional local pipe
 */

#include "cslib.h"

int
cspipe(Cs_t* state, int* fds)
{

	csprotect(&cs);

#if CS_LIB_SOCKET_UN

	return socketpair(AF_UNIX, SOCK_STREAM, 0, fds);

#else

	return pipe(fds);

#endif

}

int
_cs_pipe(int* fds)
{
	return cspipe(&cs, fds);
}
