########################################################################
#                                                                      #
#               This software is part of the ast package               #
#          Copyright (c) 1989-2012 AT&T Intellectual Property          #
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
#                                                                      #
########################################################################
#
# yes.sh
# Written by David Korn
# AT&T Labs
# Wed May 16 09:23:23 EDT 2007
#
case $(getopts '[-]' opt "--???man" 2>&1) in
version=[0-9]*)
	usage=$'[-?@(#)yes (AT&T Labs Research) 2012-06-06\n]
	'$USAGE_LICENSE$'
	[+NAME?yes - repeatedly out a string until killed]
	[+DESCRIPTION?\byes\b repeatedly writes \astring\a to standard
		output, followed by a \anewline\a character, until it
		is terminated.  If \astring\a is omitted then
		then \by\b is used.]

	[string]

	[+EXIT STATUS?]{
       		 [+0?Success.]
       		 [+>0?An error occurred.]
	}
	'
	;;
*)
	usage=''
	;;
esac

while	getopts "$usage" var
do	case $var in
	esac
done
shift $((OPTIND-1))
string=${@-y}
case $KSH_VERSION in
'')	echo=echo ;;
*)	echo="print -r --" ;;
esac
while	:
do	$echo "$string"
done
