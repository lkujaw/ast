/***********************************************************************
*                                                                      *
*               This software is part of the ast package               *
*          Copyright (c) 1989-2012 AT&T Intellectual Property          *
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
 * expression library definitions
 */

#ifndef _EXPR_H
#define _EXPR_H

#include <ast.h>

#undef	RS	/* hp.pa <signal.h> grabs this!! */

#if _BLD_expr && defined(__EXPORT__)
#define extern		__EXPORT__
#endif
#if !_BLD_expr && defined(__IMPORT__)
#define extern		extern __IMPORT__
#endif

/*
 * bison -pPREFIX misses YYSTYPE
 */

/* Modified ifdefs to deal with different versions of yacc / bison */
#if defined(YYSTYPE) || defined(YYBISON)
#define EXSTYPE		YYSTYPE
#else
#include <exparse.h>
#if defined(YYSTYPE) || defined(yystype)
#define EXSTYPE		YYSTYPE
#else
#if defined(YYSTYPE) || defined(YYSTYPE_IS_DECLARED)
#define EXSTYPE		YYSTYPE
#endif
#endif
#endif

#undef	extern

#include <cdt.h>
#include <vmalloc.h>

#define EX_VERSION	20000101L

/*
 * flags
 */

#define EX_CHARSTRING	(1<<0)		/* '...' same as "..."		*/
#define EX_CONSTANT	(1<<1)		/* compile to constant expr	*/
#define EX_FATAL	(1<<2)		/* errors are fatal		*/
#define EX_INTERACTIVE	(1<<3)		/* interactive input		*/
#define EX_PURE		(1<<4)		/* no default symbols/keywords	*/
#define EX_QUALIFY	(1<<5)		/* '.' refs qualified in id tab	*/
#define EX_RETAIN	(1<<6)		/* retain expressions on redef	*/
#define EX_SIZED	(1<<7)		/* strings are sized buffers	*/
#define EX_STRICT	(1<<8)		/* don't override null label	*/
#define EX_UNDECLARED	(1<<9)		/* allow undeclared identifiers	*/

#define EX_CALL		(-2)		/* getval() function call elt	*/
#define EX_SCALAR	(-1)		/* getval() scalar elt		*/

#define EX_NAMELEN	32		/* default Exid_t.name length	*/

#define EXID(n,l,i,t,f)	{{0},(l),(i),(t),(f),0,{0},0,n}

#define DELETE		MINTOKEN		/* exexpr() delete `type'	*/

#define INTEGRAL(t)	((t)>=CHAR&&(t)<=UNSIGNED)

/*
 * arg 0 is the return value type
 */

#define F		01		/* FLOATING			*/
#define I		02		/* INTEGER			*/
#define S		03		/* STRING			*/

#define A(n,t)		((t)<<((n)*2))	/* function arg n is type t	*/
#define N(t)		((t)>>=2)	/* shift for next arg		*/
#define T(t)		a2t[(t)&03]	/* get actual type for t	*/

#define exalloc(p,n)		exnewof(p,0,char,n,0)
#define exnewof(p,o,t,n,x)	vmnewof((p)->vm,o,t,n,x)
#define exfree(p,x)		vmfree((p)->vm,x)
#define exstrdup(p,s)		vmstrdup((p)->vm,s)

#if LONG_MAX > INT_MAX
typedef int Exshort_t;
#else
typedef short Exshort_t;
#endif

typedef EXSTYPE Extype_t;

union Exdata_u; typedef union Exdata_u Exdata_t;
struct Exdisc_s; typedef struct Exdisc_s Exdisc_t;
struct Exnode_s; typedef struct Exnode_s Exnode_t;
struct Expr_s; typedef struct Expr_s Expr_t;
struct Exref_s; typedef struct Exref_s Exref_t;

typedef struct Exlocal_s		/* user defined member type	*/
{
	Sflong_t	number;
	char*		pointer;
} Exlocal_t;

typedef struct Exid_s			/* id symbol table info		*/
{
	Dtlink_t	link;		/* symbol table link		*/
	long		lex;		/* lex class			*/
	long		index;		/* user defined index		*/
	long		type;		/* symbol and arg types		*/
	long		flags;		/* user defined flags		*/
	Exnode_t*	value;		/* value			*/
	Exlocal_t	local;		/* user defined local stuff	*/
	long		isstatic;	/* static			*/
	char		name[EX_NAMELEN];/* symbol name			*/
} Exid_t;

struct Exref_s				/* . reference list		*/
{
	Exref_t*	next;		/* next in list			*/
	Exid_t*		symbol;		/* reference id symbol		*/
	Exnode_t*	index;		/* optional reference index	*/
};

typedef struct Exbuf_s			/* sized buffer			*/
{
	unsigned long	size;		/* buffer size			*/
	char*		data;		/* buffer data			*/
} Exbuf_t;

union Exdata_u
{

	struct
	{
	Extype_t	value;		/* constant value		*/
	Exid_t*		reference;	/* conversion reference symbol	*/
	}		constant;	/* variable reference		*/

	struct
	{
	Exnode_t*	left;		/* left operand			*/
	Exnode_t*	right;		/* right operand		*/
	Exnode_t*	last;		/* for cons			*/
	}		operand;	/* operands			*/

	struct
	{
	Exnode_t*	statement;	/* case label statement(s)	*/
	Exnode_t*	next;		/* next case item		*/
	Extype_t**	constant;	/* case label constant array	*/
	}		select;		/* case item			*/

