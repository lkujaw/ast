/***********************************************************************
*                                                                      *
*               This software is part of the ast package               *
*          Copyright (c) 1985-2011 AT&T Intellectual Property          *
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
*                  David Korn <dgk@research.att.com>                   *
*                   Phong Vo <kpv@research.att.com>                    *
*                                                                      *
***********************************************************************/
#include	"sfhdr.h"

/*	Delete all pending data in the buffer
**
**	Written by Kiem-Phong Vo.
*/

#if __STD_C
int sfpurge(Sfio_t* f)
#else
int sfpurge(f)
Sfio_t*	f;
#endif
{
	reg int	mode;
	SFMTXDECL(f);

	SFMTXENTER(f,-1);

	if((mode = f->mode&SF_RDWR) != (int)f->mode && _sfmode(f,mode|SF_SYNCED,0) < 0)
		SFMTXRETURN(f, -1);

	if((f->flags&SF_IOCHECK) && f->disc && f->disc->exceptf)
		(void)(*f->disc->exceptf)(f,SF_PURGE,(Void_t*)((int)1),f->disc);

	if(f->disc == _Sfudisc)
		(void)sfclose((*_Sfstack)(f,NIL(Sfio_t*)));

	/* cannot purge read string streams */
	if((f->flags&SF_STRING) && (f->mode&SF_READ) )
		goto done;

	SFLOCK(f,0);

	/* if memory map must be a read stream, pretend data is gone */
#ifdef MAP_TYPE
	if(f->bits&SF_MMAP)
	{	f->here -= f->endb - f->next;
		if(f->data)
		{	SFMUNMAP(f,f->data,f->endb-f->data);
			(void)SFSK(f,f->here,SEEK_SET,f->disc);
		}
		SFOPEN(f,0);
		SFMTXRETURN(f, 0);
	}
#endif

	switch(f->mode&~SF_LOCK)
	{
	default :
		SFOPEN(f,0);
		SFMTXRETURN(f, -1);
	case SF_WRITE :
		f->next = f->data;
		if(!f->proc || !(f->flags&SF_READ) || !(f->mode&SF_WRITE) )
			break;

		/* 2-way pipe, must clear read buffer */
		(void)_sfmode(f,SF_READ,1);
		/* fall through */
	case SF_READ:
		if(f->extent >= 0 && f->endb > f->next)
		{	f->here -= f->endb-f->next;
			(void)SFSK(f,f->here,SEEK_SET,f->disc);
		}
		f->endb = f->next = f->data;
		break;
	}

	SFOPEN(f,0);

done:
	if((f->flags&SF_IOCHECK) && f->disc && f->disc->exceptf)
		(void)(*f->disc->exceptf)(f,SF_PURGE,(Void_t*)((int)0),f->disc);

	SFMTXRETURN(f, 0);
}
