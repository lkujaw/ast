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

	/* testing Dtstack */
	if(!(dt = dtopen(&Disc,Dtstack)) )
		terror("dtopen stack");
	if((long)dtinsert(dt,1L) != 1)
		terror("Dtstack insert 1");
	if((long)dtinsert(dt,3L) != 3)
		terror("Dtstack insert 3.1");
	if((long)dtinsert(dt,2L) != 2)
		terror("Dtstack insert 2.1");
	if((long)dtinsert(dt,3L) != 3)
		terror("Dtstack insert 3.2");
	if((long)dtinsert(dt,2L) != 2)
		terror("Dtstack insert 2.2");
	if((long)dtinsert(dt,3L) != 3)
		terror("Dtstack insert 3.3");

	if((long)dtlast(dt) != 1)
		terror("Dtstack dtlast");
	if((long)dtprev(dt,1L) != 3)
		terror("Dtstack dtprev 1");
	if((long)dtprev(dt,3L) != 2)
		terror("Dtstack dtprev 3.1");
	if((long)dtprev(dt,2L) != 3)
		terror("Dtstack dtprev 2.1");
	if((long)dtprev(dt,3L) != 2)
		terror("Dtstack dtprev 3.2");
	if((long)dtprev(dt,2L) != 3)
		terror("Dtstack dtprev 2.2");
	if((long)dtprev(dt,3L) != 0)
		terror("Dtstack dtprev 3.2");

	if((long)dtdelete(dt,NIL(Void_t*)) != 3)
		terror("Dtstack pop 3.3");

	/* search to one of the 3 */
	if((long)dtsearch(dt,3L) != 3)
		terror("Dtstack search 3.2");
	if((long)dtdelete(dt,3L) != 3)
		terror("Dtstack delete 3.2");

	if((long)dtdelete(dt,NIL(Void_t*)) != 2)
		terror("Dtstack pop 2.2");
	if((long)dtdelete(dt,NIL(Void_t*)) != 2)
		terror("Dtstack pop 2.1");
	if((long)dtdelete(dt,NIL(Void_t*)) != 3)
		terror("Dtstack pop 3.1");
	if((long)dtdelete(dt,NIL(Void_t*)) != 1)
		terror("Dtstack pop 1");

	if(dtsize(dt) != 0)
		terror("Dtstack size");

	texit(0);
}
