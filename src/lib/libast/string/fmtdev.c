/***********************************************************************
*                                                                      *
*               This software is part of the ast package               *
*          Copyright (c) 1985-2011 AT&T Intellectual Property          *
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
 * Glenn Fowler
 * AT&T Bell Laboratories
 *
 * st_dev formatter
 */

#include <ast.h>
#include <ctype.h>
#include <ls.h>

char*
fmtdev(struct stat* st)
{
	char*		buf;
	unsigned long	mm;
	unsigned int	ma;
	unsigned int	mi;
	int		z;

	mm = (S_ISBLK(st->st_mode) || S_ISCHR(st->st_mode)) ? idevice(st) : st->st_dev;
	ma = major(mm);
	mi = minor(mm);
	buf = fmtbuf(z = 17);
	if (ma == '#' && isalnum(mi))
	{
		/*
		 * Plan? Nein!
		 */

		buf[0] = ma;
		buf[1] = mi;
		buf[2] = 0;
	}
	else
		sfsprintf(buf, z, "%03d,%03d", ma, mi);
	return buf;
}
