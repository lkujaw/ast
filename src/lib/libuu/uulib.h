/***********************************************************************
*                                                                      *
*               This software is part of the ast package               *
*          Copyright (c) 1998-2011 AT&T Intellectual Property          *
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
 * uuencode/uudecode private interface
 *
 * AT&T Research
 */

#ifndef _UULIB_H
#define _UULIB_H

#define _UU_PRIVATE_ \
	unsigned long	flags;	\
	int		mode;	\
	Sfio_t*		lp;	\
	Sfio_t*		ip;	\
	Sfio_t*		op;	\
	size_t		count;

#include "uu.h"

#define UU_CLOSEOUT	(1<<4)		/* close op when done		*/
#define UU_FREEPATH	(1<<5)		/* free path when done		*/
#define UU_HEADERMUST	(1<<6)		/* header must be called	*/
#define UU_LENGTH	(1<<7)		/* length encoded too		*/
#define UU_DEFAULT	(1<<8)		/* original method was default	*/
#define UU_METHOD	(1<<9)		/* first method specific bit	*/

typedef struct
{
	const char*	end;
	int		pad;
	int		fill;
	unsigned long	flags;
	int		size;
	const char	map[65];
} Uudata_t;

#endif
