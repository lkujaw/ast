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

#include "stdhdr.h"

int
vswprintf(wchar_t* s, size_t n, const wchar_t* fmt, va_list args)
{
	Sfio_t	f;
	int	v;

	if (!s)
		return -1;

	/*
	 * make a fake stream
	 */

	SFCLEAR(&f, NiL);
	f.flags = SF_STRING|SF_WRITE;
	f.bits = SF_PRIVATE;
	f.mode = SF_WRITE;
	f.size = n - 1;
	f.data = f.next = f.endr = (uchar*)s;
	f.endb = f.endw = f.data + f.size;

	/*
	 * call and adjust
	 */

	v = vfwprintf(&f, fmt, args);
	*f.next = 0;
	_Sfi = f.next - f.data;
	return v;
}
