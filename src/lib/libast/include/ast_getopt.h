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
 * legacy standard getopt interface
 */

#ifdef	_AST_STD_I
#undef	_AST_GETOPT_H
#define _AST_GETOPT_H		-1
#endif
#ifndef _AST_GETOPT_H
#define _AST_GETOPT_H		1

extern int	opterr;
extern int	optind;
extern int	optopt;
extern char*	optarg;

extern int	getopt(int, char* const*, const char*);
extern int	getsubopt(char**, char* const*, char**);

#endif
