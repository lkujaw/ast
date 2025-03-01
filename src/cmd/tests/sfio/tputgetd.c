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
{
	Sfdouble_t	f, v;
	int	i, flag;
	Sfio_t	*fp;

	if(!(fp = sfopen(NIL(Sfio_t*), tstfile("sf", 0), "w+")) )
		terror("Can't open temp file");

#define BEGV	(Sfdouble_t)(1e-10)
#define ENDV	(Sfdouble_t)(1e-10 + 1)
#define INCR	(Sfdouble_t)(1e-3)

	for(f = BEGV; f < ENDV; f += INCR)
		if(sfputd(fp,f) < 0)
			terror("Writing %.12Lf",f);

	sfseek(fp,(Sfoff_t)0,0);
	for(flag = 0, f = BEGV, i = 0; f < ENDV; ++i, f += INCR)
	{	if((v = sfgetd(fp)) == f)
			continue;
		if(v <= (f - 1e-10) || v >= (f + 1e-10) )
			terror("Element=%d Input=%.12Lf, Expect=%.12Lf",i,v,f);
		else if(!flag)
		{	twarn("Element=%d Input=%.12Lf, Expect=%.12Lf\n",i,v,f);
			flag = 1;
		}
	}

	texit(0);
}
