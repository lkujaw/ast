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
#include	"dttest.h"

Dtdisc_t Disc =
	{ 0, sizeof(long), -1,
	  newint, NIL(Dtfree_f), compare, hashint,
	  NIL(Dtmemory_f), NIL(Dtevent_f)
	};

tmain()
{
	Dt_t*		dt;
	long		i, k;

	/* testing Dtdeque */
	if(!(dt = dtopen(&Disc,Dtdeque)) )
		terror("dtopen deque");
	if((long)dtinsert(dt,3L) != 3)
		terror("Dtdeque insert 3");
	if((long)dtappend(dt,4L) != 4)
		terror("Dtdeque append 4");
	if((long)dtinsert(dt,2L) != 2)
		terror("Dtdeque insert 2");
	if((long)dtappend(dt,5L) != 5)
		terror("Dtdeque append 5");
	if((long)dtinsert(dt,1L) != 1)
		terror("Dtdeque insert 1");
	if((long)dtappend(dt,6L) != 6)
		terror("Dtdeque append 6");

	for(k = 1, i = (long)dtfirst(dt); i != 0; i = (long)dtnext(dt,i), k += 1)
		if(i != k)
			terror("Unmatched elements");
	if(k != 7)
		terror("Bad element count");

	texit(0);
}
