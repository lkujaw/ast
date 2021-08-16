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
 * ping host by name
 */

#include "cslib.h"

#define M	"yo\n"
#define N	(sizeof(M)-1)

int
csping(register Cs_t* state, const char* name)
{
	register int	fd;
	register int	n;

	sfsprintf(state->temp, sizeof(state->path), "/dev/tcp/%s/inet.echo", name);
	if ((fd = csopen(state, state->temp, 0)) < 0) return -1;
	n = (cswrite(state, fd, M, N) != N || csread(state, fd, state->temp, N, CS_LINE) != N || strncmp(M, state->temp, N)) ? -1 : 0;
	close(fd);
	if (n) messagef((state->id, NiL, -1, "ping: %s: no contact", name));
	return n;
}

int
_cs_ping(const char* name)
{
	return csping(&cs, name);
}
