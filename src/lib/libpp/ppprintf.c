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
 * preprocessor printf using ppputchar() buffering
 */

#include "pplib.h"

int
ppprintf(char* format, ...)
{
	va_list	ap;
	Sfio_t*	sp;

	if (!(sp = sfnew(NiL, pp.outp, MAXTOKEN, -1, SF_WRITE|SF_STRING)))
		error(3, "temporary buffer allocation error");
	va_start(ap, format);
	sfvprintf(sp, format, ap);
	va_end(ap);
	pp.outp += sfseek(sp, 0L, SEEK_CUR);
	ppcheckout();
	sfclose(sp);
	return 0;
}
