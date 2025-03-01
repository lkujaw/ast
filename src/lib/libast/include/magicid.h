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
 * generic binary magic id definitions
 */

#ifndef _MAGICID_H
#define _MAGICID_H		1

#include <ast_common.h>

#define MAGICID		0x00010203

typedef uint32_t Magicid_data_t;

typedef struct Magicid_s
{
	Magicid_data_t	magic;		/* magic number			*/
	char		name[8];	/* generic data/application name*/
	char		type[12];	/* specific data type		*/
	Magicid_data_t	version;	/* YYYYMMDD or 0xWWXXYYZZ	*/
	Magicid_data_t	size;
} Magicid_t;

#endif
