########################################################################
#                                                                      #
#               This software is part of the ast package               #
#          Copyright (c) 1989-2011 AT&T Intellectual Property          #
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
: convert MAM dependency info to dag input

COMMAND=mamdag
case `(getopts '[-][123:xyz]' opt --xyz; echo 0$opt) 2>/dev/null` in
0123)	ARGV0="-a $COMMAND"
	USAGE=$'
[-?
@(#)$Id: mamdag (AT&T Labs Research) 1998-04-01 $
]
'$USAGE_LICENSE$'
[+NAME?mamdag - make abstract machine to dag dependency graph conversion filter]
[+DESCRIPTION?\bmamdag\b reads MAM (Make Abstract Machine) target and
	prerequisite file descriptions from the standard input and writes a
	\bdag\b(1) description of the dependency graph on the standard output.
	Mamfiles are generated by the \b--mam\b option of \bnmake\b(1) and
	\bgmake\b(1).]
[+?\bdag\b(1) is an obsolete predecessor to \bdot\b(1); new applications should
	use \bmamdot\b(1) and \bdot\b(1).]
[+SEE ALSO?\bdag\b(1), \bdot\b(1), \bmamdot\b(1), \bgmake\b(1), \bnmake\b(1)]
'
	;;
*)	ARGV0=""
	USAGE=""
	;;
esac

usage()
{
	OPTIND=0
	getopts $ARGV0 "$USAGE" OPT '-?'
	exit 2
}

while	getopts $ARGV0 "$USAGE" OPT
do	case $OPT in
	*)	usage
		;;
	esac
done

integer level=0 line=0
list[0]=all
print .GR 7.50 10.0
print draw nodes as Box ';'
while	read op arg arg2 argx
do	line=line+1
	case $op in
	[0-9]*)	op=$arg
		arg=$arg2
		arg2=$arg3
		arg3=$argx
		argx=
		;;
	esac
	case $op in
	make)	case " ${list[level]} " in
		*" \"$arg\" "*)	;;
		*)		list[level]="${list[level]} \"$arg\"" ;;
		esac
		level=level+1
		list[level]=\"$arg\"
		;;
	prev)	case " ${list[level]} " in
		*" \"$arg\" "*)	;;
		*)		list[level]="${list[level]} \"$arg\"" ;;
		esac
		;;
	done)	case ${list[level]} in
		*' '*)	print ${list[level]} ';'
		esac
		if	(( level <= 0 ))
		then	print -u2 "$COMMAND: line $line: $op $arg: no matching make op"
		else	level=level-1
		fi
		;;
	esac
done
print .GE
