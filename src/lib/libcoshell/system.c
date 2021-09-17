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
*               Glenn Fowler <glenn.s.fowler@gmail.com>                *
*                                                                      *
***********************************************************************/
#pragma prototyped
/*
 * Glenn Fowler
 * AT&T Research
 *
 * coshell system(3)
 */

#include "colib.h"

int
cosystem(const char* cmd)
{
	Coshell_t*	co;
	Cojob_t*	cj;
	int		status;

	if (!cmd)
		return !eaccess(pathshell(), X_OK);
	if (!(co = coopen(NiL, CO_ANY, NiL)))
		return -1;
	if (cj = coexec(co, cmd, CO_SILENT, NiL, NiL, NiL))
		cj = cowait(co, cj, -1);
	if (!cj)
		return -1;

	/*
	 * synthesize wait() status from shell status
	 * lack of synthesis is the standard's proprietary sellout
	 */

	status = cj->status;
	if (EXITED_TERM(status))
		status &= ((1<<(EXIT_BITS-1))-1);
	else
		status = (status & ((1<<EXIT_BITS)-1)) << EXIT_BITS;
	return status;
}
