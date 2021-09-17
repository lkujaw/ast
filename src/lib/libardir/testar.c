/***********************************************************************
*                                                                      *
*               This software is part of the ast package               *
*          Copyright (c) 2002-2011 AT&T Intellectual Property          *
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
*               Glenn Fowler <glenn.s.fowler@gmail.com>                *
*                    David Korn <dgkorn@gmail.com>                     *
*                                                                      *
***********************************************************************/
#include <ast.h>
#include <ardir.h>
#include <error.h>

main(int argc, char** argv)
{
	Ardir_t*	dir;
	Ardirent_t*	ent;
	long		touch;
	char*		file;

	touch = 0;
	while (file = *++argv)
	{
		if (!strcmp(file, "-t") && *(argv + 1))
			touch = strtol(*++argv, NiL, 0);
		else if (dir = ardiropen(file, NiL, touch ? ARDIR_UPDATE : 0))
		{
			sfprintf(sfstdout, "%s: type=%s truncate=%d%s\n", file, dir->meth->name, dir->truncate, (dir->flags & ARDIR_RANLIB) ? " ranlib" : "");
			while (ent = ardirnext(dir))
			{
				if (touch)
				{
					ent->mtime = touch;
					ardirchange(dir, ent);
					sfprintf(sfstdout, "touch %s\n", ent->name);
				}
				else
					sfprintf(sfstdout, "%s %8u %8u %8llu %8llu %s %s\n", fmtmode(ent->mode, 1), ent->uid, ent->gid, ent->size, ent->offset, fmttime("%k", ent->mtime), ent->name);
			}
			if (ardirclose(dir))
				error(2, "%s: archive read error", file);
		}
		else
			error(ERROR_SYSTEM|2, "%s: not an archive", file);
	}
	return 0;
}
