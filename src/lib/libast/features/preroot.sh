########################################################################
#                                                                      #
#               This software is part of the ast package               #
#          Copyright (c) 1985-2011 AT&T Intellectual Property          #
#                      and is licensed under the                       #
#                 Eclipse Public License, Version 2.0                  #
#                    by AT&T Intellectual Property                     #
#                                                                      #
#                A copy of the License is available at                 #
#      https://www.eclipse.org/org/documents/epl-2.0/EPL-2.0.html      #
#         (with md5 checksum 84283fa8859daf213bdda5a9f8d1be1d)         #
#                                                                      #
#              Information and Software Systems Research               #
#                            AT&T Research                             #
#                           Florham Park NJ                            #
#                                                                      #
#                 Glenn Fowler <gsf@research.att.com>                  #
#                  David Korn <dgk@research.att.com>                   #
#                   Phong Vo <kpv@research.att.com>                    #
#                                                                      #
########################################################################
: generate preroot features
case $# in
0)	;;
*)	eval $1
	shift
	;;
esac
if	/etc/preroot / /bin/echo >/dev/null
then	cat <<!
#pragma prototyped

#define FS_PREROOT	1			/* preroot enabled	*/
#define PR_BASE		"CCS"			/* preroot base env var	*/
#define PR_COMMAND	"/etc/preroot"		/* the preroot command	*/
#define PR_REAL		"/dev/.."		/* real root pathname	*/
#define PR_SILENT	"CCSQUIET"		/* no command trace	*/

extern char*		getpreroot(char*, const char*);
extern int		ispreroot(const char*);
extern int		realopen(const char*, int, int);
extern void		setpreroot(char**, const char*);

!
else	echo "/* preroot not enabled */"
fi
