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
: we do that too
ls 	-D header='%(dir.count:case:[01]::*:\n)s Directory of %(path)s\n' \
	-D meridian='%(mtime:time=%p)s' \
	-D trailer='%9(dir.files)lu file(s) %10(dir.bytes)lu bytes\n' \
	-Z '%-8.8(name:edit:\\([^.]*\\).*:\\1:u)s %3.3(name:edit:[^.]*\\.*\\(.*\\):\\1:u)s %5(mode:case:d*:<DIR>:l*:<LNK>:*x*:<EXE>)s%7(size)lu %(mtime:time=%m-%d-%y  %I:%M)s%(meridian:edit:\\(.\\).*:\\1:l)s' \
	"$@"
