/***********************************************************************
*                                                                      *
*               This software is part of the ast package               *
*          Copyright (c) 1985-2011 AT&T Intellectual Property          *
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
*                  David Korn <dgk@research.att.com>                   *
*                   Phong Vo <kpv@research.att.com>                    *
*                                                                      *
***********************************************************************/
#pragma prototyped

#include "asohdr.h"

#if defined(_UWIN) && defined(_BLD_ast)

NoN(asolock)

#else

int
asolock(unsigned int volatile* lock, unsigned int key, int type)
{
	unsigned int	k;

	if (key)
		switch (type)
		{
		case ASO_UNLOCK:
			return *lock == 0 ? 0 : asocasint(lock, key, 0) == key ? 0 : -1;
		case ASO_TRYLOCK:
			return *lock == key ? 0 : asocasint(lock, 0, key) == 0 ? 0 : -1;
		case ASO_LOCK:
			if (*lock == key)
				return 0;
			/*FALLTHROUGH*/
		case ASO_SPINLOCK:
			for (k = 0; asocasint(lock, 0, key) != 0; ASOLOOP(k));
			return 0;
		}
	return -1;
}

#endif
