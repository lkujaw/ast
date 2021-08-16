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
	Vmalloc_t*	vm;
	Void_t*		addr;
	Vmstat_t	st;

	if(!(vm = vmopen(Vmdcheap,Vmbest,0)) )
		terror("Can't open Vmbest region");
	if(!(addr = vmalloc(vm,123)) )
		terror("vmalloc failed1");
	if(vmstat(vm,&st) < 0 )
		terror("vmstat failed11");
	if(st.n_busy != 1 || st.s_busy < 123 || st.s_busy > (123+32))
		terror("Wrong statistics1");
	if(vmfree(vm,addr) < 0)
		terror("vmfree failed1");
	if(vmstat(vm,&st) < 0 )
		terror("vmstat failed12");
	if(st.n_busy != 0 || st.s_busy > 0 )
		terror("Wrong statistics12");
	vmclose(vm);

	if(!(vm = vmopen(Vmdcheap,Vmpool,0)) )
		terror("Can't open Vmpool region");
	if(!(addr = vmalloc(vm,13)) )
		terror("vmalloc failed2");
	if(vmstat(vm,&st) < 0 )
		terror("vmstat failed21");
	if(st.n_busy != 1 || st.s_busy != 13 )
		terror("Wrong statistics2");
	if(vmfree(vm,addr) < 0)
		terror("vmfree failed2");
	if(vmstat(vm,&st) < 0 )
		terror("vmstat failed22");
	if(st.n_busy != 0 || st.s_busy > 0 )
		terror("Wrong statistics22");
	vmclose(vm);

	if(!(vm = vmopen(Vmdcheap,Vmlast,0)) )
		terror("Can't open Vmlast region");
	if(!(addr = vmalloc(vm,123)) )
		terror("vmalloc failed3");
	if(vmstat(vm,&st) < 0 )
		terror("vmstat failed31");
	if(st.n_busy != 1 || st.s_busy < 123 )
		terror("Wrong statistics3");
	if(vmfree(vm,addr) < 0)
		terror("vmfree failed3");
	if(vmstat(vm,&st) < 0 )
		terror("vmstat failed32");
	if(st.n_busy != 0 || st.s_busy > 0 )
		terror("Wrong statistics32");
	vmclose(vm);

	if(!(vm = vmopen(Vmdcheap,Vmdebug,0)) )
		terror("Can't open Vmdebug region");
	if(!(addr = vmalloc(vm,123)) )
		terror("vmalloc failed4");
	if(vmstat(vm,&st) < 0 )
		terror("vmstat failed41");
	if(st.n_busy != 1 || st.s_busy != 123 )
		terror("Wrong statistics4");
	if(vmfree(vm,addr) < 0)
		terror("vmfree failed4");
	if(vmstat(vm,&st) < 0 )
		terror("vmstat failed42");
	if(st.n_busy != 0 || st.s_busy > 0 )
		terror("Wrong statistics42");
	vmclose(vm);

	texit(0);
}
