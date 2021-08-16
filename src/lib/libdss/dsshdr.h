/***********************************************************************
*                                                                      *
*               This software is part of the ast package               *
*          Copyright (c) 2002-2011 AT&T Intellectual Property          *
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
 * dss library private implementation header
 *
 * Glenn Fowler
 * AT&T Research
 */

#ifndef _DSSHDR_H
#define _DSSHDR_H	1

struct Format_s; typedef struct Format_s Format_t;

#define _DSS_PRIVATE_ \
	Format_t*		print;

#include "dsslib.h"

/*
 * library private globals
 */

#define dssmethinit		_dss_meth_init

extern Dssmeth_t*		dssmethinit(const char*, const char*, const char*, Dssdisc_t*, Dssmeth_t*);

#endif
