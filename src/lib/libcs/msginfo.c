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
#pragma prototyped

/*
 * system call message data initialization
 */

#include "msglib.h"

Msg_info_t	msg_info =
{
	MSG_TIMEOUT,
	0,
	{
	"NOP",
	"break",	"chmod",	"chown",	"close",
	"control",	"dup",		"exec",		"exit",
	"fork",		"getdents",	"kill",		"link",
	"lock",		"mkdir",	"mknod",	"mount",
	"open",		"pathconf",	"pipe",		"read",
	"remove",	"rename",	"rmdir",	"seek",
	"stat",		"statfs",	"sync",		"truncate",
	"utime",	"wait",		"write",
	}
};
