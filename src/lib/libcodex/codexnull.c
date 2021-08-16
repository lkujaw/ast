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
 * return null write stream for pure codexdata()
 */

#include <sfio_t.h>
#include <codex.h>

static ssize_t
nullread(Sfio_t* f, void* buf, size_t n, Sfdisc_t* disc)
{
	return 0;
}

static ssize_t
nullwrite(Sfio_t* f, const void* buf, size_t n, Sfdisc_t* disc)
{
	return n;
}

static Sfdisc_t		nulldisc = { nullread, nullwrite };

static const char	nullbuf[1];

static Sfio_t		null = SFNEW(nullbuf, 0, 0, SF_WRITE, &nulldisc, 0);

Sfio_t*
codexnull(void)
{
	return &null;
}
