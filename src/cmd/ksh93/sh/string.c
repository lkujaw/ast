/***********************************************************************
*                                                                      *
*               This software is part of the ast package               *
*          Copyright (c) 1982-2012 AT&T Intellectual Property          *
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
*                  David Korn <dgk@research.att.com>                   *
*                                                                      *
***********************************************************************/
#pragma prototyped
/*
 * string processing routines for Korn shell
 *
 */

#include	<ast.h>
#include	<ast_wchar.h>
#include	"defs.h"
#include	<stak.h>
#include	<ccode.h>
#include	"shtable.h"
#include	"lexstates.h"
#include	"national.h"

#if _hdr_wctype
#   include <wctype.h>
#endif

#if !_lib_iswprint && !defined(iswprint)
#   define iswprint(c)		(((c)&~0377) || isprint(c))
#endif


/*
 *  Table lookup routine
 *  <table> is searched for string <sp> and corresponding value is returned
 *  This is only used for small tables and is used to save non-sharable memory 
 */

const Shtable_t *sh_locate(register const char *sp,const Shtable_t *table,int size)
{
	register int			first;
	register const Shtable_t	*tp;
	register int			c;
	static const Shtable_t		empty = {0,0};
	if(sp==0 || (first= *sp)==0)
		return(&empty);
	tp=table;
	while((c= *tp->sh_name) && (CC_NATIVE!=CC_ASCII || c <= first))
	{
		if(first == c && strcmp(sp,tp->sh_name)==0)
			return(tp);
		tp = (Shtable_t*)((char*)tp+size);
	}
	return(&empty);
}

/*
 *  shtab_options lookup routine
 */

#define sep(c)		((c)=='-'||(c)=='_')

int sh_lookopt(register const char *sp, int *invert)
{
	register int			first;
	register const Shtable_t	*tp;
	register int			c;
	register const char		*s, *t, *sw, *tw;
	int				amb;
	int				hit;
	int				inv;
	int				no;
	if(sp==0)
		return(0);
	if(*sp=='n' && *(sp+1)=='o' && (*(sp+2)!='t' || *(sp+3)!='i'))
	{
		sp+=2;
		if(sep(*sp))
			sp++;
		*invert = !*invert;
	}
	if((first= *sp)==0)
		return(0);
	tp=shtab_options;
	amb=hit=0;
	for(;;)
	{
		t=tp->sh_name;
		if(no = *t=='n' && *(t+1)=='o' && *(t+2)!='t')
			t+=2;
		if(!(c= *t))
			break;
		if(first == c)
		{
			if(strcmp(sp,t)==0)
			{
				*invert ^= no;
				return(tp->sh_number);
			}
			s=sw=sp;
			tw=t;
			for(;;)
			{
				if(!*s || *s=='=')
				{
					if (*s == '=' && !strtol(s+1, NiL, 0))
						no = !no;
					if (!*t)
					{
						*invert ^= no;
						return(tp->sh_number);
					}
					if (hit || amb)
					{
						hit = 0;
						amb = 1;
					}
					else
					{
						hit = tp->sh_number;
						inv = no;
					}
					break;
				}
				else if(!*t)
					break;
				else if(sep(*s))
					sw = ++s;
				else if(sep(*t))
					tw = ++t;
				else if(*s==*t)
				{
					s++;
					t++;
				}
				else if(s==sw && t==tw)
					break;
				else
				{
					if(t!=tw)
					{
						while(*t && !sep(*t))
							t++;
						if(!*t)
							break;
						tw = ++t;
					}
					while (s>sw && *s!=*t)
						s--;
				}
			}
		}
		tp = (Shtable_t*)((char*)tp+sizeof(*shtab_options));
	}
	if(hit)
		*invert ^= inv;
	return(hit);
}

/*
 * look for the substring <oldsp> in <string> and replace with <newsp>
 * The new string is put on top of the stack
 */
