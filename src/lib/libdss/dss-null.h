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
*                 Glenn Fowler <gsf@research.att.com>                  *
*                                                                      *
***********************************************************************/
#pragma prototyped

/*
 * null query
 */

static const char null_usage[] =
"[-1ls5P?\n@(#)$Id: dss null query (AT&T Research) 2002-12-10 $\n]"
USAGE_LICENSE
"[+PLUGIN?\findex\f]"
"[+DESCRIPTION?The \bdss\b \bnull\b query selects all records"
"	but otherwise generates no output.]"
;

static int
null_beg(Cx_t* cx, Cxexpr_t* expr, void* data, Cxdisc_t* disc)
{
	char**	argv = (char**)data;
	int	errors = error_info.errors;

	for (;;)
	{
		switch (optget(argv, null_usage))
		{
		case '?':
			if (disc->errorf)
				(*disc->errorf)(NiL, disc, ERROR_USAGE|4, "%s", opt_info.arg);
			continue;
		case ':':
			if (disc->errorf)
				(*disc->errorf)(NiL, disc, 2, "%s", opt_info.arg);
			continue;
		}
		break;
	}
	if (error_info.errors > errors)
		return -1;
	argv += opt_info.index;
	if (*argv)
	{
		if (disc->errorf)
			(*disc->errorf)(NiL, disc, ERROR_USAGE|4, "%s", optusage(NiL));
		return -1;
	}
	return 0;
}

#define QUERY_null \
	{ \
		"null", \
		"select all records; generate no output", \
		CXH, \
		null_beg, \
		0, \
		0, \
		0 \
	}
