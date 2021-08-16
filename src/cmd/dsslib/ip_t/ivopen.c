/***********************************************************************
*                                                                      *
*               This software is part of the ast package               *
*          Copyright (c) 2000-2011 AT&T Intellectual Property          *
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
*                   Phong Vo <kpv@research.att.com>                    *
*                                                                      *
***********************************************************************/
#pragma prototyped

#include "ivlib.h"

Iv_t*
ivopen(Ivdisc_t* disc, Ivmeth_t* meth, int size, const char* options)
{
	Iv_t*		iv;

	if (!disc || !meth || !(iv = newof(0, Iv_t, 1, 3 * size)))
		return 0;
	iv->disc = disc;
	iv->meth = meth;
	iv->data = 0;
	iv->unit = (unsigned char*)(iv + 1);
	fvset(size, iv->unit, 1);
	iv->r1 = iv->unit + size;
	iv->r2 = iv->r1 + size;
	iv->size = size;
	if (meth->eventf && (*meth->eventf)(iv, IV_OPEN, (void*)options) < 0)
	{	
		free(iv);
		return 0;
	}
	return iv;
}
