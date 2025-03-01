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
: self extracting archive generator for ratz

COMMAND=sear

args=
cc="ncc -O -Y-Os"
cmd="dir"
dyn=-D_DLL
ico=
opt=
out=install.exe
src=

case `(getopts '[-][123:xyz]' opt --xyz; echo 0$opt) 2>/dev/null` in
0123)	ARGV0="-a $COMMAND"
	USAGE=$'
[-?
@(#)$Id: sear (AT&T Labs Research) 2011-03-04 $
]
'$USAGE_LICENSE$'
[+NAME?sear - generate a win32 ratz self extracting archive]
[+DESCRIPTION?\bsear\b generates a win32 self extracting archive that
    can be used to install win32 files and applications. \bpax\b(1) is used
    to generate a \btgz\b (\btar\b(1) \bgzip\b(1)) archive from the
    \afile\a operands that is appended to the self extracting archive. If
    no \afile\a operands are specified then the standard input is read.
    \bpax\b(1) options (like \b--verbose\b) may be specified after a \b--\b
    operand but before the first \afile\a operand.]
[+?When the self extracting archive is executed it creates a temporary
    directory and unpacks each \afile\a. If \b--command\b=\acommand\a was
    specified when the archive was generated then \acommand\a is executed
    by \bCMD.EXE\b. The temporary directory is then removed.]
[+?\b.exe\b files generated by \bsear\b(1) are fully functional
    \bratz\b(1) executables, so any \bratz\b option may be used on a
    \bsear\b file. This allows \bsear\b file contents to be examined and
    extracted without executing any embedded installation scripts.]
[a:args|arguments?The arguments appended to the \bCMD.EXE\b command
    string after the runtime sear operands are appended.]:[args]
[b:bootstrap?Bootstrap-sepcific link.]
[c:cc?The C compiler command and flags are set to \acc\a.]:[cc:='$cc$']
[i:icon?The resource icon is set to \aicon\a. The default is a 32 or 64
    bit icon.]:[icon:=$INSTALLROOT/lib/sear/sear??.ico]
[m:meter?Set the \bratz\b(1) \b--meter\b option when the archive is
    extracted.]
[o:output?The self extracting file name is \afile\a.]:[file:='$out$']
[r:ratz?The \bratz\b(1) source file is set to
    \apath\a.]:[path:=$INSTALLROOT/lib/sear/ratz.c]
[x:command?The \bCMD.EXE\b command string to run after the top level
    files have been read into the temporary directory.]:[command:='$cmd$']
[v:verbose?Set the \bratz\b(1) \b--verbose\b option when the archive is
    extracted.]

[ -- pax-options ] [ file ] ...

[+EXIT STATUS?]{
	[+0?Success.]
	[+>0?An error occurred.]
}
[+SEE ALSO?\bratz\b(1), \bgunzip\b(1), \bpax\b(1), \bCMD.EXE\b(m$)]
'
	;;
*)	ARGV0=""
	USAGE="c:[command]i:[icon]o:[output]r:[ratz-src] [ file ] ..."
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
	a)	args=-D_SEAR_ARGS="\"$OPTARG\""
		;;
	b)	dyn=
		;;
	c)	cc=$OPTARG
		;;
	i)	ico=$OPTARG
		;;
	m)	opt=${opt}m
		;;
	o)	out=$OPTARG
		[[ ${out##*/} != *.?* ]] && out=${out%.}.exe
		;;
	r)	src=$OPTARG
		;;
	x)	cmd=$OPTARG
		;;
	v)	opt=${opt}v
		;;
	*)	usage
		;;
	esac
done
shift $((OPTIND-1))

if	[[ ! $src ]]
then	f=ratz.c
	src=$(dirname -r lib/$COMMAND/$f)
	if	[[ ! $src ]]
	then	echo "$COMMAND: $f: cannot locate ratz source" >&2
		exit 1
	fi
elif	[[ ! -f $src ]]
then	echo "$COMMAND: $src: cannot read ratz source" >&2
	exit 1
fi
if	[[ ! $ico ]]
then	w=$(uname -i 2>/dev/null)
	w=${w%/*}
	[[ $w == 32 || $w == 64 ]] || w=
	f=sear$w.ico
	ico=$(dirname -r lib/$COMMAND/$f)
	if	[[ ! $ico ]]
	then	echo "$COMMAND: $f: cannot locate icon source" >&2
		exit 1
	fi
elif	[[ ! -f $ico ]]
then	echo "$COMMAND: $ico: cannot read icon" >&2
	exit 1
fi
[[ $opt ]] && cc="$cc -D_SEAR_OPTS=\"-$opt\""
cc="$cc $dyn"

tmp=/tmp/sear$$
obj=${src##*/}
obj=${obj%.*}.o
trap 'rm -f "$obj" $tmp.*' 0 1 2 3
res=$tmp.res
libs=-ladvapi32
typeset -H host_ico=$ico host_rc=$tmp.rc host_res=$tmp.res
print -r "sear ICON \"${host_ico//\\/\\\\}\"" > $tmp.rc
if	! rc -x -r -fo"$host_res" "$host_rc"
then	exit 1
fi
if	! $cc -D_SEAR_SEEK=0 -D_SEAR_EXEC="\"$cmd\"" "$args" -c "$src" ||
	! ${cc/-Bstatic/} --mt-output="$out.manifest" --mt-name="${out%.*}" --mt-administrator -o "$out" "$obj" "$res" $libs
then	exit 1
fi
if	[[ -f "$out.manifest" ]]
then	mv "$out.manifest" "${out%.*}.manifest"
	ed - "${out%.*}.manifest" <<-'!'
	/<dependency>/,/<\/dependency>/d
	w
	q
	!
	if	! $cc --mt-input="${out%.*}.manifest" -o "$out" "$obj" "$res" $libs
	then	exit 1
	fi
	mt="--mt-input=${out%.*}.manifest --mt-delete"
else	mt=
fi
size=$(wc -c < "$out")
if	! $cc -D_SEAR_SEEK=$(($size)) -D_SEAR_EXEC="\"$cmd\"" "$args" -c "$src" ||
	! $cc $mt -o "$out" "$obj" "$res" $libs
then	exit 1
fi
if	[[ -f "$out.manifest" ]]
then	rm -f "$out.manifest"
fi
files=0
pax -x tgz -w "$@" >> "$out"