char *sh_substitute(const char *string,const char *oldsp,char *newsp)
/*@
	assume string!=NULL && oldsp!=NULL && newsp!=NULL;
	return x satisfying x==NULL ||
		strlen(x)==(strlen(in string)+strlen(in newsp)-strlen(in oldsp));
@*/
{
	register const char *sp = string;
	register const char *cp;
	const char *savesp = 0;
	stakseek(0);
	if(*sp==0)
		return((char*)0);
	if(*(cp=oldsp) == 0)
		goto found;
#if SHOPT_MULTIBYTE
	mbinit();
#endif /* SHOPT_MULTIBYTE */
	do
	{
	/* skip to first character which matches start of oldsp */
		while(*sp && (savesp==sp || *sp != *cp))
		{
#if SHOPT_MULTIBYTE
			/* skip a whole character at a time */
			int c = mbsize(sp);
			if(c < 0)
				sp++;
			while(c-- > 0)
#endif /* SHOPT_MULTIBYTE */
			stakputc(*sp++);
		}
		if(*sp == 0)
			return((char*)0);
		savesp = sp;
	        for(;*cp;cp++)
		{
			if(*cp != *sp++)
				break;
		}
		if(*cp==0)
		/* match found */
			goto found;
		sp = savesp;
		cp = oldsp;
	}
	while(*sp);
	return((char*)0);

found:
	/* copy new */
	stakputs(newsp);
	/* copy rest of string */
	stakputs(sp);
	return(stakfreeze(1));
}

/*
 * TRIM(sp)
 * Remove escape characters from characters in <sp> and eliminate quoted nulls.
 */

void	sh_trim(register char *sp)
/*@
	assume sp!=NULL;
	promise  strlen(in sp) <= in strlen(sp);
@*/
{
	register char *dp;
	register int c;
	if(sp)
	{
		dp = sp;
		while(c= *sp)
		{
#if SHOPT_MULTIBYTE
			int len;
			if(mbwide() && (len=mbsize(sp))>1)
			{
				memmove(dp, sp, len);
				dp += len;
				sp += len;
				continue;
			}
#endif /* SHOPT_MULTIBYTE */
			sp++;
			if(c == '\\')
				c = *sp++;
			if(c)
				*dp++ = c;
		}
		*dp = 0;
	}
}

/*
 * copy <str1> to <str2> changing upper case to lower case
 * <str2> must be big enough to hold <str1>
 * <str1> and <str2> may point to the same place.
 */

void sh_utol(register char const *str1,register char *str2)
/*@
	assume str1!=0 && str2!=0
	return x satisfying strlen(in str1)==strlen(in str2);
@*/ 
{
	register int c;
	for(; c= *((unsigned char*)str1); str1++,str2++)
	{
		if(isupper(c))
			*str2 = tolower(c);
		else
			*str2 = c;
	}
	*str2 = 0;
}

/*
 * format string as a csv field
 */
static char	*sh_fmtcsv(const char *string)
{
	register const char *cp = string;
	register int c;
	int offset;
	if(!cp)
		return((char*)0);
	offset = staktell();
	while((c=mbchar(cp)),isaname(c));
	if(c==0)
		return((char*)string);
	stakputc('"');
	stakwrite(string,cp-string);
	if(c=='"')
		stakputc('"');
	string = cp;
	while(c=mbchar(cp))
	{
		if(c=='"')
		{
			stakwrite(string,cp-string);
			string = cp;
			stakputc('"');
		}
	}
	if(--cp>string)
		stakwrite(string,cp-string);
	stakputc('"');
	stakputc(0);
	return(stakptr(offset));
}

/*
 * print <str> quoting chars so that it can be read by the shell
 * puts null terminated result on stack, but doesn't freeze it
 */
