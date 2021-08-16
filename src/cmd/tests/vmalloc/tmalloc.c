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
	Vmalloc_t	*vm;
	Void_t		*addr[10];
	Void_t		*mem;
	int		i;

	Vmdcheap->round = 64;
	if(!(vm = vmopen(Vmdcheap, Vmbest, 0)) )
		terror("Open failed");

	for(i = 0; i < 10; ++i)
		if(!(addr[i] = vmalloc(vm,15)) )
			terror("vmalloc failed");
	for(i = 0; i < 10; ++i)
		if(vmfree(vm,addr[i]) < 0)
			terror("vmfree failed");
	for(i = 0; i < 10; ++i)
		if(!(addr[i] = vmalloc(vm,15)) )
			terror("vmalloc failed");
#ifdef DEBUG
	for(i = 0; i < 10; ++i)
		printf("size[%d]=%d\n",i,vmsize(vm,addr[i]));
	printf("Extent=%d\n",vmsize(vm,NIL(Void_t*)));
#endif

	mem = 0;
	if(posix_memalign(&mem, 3, 128) != EINVAL)
		terror("Bad return value from posix_memalign()");
	if(mem)
		terror("Bad memory");

	if(posix_memalign(&mem, 3*sizeof(Void_t*), 128) != EINVAL)
		terror("Bad return value from posix_memalign()");
	if(mem)
		terror("Bad memory");

	if(posix_memalign(&mem, (sizeof(Void_t*)<<4), 128) != 0 )
		terror("posix_memalign() failed");
	if(!mem)
		terror("Bad memory");

	texit(0);
}
