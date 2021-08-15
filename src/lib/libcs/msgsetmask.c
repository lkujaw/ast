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

#include "msglib.h"

#include <ctype.h>

/*
 * convert msg name list s to mask
 * *s=='!' inverts the mask
 */

unsigned long
msgsetmask(register const char* s)
{
	register int		c;
	register unsigned long m;
	int			invert;

	m = 0;
	invert = *s == '!';
	for (;;)
	{
		do if (!(c = *s++)) goto done; while (!isalnum(c));
		m |= MSG_MASK(msgindex(--s));
		do if (!(c = *s++)) goto done; while (isalnum(c));
	}
 done:
	return invert ? ~m : m;
}
