/***********************************************************************
*                                                                      *
*               This software is part of the ast package               *
*          Copyright (c) 1989-2011 AT&T Intellectual Property          *
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
 * expression library support
 */

#include "exlib.h"

/*
 * return 0 value for type
 */

Extype_t
exzero(int type)
{
	Extype_t	v;

	switch (type)
	{
	case FLOATING:
		v.floating = 0.0;
		break;
	case INTEGER:
	case UNSIGNED:
		v.integer = 0;
		break;
	case STRING:
		v.string = expr.nullstring;
		break;
	}
	return v;
}
