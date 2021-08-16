/***********************************************************************
*                                                                      *
*               This software is part of the ast package               *
*          Copyright (c) 2003-2011 AT&T Intellectual Property          *
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
*                   Phong Vo <kpv@research.att.com>                    *
*                 Glenn Fowler <gsf@research.att.com>                  *
*                                                                      *
***********************************************************************/
#include	"vctest.h"

#define NCOLS	1600
#define NROWS	2000

int main()
{
	int		i, j;
	Vcchar_t	matrix[NROWS][NCOLS], trans[NCOLS][NROWS], *tr;
	Vcodex_t	*vc;

	for(i = 0; i < NROWS; ++i)
	for(j = 0; j < NCOLS; ++j)
	{	matrix[i][j] = 'a' + (i+j)%26;
		trans[j][i] = 'a' + (i+j)%26;
	}

	if(!(vc = vcopen(0, Vctranspose, "0", 0, VC_ENCODE)) )
		terror("Cannot open Vctranspose handle");

	vcsetmtarg(vc, "columns", (Void_t*)1600, 2);
	if((i = vcapply(vc, matrix, sizeof(matrix), &tr)) != sizeof(matrix) )
		terror("Vctranspose failed");

	if(memcmp(&trans[0][0], tr, sizeof(trans)) != 0)
		terror("Bad data");

	exit(0);
}
