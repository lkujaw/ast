########################################################################
#                                                                      #
#               This software is part of the ast package               #
#          Copyright (c) 1990-2011 AT&T Intellectual Property          #
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
:
#
# Glenn Fowler
# AT&T Bell Laboratories
#
# Bourne coshell support
#
# @(#)ignore (AT&T Bell Laboratories) 08/11/92
#
while	:
do	case $# in
	0)	exit 0 ;;
	esac
	case $1 in
	*=*)	case $RANDOM in
		$RANDOM)`echo $1 | sed "s/\\([^=]*\\)=\\(.*\\)/eval \\1='\\2'; export \\1/"` ;;
		*)	export "$1" ;;
		esac
		shift
		;;
	*)	break
		;;
	esac
done
"$@"
exit 0
