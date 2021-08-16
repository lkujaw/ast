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
#include	"sftest.h"

tmain()
{
	Sfio_t*	ip;
	Sfio_t*	op;
	int	n;

	if(!(ip = sfopen((Sfio_t*)0, "/dev/null", "r")))
		terror("/dev/null read open");
	if(!(op = sfopen((Sfio_t*)0, tstfile("sf", 0), "w")))
		terror("Write open");

	n = (int)sfmove(ip, op, SF_UNBOUND, -1);

	if(n)
		terror("move count %d != 0", n);
	if(!sfeof(ip))
		terror("sfeof(ip) expected");
	if(sfeof(op))
		terror("sfeof(op) not expected");

	if(sferror(ip))
		terror("sferror(ip) not expected");
	if(sferror(op))
		terror("sferror(op) not expected");

	if(sfclose(ip))
		terror("sfclose(ip)");
	if(sfclose(op))
		terror("sfclose(op)");

	texit(0);
}
