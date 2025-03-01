/***********************************************************************
*                                                                      *
*               This software is part of the ast package               *
*          Copyright (c) 1999-2012 AT&T Intellectual Property          *
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
#include	"terror.h"

#include	<sys/mman.h>

/* Test concurrency locking based on Atomic Scalar Operations
**
** Written by Kiem-Phong Vo
*/

#ifndef N_PROC
#define N_PROC		16
#endif

#define N_SLOT		12	/* number of lock slots		*/
#define N_STEP		1000	/* number of working steps	*/
static int		Pnum;	/* process number		*/
static unsigned int	*Nproc; /* number of processes		*/
static pid_t		*Pid;	/* process id			*/
static unsigned char	*Lckc;	/* slots of char locks		*/
static unsigned short	*Lcks;	/* slots of short locks		*/
static unsigned int	*Lcki;	/* slots of int  locks		*/
static unsigned int	*Done;	/* count done workloads		*/

int lockobj(void* lck, ssize_t size, int locking)
{
	int	lckv, k, aso;

	if(locking == 0) /* unlocking a slot */
	{	if(size == sizeof(char))
			lckv = *((char*)lck);
		else if(size == sizeof(short))
			lckv = *((short*)lck);
		else	lckv = *((int*)lck);
		if(lckv != Pnum ) /* unlocking a wrong lock */
			terror("Process %3d(pid=%d): unlocking %d(pid=%d)?",
				Pnum, Pid[Pnum], lckv);

		if(size == sizeof(char))
			aso = asocaschar(lck, Pnum, 0);
		else if(size == sizeof(short))
			aso = asocasshort(lck, Pnum, 0);
		else	aso = asocasint(lck, Pnum, 0);
		if(aso != Pnum) /* CAS failed! */
			terror("Process %3d(pid=%d): unlocking CAS error %d",
				Pnum, Pid[Pnum], aso);

		return 0;
	}

	for(k = 0;; ++k, usleep(100) ) /* locking a slot */
	{	if(size == sizeof(char))
			aso = asocaschar(lck, 0, Pnum);
		else if(size == sizeof(short))
			aso = asocasshort(lck, 0, Pnum);
		else	aso = asocasint(lck, 0, Pnum);

		if(aso == 0)
			break;
		else if(aso < 0)
			terror("Process %3d(pid=%d): locking CAS error %d",
				Pnum, Pid[Pnum], aso);
		else if(k > 0 && (k%10000) == 0)
			twarn("Process %3d(pid=%d): locking loop %d blocked by %d",
				Pnum, Pid[Pnum], k, aso);
	}

	for(k = 0; k < 2; ++k, usleep(100) ) /* make sure that lock is good */
	{	if(size == sizeof(char))
			lckv = *((char*)lck);
		else if(size == sizeof(short))
			lckv = *((short*)lck);
		else	lckv = *((int*)lck);
		if(lckv != Pnum)
			terror("Process %3d(pid=%d): at step %d lock=%d?",
				Pnum, Pid[Pnum], k, lckv);
	}

	return 0;
}

static void workload(int pnum)
{
	int	k, r;

	Pnum = pnum;
	for(k = 0; k < N_STEP; ++k)
	{	if(k > 0 && (k%100) == 0)
			tinfo("Process %3d(pid=%d): progress to %d", Pnum, Pid[Pnum], k);

		r = random()%N_SLOT;
		lockobj(Lcki+r, sizeof(int), 1);
		if(Lcki[r] != Pnum)
			terror("Process %3d(pid=%d): bad int lock %d",
				Pnum, Pid[Pnum], (int)Lcki[r]);
		lockobj(Lcki+r, sizeof(int), 0);

		r = random()%N_SLOT;
		lockobj(Lcks+r, sizeof(short), 1);
		if(Lcks[r] != Pnum)
			terror("Process %3d(pid=%d): bad short lock %d",
				Pnum, Pid[Pnum], (int)Lcks[r]);
		lockobj(Lcks+r, sizeof(short), 0);

		r = random()%N_SLOT;
		lockobj(Lckc+r, sizeof(char), 1);
		if(Lckc[r] != Pnum)
			terror("Process %3d(pid=%d): bad char lock %d",
				Pnum, Pid[Pnum], (int)Lckc[r]);
		lockobj(Lckc+r, sizeof(char), 0);
	}
	asoincint(Done);
}

tmain()
{
	ssize_t		k, z;
	Void_t		*addr;
	int		zerof;
	pid_t		pid;

	taso(ASO_PROCESS);
	if (!Tstall && !(asometh(0, 0)->type & ASO_INTRINSIC))
	{
		twarn("only ASO_INTRINSIC methods are tested by default");
		texit(0);
	}
	tchild();

	if((zerof = open("/dev/zero", O_RDWR)) < 0)
		terror("Can't open /dev/zero");

	/* get shared memory */
	z = sizeof(*Nproc) + (N_PROC+1)*sizeof(pid_t) + sizeof(*Done) +
		N_SLOT*sizeof(unsigned char) +
		N_SLOT*sizeof(unsigned short) +
		N_SLOT*sizeof(unsigned int);
	addr = mmap(0,z,PROT_READ|PROT_WRITE,MAP_SHARED,zerof,0);
	if(!addr || addr == (Void_t*)(-1))
		terror("mmap failed");
	memset(addr, 0, z);

	Nproc = (unsigned int*)addr;
	Pid   = (pid_t*)(Nproc+1);
	Done  = (unsigned int*)(Pid + (N_PROC+1)*sizeof(pid_t));
	Lcki  = (unsigned int*)(Done + 1);
	Lcks  = (unsigned short*)(Lcki + N_SLOT);
	Lckc  = (unsigned char* )(Lcks + N_SLOT);

	for(k = 1; k <= N_PROC; ++k)
	{	if((pid = fork()) < 0 )
			terror("Can't create a child process");
		else if(pid > 0 ) /* parent process */
		{	Pid[k] = pid; *Nproc += 1;
			continue;
		}
		else /* child process */
		{	for(;; usleep(1000) ) /* wait until all are alive */
				if(*Nproc == N_PROC)
					break;
			workload(k); /* now start working concurrently */
			texit(0);
		}
	}

	if (twait(Pid+1, N_PROC))
		terror("workload subprocess error");

	if(*Done != N_PROC)
		terror("Some subprocess did not finish its workload");

	texit(0);
}
