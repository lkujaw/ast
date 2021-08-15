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
#include	"vmtest.h"

tmain()
{
	Void_t		*addr[10];
	Vmalloc_t	*vm, *tv;
	int		i;

	Vmdcheap->round = 127;
	if(!(vm = vmopen(Vmdcheap,Vmbest,0)) )
		terror("Can't open a region");

	for(i = 0; i < 10; i += 2)
	{	addr[i] = vmalloc(vm,88);
		if((((Vmulong_t)addr[i])%ALIGN) != 0)
			terror("Unaligned addr");

		addr[i+1] = vmalloc(Vmheap,128);
		if((((Vmulong_t)addr[i+1])%ALIGN) != 0)
			terror("Unaligned addr");
	}

	for(i = 0; i < 10; i += 2)
	{	if((tv = vmregion(addr[i])) != vm)
			terror("Wrong region");
		if((tv = vmregion(addr[i+1])) != Vmheap)
			terror("Wrong region");
	}

	vmclose(vm);

	texit(0);
}
