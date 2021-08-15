/***********************************************************************
*                                                                      *
*               This software is part of the ast package               *
*          Copyright (c) 2000-2011 AT&T Intellectual Property          *
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
*                   Phong Vo <kpv@research.att.com>                    *
*                                                                      *
***********************************************************************/
#pragma prototyped
/*
 * integer tuple list internal/external implementation
 *
 * Glenn Fowler
 * AT&T Research
 */

#include "itl.h"

#include <error.h>

#define ITLINT		uint16_t
#define ITLINTERNAL	itl2internal
#define ITLEXTERNAL	itl2external

#include "itlie.h"

#define ITLINT		uint8_t
#define ITLINTERNAL	itl1internal
#define ITLEXTERNAL	itl1external

#include "itlie.h"

#define ITLINT		uint32_t
#define ITLINTERNAL	itl4internal
#define ITLEXTERNAL	itl4external

#include "itlie.h"