	struct
	{
	Exid_t*		symbol;		/* id symbol table entry	*/
	Exref_t*	reference;	/* . reference list		*/
	Exnode_t*	index;		/* array index expression	*/
	}		variable;	/* variable reference		*/

#ifdef _EX_DATA_PRIVATE_
	_EX_DATA_PRIVATE_
#endif

};

struct Exnode_s				/* expression tree node		*/
{
	Exshort_t	type;		/* value type			*/
	Exshort_t	op;		/* operator			*/
	Exshort_t	binary;		/* data.operand.{left,right} ok	*/
	Exshort_t	pad_1;		/* padding to help cc		*/
	Exlocal_t	local;		/* user defined local stuff	*/
	union
	{
	double	(*floating)(char**);	/* FLOATING return value	*/
	Sflong_t(*integer)(char**);	/* INTEGER|UNSIGNED return value*/
	char*	(*string)(char**);	/* STRING return value		*/
	}		compiled;	/* compiled function pointer	*/
	Exdata_t	data;		/* node data			*/

#ifdef _EX_NODE_PRIVATE_
	_EX_NODE_PRIVATE_
#endif

};

struct Exdisc_s				/* discipline			*/
{
	unsigned long	version;	/* EX_VERSION			*/
	unsigned long	flags;		/* EX_* flags			*/
	Exid_t*		symbols;	/* static symbols		*/
	char**		data;		/* compiled function arg data	*/
	char*		lib;		/* pathfind() lib		*/
	char*		type;		/* pathfind() type		*/
	int		(*castf)(Expr_t*, Exnode_t*, const char*, int, Exid_t*, int, Exdisc_t*);
					/* unknown cast function	*/
	int		(*convertf)(Expr_t*, Exnode_t*, int, Exid_t*, int, Exdisc_t*);
					/* type conversion function	*/
	Error_f		errorf;		/* error function		*/
	Extype_t	(*getf)(Expr_t*, Exnode_t*, Exid_t*, Exref_t*, void*, int, Exdisc_t*);
					/* get value function		*/
	Extype_t	(*reff)(Expr_t*, Exnode_t*, Exid_t*, Exref_t*, char*, int, Exdisc_t*);
					/* reference value function	*/
	int		(*setf)(Expr_t*, Exnode_t*, Exid_t*, Exref_t*, void*, int, Extype_t, Exdisc_t*);
					/* set value function		*/
	int		(*matchf)(Expr_t*, Exnode_t*, const char*, Exnode_t*, const char*, void*, Exdisc_t*);
};

struct Expr_s				/* ex program state		*/
{
	const char*	id;		/* library id			*/
	Dt_t*		symbols;	/* symbol table			*/
	const char*	more;		/* more after %% (sp or != 0)	*/
	Sfio_t*		file[10];	/* io streams			*/
	Vmalloc_t*	vm;		/* program store		*/

#ifdef _EX_PROG_PRIVATE_
	_EX_PROG_PRIVATE_
#endif

};

struct Excc_s; typedef struct Excc_s Excc_t;
struct Exccdisc_s; typedef struct Exccdisc_s Exccdisc_t;

struct Exccdisc_s			/* excc() discipline		*/
{
	Sfio_t*		text;		/* text output stream		*/
	char*		id;		/* symbol prefix		*/
	unsigned long	flags;		/* EXCC_* flags			*/
	int		(*ccf)(Excc_t*, Exnode_t*, Exid_t*, Exref_t*, Exnode_t*, Exccdisc_t*);
					/* program generator function	*/
};

struct Excc_s				/* excc() state			*/
{
	Expr_t*		expr;		/* exopen() state		*/
	Exdisc_t*	disc;		/* exopen() discipline		*/

#ifdef _EX_CC_PRIVATE_
	_EX_CC_PRIVATE_
#endif

};

#if _BLD_expr && defined(__EXPORT__)
#define extern		__EXPORT__
#endif

extern Exnode_t*	excast(Expr_t*, Exnode_t*, int, Exnode_t*, int);
extern int		excc(Excc_t*, const char*, Exid_t*, int);
extern int		exccclose(Excc_t*);
extern Excc_t*		exccopen(Expr_t*, Exccdisc_t*);
extern void		exclose(Expr_t*, int);
extern int		excomp(Expr_t*, const char*, int, const char*, Sfio_t*);
extern char*		excontext(Expr_t*, char*, int);
extern int		exdump(Expr_t*, Exnode_t*, Sfio_t*);
extern void		exerror(const char*, ...);
extern Extype_t		exeval(Expr_t*, Exnode_t*, void*);
extern Exnode_t*	exexpr(Expr_t*, const char*, Exid_t*, int);
extern void		exfreenode(Expr_t*, Exnode_t*);
extern Exnode_t*	exnewnode(Expr_t*, int, int, int, Exnode_t*, Exnode_t*);
extern char*		exnospace(void);
extern Expr_t*		exopen(Exdisc_t*);
extern int		expop(Expr_t*);
extern int		expush(Expr_t*, const char*, int, const char*, Sfio_t*);
extern int		exrewind(Expr_t*);
extern char*		exstash(Sfio_t*, Vmalloc_t*);
extern void		exstatement(Expr_t*);
extern int		extoken(Expr_t*);
extern char*		extype(int);
extern Extype_t		exzero(int);

#undef	extern

#endif
