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
 * syscall message server side receipt
 */

#include "msglib.h"

#include <cs.h>

/*
 * read a message from fd into buf,siz
 * handles record boundaries on fd
 * siz must be > MSG_SIZE_SIZE
 */

ssize_t
msgread(int fd, char* buf, size_t siz)
{
	register ssize_t	n;
	register int		o;

	if ((n = cspeek(&cs, fd, buf, MSG_SIZE_SIZE)) >= 0) o = 0;
	else
	{
		n = csread(&cs, fd, buf, MSG_SIZE_SIZE, CS_EXACT);
		o = MSG_SIZE_SIZE;
	}
	if (n != MSG_SIZE_SIZE) return n ? -1 : 0;
	n = msggetsize(buf);
	if (n <= MSG_SIZE_SIZE || n > siz || csread(&cs, fd, buf + o, n - o, CS_EXACT) != n - o) return -1;
	return n;
}
