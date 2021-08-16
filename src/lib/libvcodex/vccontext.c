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

/*	If a method carries states across vcapply() calls, it needs to
**	provide a way so that the invoker can set multiple contexts for
**	transforming data. The below functions create/delete context.
**
**	Written by Kiem-Phong Vo (kpv@research.att.com)
*/

#if __STD_C
Vccontext_t* vcinitcontext(Vcodex_t* vc, Vccontext_t* ctxt)
#else
Vccontext_t* vcinitcontext(vc, ctxt)
Vcodex_t*	vc;
Vccontext_t*	ctxt;	/* if NULL, make a new one */
#endif
{
	Vccontext_t	*c, *p;

	if(ctxt)
	{	for(p = NIL(Vccontext_t*), c = vc->ctxt; c; p = c, c = c->next)
			if(c == ctxt)
				break;
		if(!c) /* non-existing context */
			return NIL(Vccontext_t*);
		if(!p) /* already at head of list */
			return ctxt;
		else	p->next = ctxt->next;
	}
	else
	{	if(!vc->meth->eventf ||
		   (*vc->meth->eventf)(vc, VC_INITCONTEXT, (Void_t*)(&ctxt)) < 0 || !ctxt)
			return NIL(Vccontext_t*);
	}

	ctxt->next = vc->ctxt;
	vc->ctxt = ctxt;
	return ctxt;
}

#if __STD_C
int vcfreecontext(Vcodex_t* vc, Vccontext_t* ctxt)
#else
int vcfreecontext(vc, ctxt)
Vcodex_t*	vc;
Vccontext_t*	ctxt; /* if NULL, free all */
#endif
{
	Vccontext_t	*next;

	if(ctxt)
	{	if(vcinitcontext(vc, ctxt) != ctxt)
			return -1;
		vc->ctxt = ctxt->next;
		ctxt->next = NIL(Vccontext_t*);
	}
	else
	{	ctxt = vc->ctxt;
		vc->ctxt = NIL(Vccontext_t*);
	}

	for(; ctxt; ctxt = next)
	{	next = ctxt->next;
		if(vc->meth->eventf &&
		   (*vc->meth->eventf)(vc, VC_FREECONTEXT, (Void_t*)ctxt) < 0)
			return -1;
	}

	return 0;
}
