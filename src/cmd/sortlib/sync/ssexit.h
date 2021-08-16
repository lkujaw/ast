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
*                                                                      *
***********************************************************************/
#pragma prototyped

/*
 * ibm dfsort user exit function interface
 *
 * Glenn Fowler
 * AT&T Research
 */

#ifndef _SSEXIT_H
#define _SSEXIT_H	1

#include <ast.h>
#include <error.h>
#include <recsort.h>

#define SS_EXIT_FIRST		0	/* the first exit record	*/
#define SS_EXIT_MOST		4	/* the middle exit records	*/
#define SS_EXIT_LAST		8	/* the last exit record		*/

#define SS_EXIT_ACCEPT		0	/* accept this record		*/
#define SS_EXIT_DELETE		4	/* delete this record		*/
#define SS_EXIT_CLOSE		8	/* don't call this exit again	*/
#define SS_EXIT_INSERT		12	/* insert this record		*/
#define SS_EXIT_TERMINATE	16	/* terminate the sort		*/
#define SS_EXIT_REPLACE		20	/* replace this record		*/

typedef int (*Ssexit_f)(Rsobj_t*, Rsobj_t*, void**);

#endif
