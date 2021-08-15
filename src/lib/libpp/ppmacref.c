/***********************************************************************
*                                                                      *
*               This software is part of the ast package               *
*          Copyright (c) 1986-2011 AT&T Intellectual Property          *
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
 * Glenn Fowler
 * AT&T Research
 *
 * common preprocessor macro reference handler
 */

#include "pplib.h"

void
ppmacref(struct ppsymbol* sym, char* file, int line, int type, unsigned long sum)
{
	register char*	p;

	NoP(file);
	NoP(line);
	p = (pp.state & (DIRECTIVE|JOINING)) == DIRECTIVE ? pp.outp : pp.addp;
	p += sfsprintf(p, MAXTOKEN, "\n#%s %d", pp.lineid, error_info.line);
	p += sfsprintf(p, MAXTOKEN, "\n#%s %s:%s %s %d", dirname(PRAGMA), pp.pass, keyname(X_MACREF), sym->name, type);
	if (type > 0)
	{
		if (sym->macro && sym->macro->value)
			sum = strsum(sym->macro->value, (long)sym->macro->arity);
		p += sfsprintf(p, MAXTOKEN, " %lu", sum);
	}
	if ((pp.state & (DIRECTIVE|JOINING)) == DIRECTIVE)
	{
		pp.outp = p;
		ppcheckout();
	}
	else
	{
		*p++ = '\n';
		pp.addp = p;
		pp.state |= ADD;
	}
	pp.pending = pppendout();
}
