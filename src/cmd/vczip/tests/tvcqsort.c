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
*                   Phong Vo <kpv@research.att.com>                    *
*                 Glenn Fowler <gsf@research.att.com>                  *
*                                                                      *
***********************************************************************/
#include	"vctest.h"

int	ilist[] = {3, 4, 4, 5, 1, 1, 2, 2, 7, 6};
int	isort[] = {1, 1, 2, 2, 3, 4, 4, 5, 6, 7};

int intcmp(Void_t* one, Void_t* two, Void_t* disc)
{
	int	i1 = *((int*)one), i2 = *((int*)two);
	return i1 - i2;
}

int main()
{
	int	i;

	vcqsort(ilist, sizeof(ilist)/sizeof(int), sizeof(int), intcmp, 0);
	for(i = 0; i < sizeof(ilist)/sizeof(int); ++i)
	{	if(ilist[i] != isort[i])
			terror("vcqsort() failed");
	}

	exit(0);
}
