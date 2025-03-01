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

/*
 * Glenn Fowler
 * AT&T Bell Laboratories
 *
 * return fs type string given stat
 */

#include <ast.h>
#include <ls.h>
#include <mnt.h>

#include "FEATURE/fs"

#if _str_st_fstype

char*
fmtfs(struct stat* st)
{
	return st->st_fstype;
}

#else

#include <cdt.h>

typedef struct Id_s
{
	Dtlink_t	link;
	dev_t		id;
	char		name[1];
} Id_t;

char*
fmtfs(struct stat* st)
{
	register Id_t*		ip;
	register void*		mp;
	register Mnt_t*		mnt;
	register char*		s;
	struct stat		rt;
	char*			buf;

	static Dt_t*		dict;
	static Dtdisc_t		disc;

	if (!dict)
	{
		disc.key = offsetof(Id_t, id);
		disc.size = sizeof(dev_t);
		dict = dtopen(&disc, Dtset);
	}
	else if (ip = (Id_t*)dtmatch(dict, &st->st_dev))
		return ip->name;
	s = FS_default;
	if (mp = mntopen(NiL, "r"))
	{
		while ((mnt = mntread(mp)) && (stat(mnt->dir, &rt) || rt.st_dev != st->st_dev));
		if (mnt && mnt->type)
			s = mnt->type;
	}
	if (!dict || !(ip = newof(0, Id_t, 1, strlen(s))))
	{
		if (!mp)
			return s;
		buf = fmtbuf(strlen(s) + 1);
		strcpy(buf, s);
		mntclose(mp);
		return buf;
	}
	strcpy(ip->name, s);
	if (mp)
		mntclose(mp);
	dtinsert(dict, ip);
	return ip->name;
}

#endif
