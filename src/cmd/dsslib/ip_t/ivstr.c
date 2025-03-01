/***********************************************************************
*                                                                      *
*               This software is part of the ast package               *
*          Copyright (c) 2000-2011 AT&T Intellectual Property          *
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
*                   Phong Vo <kpv@research.att.com>                    *
*                                                                      *
***********************************************************************/
#pragma prototyped

#include "ivlib.h"

#include <ip6.h>

/*
 * convert string to address or prefix
 */

int
ivstr(Iv_t* iv, const char* s, char** e, unsigned char* addr, unsigned char* bits)
{
	int	c;
	int	i;
	int	n;
	int	r;

	if (iv->size == 16)
		return strtoip6(s, e, addr, bits);
	r = -1;
	i = 0;
	do
	{
		n = 0;
		while ((c = *s++) >= '0' && c <= '9')
			n = n * 10 + (c - '0');
		if (n > 0xff)
			goto done;
		addr[i++] = n;
	} while (c == '.' && i < iv->size);
	if (bits)
	{
		if (c == '/')
		{
			n = 0;
			while ((c = *s++) >= '0' && c <= '9')
				n = n * 10 + (c - '0');
			c = (n + 7) / 8;
			if (i > c)
				i = c;
		}
		else
			n = i * 8;
		*bits = n;
	}
	while (i < iv->size)
		addr[i++] = 0;
	r = 0;
 done:
	if (e)
		*e = (char*)(s - 1);
	return r;
}
