/***********************************************************************
*                                                                      *
*               This software is part of the ast package               *
*          Copyright (c) 1996-2011 AT&T Intellectual Property          *
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
#include	"rskeyhdr.h"

/*	Opening sorting contexts
**
**	Written by Kiem-Phong Vo (07/08/96)
*/

static const char id[] = "\n@(#)$Id: recsort library (AT&T Research) 2011-10-11 $\0\n";

#if __STD_C
Rs_t* rsnew(Rsdisc_t* disc)
#else
Rs_t* rsnew(disc)
Rsdisc_t*	disc;	/* discipline describing record types	*/
#endif
{
	reg Rs_t*	rs;

	if(rs = (Rs_t*)vmresize(Vmheap,NIL(Void_t*),sizeof(Rs_t),VM_RSZERO))
		rsdisc(rs,disc,RS_DISC);
	return rs;
}

#if __STD_C
int rsinit(reg Rs_t* rs, Rsmethod_t* meth, ssize_t c_max, int type, Rskey_t* key)
#else
int rsinit(rs, meth, c_max, type, key)
Rs_t*		rs;	/* handle from rsnew()			*/
Rsmethod_t*	meth;	/* sorting method			*/
ssize_t		c_max;	/* process about this much per chain	*/
int		type;	/* sort controls			*/
Rskey_t*	key;	/* key coder state			*/
#endif
{
	Rsdisc_t*	disc;
	ssize_t		round;

	if((round = c_max) > 0)
		round /= 4;
	rs->vmdisc.memoryf = Vmdcheap->memoryf;
	rs->vmdisc.exceptf = Vmdcheap->exceptf;
	if(!(rs->vm = (Vmalloc_t*)vmopen(&rs->vmdisc, Vmbest, 0)) )
	{	vmfree(Vmheap,(void*)rs);
		return -1;
	}
	rs->vmdisc.round = round <= 0 ? RS_RESERVE : round;
	if(!(rs->vm = (Vmalloc_t*)vmopen(&rs->vmdisc, Vmbest, 0)) )
	{	vmfree(Vmheap,(void*)rs);
		return -1;
	}

	if(!(rs->methdata = (Void_t*)vmresize(Vmheap,NIL(Void_t*),meth->size,VM_RSZERO)) )
		goto bad;

	rs->meth = meth;
	rs->c_max = c_max;
	rs->type = rs->disc->type | (type&RS_TYPES);
	rs->key = rs->disc->version < 20111011L ? (Rskey_t*)((char*)rs->disc - sizeof(Rskey_t)) : key;

	rs->events = 0;
	for (disc = rs->disc; disc; disc = disc->disc)
		rs->events |= disc->events;

	if (RSNOTIFY(rs, RS_OPEN, 0, 0, rs->disc) < 0)
		goto bad;

	return 0;
 bad:
	vmclose(rs->vm);
	vmfree(Vmheap,rs);
	return -1;
}

#if __STD_C
Rs_t* rsopen(Rsdisc_t* disc, Rsmethod_t* meth, ssize_t c_max, int type)
#else
Rs_t* rsopen(disc, meth, c_max, type)
Rsdisc_t*	disc;	/* discipline describing record types	*/
Rsmethod_t*	meth;	/* sorting method			*/
ssize_t		c_max;	/* process about this much per chain	*/
int		type;	/* sort controls			*/
#endif
{
	reg Rs_t*	rs;

	if((rs = rsnew(disc)) && rsinit(rs, meth, c_max, type, NiL))
	{	vmclose(rs->vm);
		vmfree(Vmheap,rs);
		rs = 0;
	}
	return rs;
}
