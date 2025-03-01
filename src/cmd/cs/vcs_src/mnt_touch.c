/***********************************************************************
*                                                                      *
*               This software is part of the ast package               *
*          Copyright (c) 1990-2011 AT&T Intellectual Property          *
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
#include "mnt_imount.h"

#define USAGE	"rm file ... # remove cached files"

int im_touch_help(s)
	char*	s;
{
	printf("\t%s\n", USAGE);
	return (0);
}

int im_touch(argc, argv)
	int		argc;
	register char**	argv;
{	
	register int	n;
	register char*	s;
	int		fd;
	
	error_info.id = argv[0];
	opt_info.index = 1;
	while (n = optget(argv, "s:[server] "))
	 switch (n)
	{
	case 's':
		s = opt_info.arg;
		if ((fd = csopen(s, CS_OPEN_READ)) < 0)
		{
			printf("cannot connect cs server %s\n", s);
			return (-1);
		}
		istate.cs_svc = strdup(s);
		istate.fd = fd;
		break;
	case '?':
	case ':':
		printf(USAGE);
		return (1);
	}
	
	argc -= opt_info.index;
	argv += opt_info.index;
	
	while(argc > 0)
	{
		s = *argv;
		unlink(s);
		argc--;
		argv++;
	}
	return (0);
}