char	*sh_fmtq(const char *string)
{
	register const char *cp = string, *op;
	register int c, state;
	int offset;
	if(!cp)
		return((char*)0);
	offset = staktell();
	state = ((c= mbchar(cp))==0);
	if(isaletter(c))
	{
		while((c=mbchar(cp)),isaname(c));
		if(c==0)
			return((char*)string);
		if(c=='=')
		{
			if(*cp==0)
				return((char*)string);
			if(*cp=='=')
				cp++;
			c = cp - string;
			stakwrite(string,c);
			string = cp;
			c = mbchar(cp);
		}
	}
	if(c==0 || c=='#' || c=='~')
		state = 1;
	for(;c;c= mbchar(cp))
	{
#if SHOPT_MULTIBYTE
		if(c=='\'' || c>=128 || c<0 || !iswprint(c)) 
#else
		if(c=='\'' || !isprint(c))
#endif /* SHOPT_MULTIBYTE */
			state = 2;
		else if(c==']' || c=='=' || (c!=':' && c<=0x7f && (c=sh_lexstates[ST_NORM][c]) && c!=S_EPAT))
			state |=1;
	}
	if(state<2)
	{
		if(state==1)
			stakputc('\'');
		if(c = --cp - string)
			stakwrite(string,c);
		if(state==1)
			stakputc('\'');
	}
	else
	{
		int isbyte=0;
		stakwrite("$'",2);
		cp = string;
#if SHOPT_MULTIBYTE
		while(op = cp, c= mbchar(cp))
#else
		while(op = cp, c= *(unsigned char*)cp++)
#endif
		{
			state=1;
			switch(c)
			{
			    case ('a'==97?'\033':39):
				c = 'E';
				break;
			    case '\n':
				c = 'n';
				break;
			    case '\r':
				c = 'r';
				break;
			    case '\t':
				c = 't';
				break;
			    case '\f':
				c = 'f';
				break;
			    case '\b':
				c = 'b';
				break;
			    case '\a':
				c = 'a';
				break;
			    case '\\':	case '\'':
				break;
			    default:
#if SHOPT_MULTIBYTE
				isbyte = 0;
				if(c<0)
				{
					c = *((unsigned char *)op);
					cp = op+1;
					isbyte = 1;
				}
				if(mbwide() && ((cp-op)>1))
				{
					sfprintf(staksp,"\\u[%x]",c);
					continue;
				}
				else if(!iswprint(c) || isbyte)
#else
				if(!isprint(c))
#endif
				{
					sfprintf(staksp,"\\x%.2x",c);
					continue;
				}
				state=0;
				break;
			}
			if(state)
			{
				stakputc('\\');
				stakputc(c);
			}
			else
				stakwrite(op, cp-op);
		}
		stakputc('\'');
	}
	stakputc(0);
	return(stakptr(offset));
}

/*
 * print <str> quoting chars so that it can be read by the shell
 * puts null terminated result on stack, but doesn't freeze it
 * single!=0 limits quoting to '...'
 * fold>0 prints raw newlines and inserts appropriately
 * escaped newlines every (fold-x) chars
 */
