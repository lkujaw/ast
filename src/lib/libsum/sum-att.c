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
*                 Glenn Fowler <gsf@research.att.com>                  *
*                                                                      *
***********************************************************************/
#pragma prototyped

/*
 * att
 */

#define att_description	\
	"The system 5 release 4 checksum. This is the default for \bsum\b \
	when \bgetconf UNIVERSE\b is \batt\b. This is the only true sum; \
	all of the other methods are order dependent."
#define att_options	0
#define att_match	"att|sys5|s5|default"
#define att_open	long_open
#define att_init	long_init
#define att_print	long_print
#define att_data	long_data
#define att_scale	512

static int
att_block(register Sum_t* p, const void* s, size_t n)
{
	register uint32_t	c = ((Integral_t*)p)->sum;
	register unsigned char*	b = (unsigned char*)s;
	register unsigned char*	e = b + n;

	while (b < e)
		c += *b++;
	((Integral_t*)p)->sum = c;
	return 0;
}

static int
att_done(Sum_t* p)
{
	register uint32_t	c = ((Integral_t*)p)->sum;

	c = (c & 0xffff) + ((c >> 16) & 0xffff);
	c = (c & 0xffff) + (c >> 16);
	((Integral_t*)p)->sum = c & 0xffff;
	return short_done(p);
}
