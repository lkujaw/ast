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

#include <ast.h>

#if _lib_execve

NoN(execve)

#else

#include <sig.h>
#include <wait.h>
#include <error.h>

static pid_t		childpid;

static void
execsig(int sig)
{
	kill(childpid, sig);
	signal(sig, execsig);
}

#if defined(__EXPORT__)
#define extern	__EXPORT__
#endif

extern int
execve(const char* path, char* const argv[], char* const arge[])
{
	int	status;

	if ((childpid = spawnve(path, argv, arge)) < 0)
		return(-1);
	for (status = 0; status < 64; status++)
		signal(status, execsig);
	while (waitpid(childpid, &status, 0) == -1)
		if (errno != EINTR) return(-1);
	if (WIFSIGNALED(status))
	{
		signal(WTERMSIG(status), SIG_DFL);
		kill(getpid(), WTERMSIG(status));
		pause();
	}
	else status = WEXITSTATUS(status);
	exit(status);
}

#endif
