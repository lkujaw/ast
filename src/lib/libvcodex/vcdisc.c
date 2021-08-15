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
*                                                                      *
***********************************************************************/
#include	"vchdr.h"

/*	Change the discipline for a Vcodex_t handle.
**
**	Written by Kiem-Phong Vo (kpv@research.att.com)
*/

#if __STD_C
Vcdisc_t* vcdisc(Vcodex_t* vc, Vcdisc_t* disc)
#else
Vcdisc_t* vcdisc(vc, disc)
Vcodex_t*	vc;
Vcdisc_t*	disc;
#endif
{
	Vcdisc_t	*old = vc->disc;
	int		rv;

	if(!vc)
		return NIL(Vcdisc_t*);

	/* check with incumbent to see if it's ok with the change */
	if(old && old->eventf &&
	   (*old->eventf)(vc, VC_DISC, (Void_t*)disc, old) < 0 )
		return NIL(Vcdisc_t*);

	/* now announce to method */
	if(!vc->meth || !vc->meth->eventf)
		rv = 0;
	else	rv = (*vc->meth->eventf)(vc, VC_DISC, (Void_t*)disc);

	if(rv < 0)
		return NIL(Vcdisc_t*);
	else if(rv == 0) /* install discipline */
	{	vc->disc = disc;
		return old ? old : disc;
	}
	else	return disc;
}
