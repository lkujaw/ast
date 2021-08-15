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

#if _typ_long_double
#include	<float.h>
#endif

tmain()
{
#if _typ_long_double
	long double	ldval, ldmax;
	char		*s, *str;

	if(sfsscanf("Inf","%Le",&ldmax) != 1)
		terror("sfsscanf Inf failed");
	if(!(s = sfprints("%Le",ldmax)) )
		terror("sfprints failed1");
	if(!(str = malloc(strlen(s)+1)) )
		terror("Malloc failed");
	strcpy(str,s);

	if(sfsscanf(str,"%Le",&ldval) != 1)
		terror("sfsscanf failed");
	if(!(s = sfprints("%Le",ldval)) )
		terror("sfprints failed2");

	if(strcmp(s,str) != 0)
		terror("Bad conversion, expecting %s and getting %s",str,s);
#endif

	texit(0);
}
