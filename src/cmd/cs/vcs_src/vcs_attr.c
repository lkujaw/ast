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
/*
 *	return attr of a sfile 
 */


#include "vcs_rscs.h"

int get_attr(f, ap)
	Sfio_t*		f;
	register attr_t*	ap;
{
	if (sfread(f, (char *)ap, sizeof(attr_t)) != sizeof(attr_t) || !ISRSCS(ap))
	{
		rserrno = NOTRSCS;
		return (-1);
	}

	return (0);
}


