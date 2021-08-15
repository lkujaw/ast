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
#include "vcs_rscs.h"

struct rfile_t
{
	char*		path;
	Sfio_t*	fd;
	attr_t*		ap;
	rdirent_t*	list;
};

typedef struct rfile_t	rfile_t;

struct version_t
{
	char*		version;
	char*		path;
	int		domain;
	Sfio_t*	fd;
	tag_t*		tp;
};

typedef struct version_t version_t;
#define RSCS_DIR	"RSCS"		/* or "..." inside 3d */
