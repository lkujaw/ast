/***********************************************************************
*                                                                      *
*               This software is part of the ast package               *
*          Copyright (c) 1987-2012 AT&T Intellectual Property          *
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
 * pax bzip format
 */

#include "format.h"

static int
bzip_getprologue(Pax_t* pax, Format_t* fp, Archive_t* ap, File_t* f, unsigned char* buf, size_t size)
{
	if (size < 3 || buf[0] != 0x42 || buf[1] != 0x5a || buf[2] != 0x68)
		return 0;
	ap->uncompressed = ap->io->size * 7;
	return 1;
}

static Compress_format_t	pax_bzip_data =
{
	0,
	{ "bunzip2" },
	{ 0 },
};

Format_t	pax_bzip_format =
{
	"bzip",
	"bzip2|bz",
	"bzip compression",
	0,
	COMPRESS|IN|OUT,
	0,
	0,
	0,
	PAXNEXT(bzip),
	&pax_bzip_data,
	0,
	bzip_getprologue,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0
};

PAXLIB(bzip)
