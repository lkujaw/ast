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
#include "rshdr.h"

/*
 * announce sp open for write on path
 */

#if __STD_C
int rsfilewrite(Rs_t* rs, Sfio_t* sp, const char* path)
#else
int rsfilewrite(rs, sp, path)
Rs_t*	rs;
Sfio_t*	sp;
char*	path;
#endif
{
	if ((rs->events & RS_FILE_WRITE) && rsnotify(rs, RS_FILE_WRITE, sp, (Void_t*)path, rs->disc) < 0)
		return -1;
	return 0;
}

/*
 * announce sp open for read on path
 */

#if __STD_C
int rsfileread(Rs_t* rs, Sfio_t* sp, const char* path)
#else
int rsfileread(rs, sp, path)
Rs_t*	rs;
Sfio_t*	sp;
char*	path;
#endif
{
	if ((rs->events & RS_FILE_READ) && rsnotify(rs, RS_FILE_READ, sp, (Void_t*)path, rs->disc) < 0)
		return -1;
	return 0;
}

/*
 * close file stream
 */

#if __STD_C
int rsfileclose(Rs_t* rs, Sfio_t* sp)
#else
int rsfileclose(rs, sp)
Rs_t*	rs;
Sfio_t*	sp;
#endif
{
	int	n;

	if (rs->events & RS_FILE_CLOSE)
	{
		if ((n = rsnotify(rs, RS_FILE_CLOSE, sp, (Void_t*)0, rs->disc)) < 0)
			return -1;
		if (n)
			return 0;
	}
	if (sp != sfstdout)
		return sfclose(sp);
	return 0;
}
