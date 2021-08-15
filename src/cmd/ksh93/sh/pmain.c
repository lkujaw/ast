/***********************************************************************
*                                                                      *
*               This software is part of the ast package               *
*          Copyright (c) 1982-2011 AT&T Intellectual Property          *
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
*                  David Korn <dgk@research.att.com>                   *
*                                                                      *
***********************************************************************/
#pragma prototyped

#include	<shell.h>

#include	"FEATURE/externs"

#if defined(__sun) && _sys_mman && _lib_memcntl && defined(MHA_MAPSIZE_STACK) && defined(MC_HAT_ADVISE)
#   undef	VM_FLAGS	/* solaris vs vmalloc.h symbol clash */
#   include	<sys/mman.h>
#else
#   undef	_lib_memcntl
#endif

typedef int (*Shnote_f)(int, long, int);

int main(int argc, char *argv[])
{
#if _lib_memcntl
	/* advise larger stack size */
	struct memcntl_mha mha;
	mha.mha_cmd = MHA_MAPSIZE_STACK;
	mha.mha_flags = 0;
	mha.mha_pagesize = 64 * 1024;
	(void)memcntl(NULL, 0, MC_HAT_ADVISE, (caddr_t)&mha, 0, 0);
#endif
	return(sh_main(argc, argv, (Shinit_f)0));
}
