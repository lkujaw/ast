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
*                                                                      *
***********************************************************************/
#include	"vcwhdr.h"

/*	Method to get a matching window while decoding.
**	In this case, data must be VCD_SOURCEFILE or VCD_TARGETFILE.
**
**	Written by Kiem-Phong Vo (kpv@research.att.com)
*/

#if __STD_C
static Vcwmatch_t* decode(Vcwindow_t* vcw, Void_t* data, size_t size, Sfoff_t here)
#else
static Vcwmatch_t* decode(vcw, data, size, here)
Vcwindow_t*	vcw;	/* signature structure		*/
Void_t*		data;	/* target data to be matched	*/
size_t		size;	/* data size			*/
Sfoff_t		here;	/* current target position	*/
#endif
{
	Sfio_t	*sf;

	if(!vcw || !vcw->disc || size <= 0 )
		return NIL(Vcwmatch_t*);

	if((vcw->match.type = TYPECAST(int,data)) == VCD_SOURCEFILE )
		sf = vcw->disc->srcf;
	else if(vcw->match.type == VCD_TARGETFILE)
		sf = vcw->disc->tarf;
	else	sf = NIL(Sfio_t*);

	if(!sf)
		return NIL(Vcwmatch_t*);

	if(sfseek(sf, here, SEEK_SET) != here)
		return NIL(Vcwmatch_t*);

	if(!(vcw->match.wdata = sfreserve(sf, size, 0)) || sfvalue(sf) < size )
		return NIL(Vcwmatch_t*);
	vcw->match.wsize = size;
	vcw->match.wpos  = here;
	vcw->match.msize = size;
	vcw->match.more  = 0;

	return &vcw->match;
}

static Vcwmethod_t	_Vcwdecode =
{	decode,
	0,
	"decode"
};

Vcwmethod_t*	Vcwdecode = &_Vcwdecode;
