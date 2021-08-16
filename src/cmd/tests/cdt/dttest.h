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
#include	"cdt.h"
#include	"terror.h"

#if __STD_C
static int compare(Dt_t* dt, Void_t* o1, Void_t* o2, Dtdisc_t* disc)
#else
static int compare(dt,o1,o2,disc)
Dt_t*		dt;
Void_t*		o1;
Void_t*		o2;
Dtdisc_t*	disc;
#endif
{
	return (int)((char*)o1 - (char*)o2);
}

#if __STD_C
static int rcompare(Dt_t* dt, Void_t* o1, Void_t* o2, Dtdisc_t* disc)
#else
static int rcompare(dt,o1,o2,disc)
Dt_t*		dt;
Void_t*		o1;
Void_t*		o2;
Dtdisc_t*	disc;
#endif
{
	return (int)((char*)o2 - (char*)o1);
}

#if __STD_C
static Void_t* newint(Dt_t* dt, Void_t* o, Dtdisc_t* disc)
#else
static Void_t* newint(dt,o,disc)
Dt_t*		dt;
Void_t*		o;
Dtdisc_t*	disc;
#endif
{
	return o;
}

#if __STD_C
static unsigned int hashint(Dt_t* dt, Void_t* o, Dtdisc_t* disc)
#else
static unsigned int hashint(dt,o,disc)
Dt_t*		dt;
Void_t*		o;
Dtdisc_t*	disc;
#endif
{
	return (unsigned int)((char*)o - (char*)0);
}