char	*sh_fmtqf(const char *string, int single, int fold)
{
	register const char *cp = string;
	register const char *bp;
	register const char *vp;
	register int c;
	register int n;
	register int q;
	register int a;
	int offset;

	if (--fold < 8)
		fold = 0;
	if(single)
		return sh_fmtcsv(cp);
	if (!cp || !*cp || !fold || fold && strlen(string) < fold)
		return sh_fmtq(cp);
	offset = staktell();
	single = single ? 1 : 3;
	c = mbchar(string);
	a = isaletter(c) ? '=' : 0;
	vp = cp + 1;
	do
	{
		q = 0;
		n = fold;
		bp = cp;
		while ((!n || n-- > 0) && (c = mbchar(cp)))
		{
			if (a && !isaname(c))
				a = 0;
#if SHOPT_MULTIBYTE
			if (c >= 0x200)
				continue;
			if (c == '\'' || !iswprint(c))
#else
			if (c == '\'' || !isprint(c))
#endif /* SHOPT_MULTIBYTE */
			{
				q = single;
				break;
			}
			if (c == '\n')
				q = 1;
			else if (c == a)
			{
				stakwrite(bp, cp - bp);
				bp = cp;
				vp = cp + 1;
				a = 0;
			}
			else if ((c == '#' || c == '~') && cp == vp || c == ']' || c != ':' && (c = sh_lexstates[ST_NORM][c]) && c != S_EPAT)
				q = 1;
		}
		if (q & 2)
		{
			stakputc('$');
			stakputc('\'');
			cp = bp;
			n = fold - 3;
			q = 1;
			while (c = mbchar(cp))
			{
				switch (c)
				{
		    		case ('a'==97?'\033':39):
					c = 'E';
					break;
		    		case '\n':
					q = 0;
					n = fold - 1;
					break;
		    		case '\r':
					c = 'r';
					break;
		    		case '\t':
					c = 't';
					break;
		    		case '\f':
					c = 'f';
					break;
		    		case '\b':
					c = 'b';
					break;
		    		case '\a':
					c = 'a';
					break;
		    		case '\\':
					if (*cp == 'n')
					{
						c = '\n';
						q = 0;
						n = fold - 1;
						break;
					}
				case '\'':
					break;
		    		default:
#if SHOPT_MULTIBYTE
					if(!iswprint(c))
#else
					if(!isprint(c))
#endif
					{
						if ((n -= 4) <= 0)
						{
							stakwrite("'\\\n$'", 5);
							n = fold - 7;
						}
						sfprintf(staksp, "\\%03o", c);
						continue;
					}
					q = 0;
					break;
				}
				if ((n -= q + 1) <= 0)
				{
					if (!q)
					{
						stakputc('\'');
						cp = bp;
						break;
					}
					stakwrite("'\\\n$'", 5);
					n = fold - 5;
				}
				if (q)
					stakputc('\\');
				else
					q = 1;
				stakputc(c);
				bp = cp;
			}
			if (!c)
				stakputc('\'');
		}
		else if (q & 1)
		{
			stakputc('\'');
			cp = bp;
			n = fold ? (fold - 2) : 0;
			while (c = mbchar(cp))
			{
				if (c == '\n')
					n = fold - 1;
				else if (n && --n <= 0)
				{
					n = fold - 2;
					stakwrite(bp, --cp - bp);
					bp = cp;
					stakwrite("'\\\n'", 4);
				}
				else if (n == 1 && *cp == '\'')
				{
					n = fold - 5;
					stakwrite(bp, --cp - bp);
					bp = cp;
					stakwrite("'\\\n\\''", 6);
				}
				else if (c == '\'')
				{
					stakwrite(bp, cp - bp - 1);
					bp = cp;
					if (n && (n -= 4) <= 0)
					{
						n = fold - 5;
						stakwrite("'\\\n\\''", 6);
					}
					else
						stakwrite("'\\''", 4);
				}
			}
			stakwrite(bp, cp - bp - 1);
			stakputc('\'');
		}
		else if (n = fold)
		{
			cp = bp;
			while (c = mbchar(cp))
			{
				if (--n <= 0)
				{
					n = fold;
					stakwrite(bp, --cp - bp);
					bp = cp;
					stakwrite("\\\n", 2);
				}
			}
			stakwrite(bp, cp - bp - 1);
		}
		else
			stakwrite(bp, cp - bp);
		if (c)
		{
			stakputc('\\');
			stakputc('\n');
		}
	} while (c);
	stakputc(0);
	return(stakptr(offset));
}

#if SHOPT_MULTIBYTE
	int sh_strchr(const char *string, register const char *dp)
	{
		wchar_t c, d;
		register const char *cp=string;
		mbinit();
		d = mbchar(dp); 
		mbinit();
		while(c = mbchar(cp))
		{
			if(c==d)
				return(cp-string);
		}
		if(d==0)
			return(cp-string);
		return(-1);
	}
#endif /* SHOPT_MULTIBYTE */

const char *_sh_translate(const char *message)
{
#if ERROR_VERSION >= 20000317L
	return(ERROR_translate(0,0,e_dict,message));
#else
#if ERROR_VERSION >= 20000101L
	return(ERROR_translate(e_dict,message));
#else
	return(ERROR_translate(message,1));
#endif
#endif
}

/*
 * change '['identifier']' to identifier
 * character before <str> must be a '['
 * returns pointer to last character
 */
char *sh_checkid(char *str, char *last)
{
	register unsigned char *cp = (unsigned char*)str;
	register unsigned char *v = cp;
	register int c;
	if(c=mbchar(cp),isaletter(c))
		while(c=mbchar(cp),isaname(c));
	if(c==']' && (!last || ((char*)cp==last)))
	{
		/* eliminate [ and ] */
		while(v < cp)
		{
			v[-1] = *v;
			v++;
		}
		if(last)
			last -=2;
		else
		{
			while(*v)
			{
				v[-2] = *v;
				v++;
			}
			v[-2] = 0;
			last = (char*)v;
		}
	}
	return(last);
}

#if	_AST_VERSION  <= 20000317L
char *fmtident(const char *string)
{
	return((char*)string);
}
#endif
