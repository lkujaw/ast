/***********************************************************************
*                                                                      *
*               This software is part of the ast package               *
*          Copyright (c) 1999-2011 AT&T Intellectual Property          *
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
#include	"sftest.h"

tmain()
{	Sfio_t	*f;
	int	i, c;

	if(!(f = sftmp(8)))
		terror("Can't open temp file");

	for(i = 0; i < 10000; ++i)
		if(sfputc(f,(i%26)+'a') < 0)
			terror("Writing %c",(i%26)+'a');

	sfseek(f,(Sfoff_t)0,0);

	for(i = 0; i < 10000; ++i)
		if((c = sfgetc(f)) != ((i%26)+'a'))
			terror("Input=%#o, Expect=%c",c,(i%26)+'a');

	texit(0);
}
