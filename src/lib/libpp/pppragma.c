/***********************************************************************
*                                                                      *
*               This software is part of the ast package               *
*          Copyright (c) 1986-2011 AT&T Intellectual Property          *
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
 * common preprocessor pragma handler
 */

#include "pplib.h"

void
pppragma(char* directive, char* pass, char* name, char* value, int newline)
{
	register int	sep = 0;

	ppsync();
	if (directive)
	{
		ppprintf("#%s", directive);
		sep = 1;
	}
	if (pass)
	{
		if (sep)
		{
			sep = 0;
			ppprintf(" ");
		}
		ppprintf("%s:", pass);
	}
	if (name)
	{
		if (sep)
			ppprintf(" ");
		else
			sep = 1;
		ppprintf("%s", name);
	}
	if (value)
	{
		if (sep || pass)
			ppprintf(" ");
		ppprintf("%s", value);
	}
	if (newline)
		ppprintf("\n");
}
