/* UNIX V7 source code: see /COPYRIGHT or www.tuhs.org for details. */
/* Changes: Copyright (c) 1999 Robert Nordier. All rights reserved. */

#pragma once

/*
 * tunable variables
 */
#define BIG 0
#if BIG
#define	NBUF	251		/* size of buffer cache */
#define	NINODE	200		/* number of in core inodes */
#define	NFILE	175		/* number of in core file structures */
#define	NMOUNT	8		/* number of mountable file systems */
#else
#define	NBUF	8		/* size of buffer cache */
#define	NINODE	25		/* number of in core inodes */
#define	NFILE	25		/* number of in core file structures */
#define	NMOUNT	3		/* number of mountable file systems */
#endif
#define	MAXMEM	(64*32)		/* max core per process - first # is Kw */
#define	MAXUPRC	25		/* max processes per user */
#define	SSIZE	1		/* initial stack size (*4096 bytes) */
#define	SINCR	1		/* increment of stack (*4096 bytes) */
#define	NOFILE	20		/* max open files per process */
#define	CANBSIZ	256		/* max size of typewriter line */
#define	CMAPSIZ	50		/* size of core allocation area */
#define	SMAPSIZ	50		/* size of swap allocation area */
#define	NCALL	20		/* max simultaneous time callouts */
#if BIG
#define	NPROC	150		/* max number of processes */
#define	NTEXT	40		/* max number of pure texts */
#else
#define	NPROC	40		/* max number of processes */
#define	NTEXT	25		/* max number of pure texts */
#endif
#define	NCLIST	100		/* max total clist size */
#define	HZ	60		/* Ticks/second of the clock */
#define	TIMEZONE (5*60)		/* Minutes westward from Greenwich */
#define	DSTFLAG	1		/* Daylight Saving Time applies in this locality */
#define	MSGBUFS	128		/* Characters saved from error messages */
#define	NCARGS	5120		/* # characters in exec arglist */

/*
 * priorities
 * probably should not be
 * altered too much
 */

#define	PSWP	0
#define	PINOD	10
#define	PRIBIO	20
#define	PZERO	25
#define	NZERO	20
#define	PPIPE	26
#define	PWAIT	30
#define	PSLEP	40
#define	PUSER	50

/*
 * signals
 * dont change
 */

#define	NSIG	17

#define	SIGHUP	1	/* hangup */
#define	SIGINT	2	/* interrupt (rubout) */
#define	SIGQUIT	3	/* quit (FS) */
#define	SIGINS	4	/* illegal instruction */
#define	SIGTRC	5	/* trace or breakpoint */
#define	SIGIOT	6	/* iot */
#define	SIGEMT	7	/* emt */
#define	SIGFPT	8	/* floating exception */
#define	SIGKIL	9	/* kill, uncatchable termination */
#define	SIGBUS	10	/* bus error */
#define	SIGSEG	11	/* segmentation violation */
#define	SIGSYS	12	/* bad system call */
#define	SIGPIPE	13	/* end of pipe */
#define	SIGCLK	14	/* alarm clock */
#define	SIGTRM	15	/* Catchable termination */

/*
 * fundamental constants of the implementation--
 * cannot be changed easily
 */

#define	NBPW	sizeof(int)	/* number of bytes in an integer */
#define	BSIZE	512		/* size of secondary block (bytes) */
/* BSLOP can be 0 unless you have a TIU/Spider */
#define	BSLOP	2		/* In case some device needs bigger buffers */
#define	NINDIR	(BSIZE/sizeof(daddr_t))
#define	BMASK	0777		/* BSIZE-1 */
#define	BSHIFT	9		/* LOG2(BSIZE) */
#define	NMASK	0177		/* NINDIR-1 */
#define	NSHIFT	7		/* LOG2(NINDIR) */
#define	USIZE	2		/* size of user block etc. (*4096) */
#define	NULL	0
#define	CMASK	0		/* default mask for file creation */
#define	NODEV	(dev_t)(-1)
#define	ROOTINO	((ino_t)2)	/* i number of all roots */
#define	SUPERB	((daddr_t)1)	/* block number of the super block */
#define	DIRSIZ	14		/* max characters per directory */
#define	NICINOD	100		/* number of superblock inodes */
#define	NICFREE	50		/* number of superblock free blocks */
#define	INFSIZE	138		/* size of per-proc info for users */
#define	CBSIZE	28		/* number of chars in a clist block */
#define	CROUND	037		/* clist rounding: sizeof(int *) + CBSIZE - 1*/

/*
 * Some macros for units conversion
 */
/* Core clicks (4096 bytes) to disk blocks */
#define	ctod(x)	((x)<<3)

/* inumber to disk address */
#define	itod(x)	(daddr_t)((((unsigned)x+15)>>3))

/* inumber to disk offset */
#define	itoo(x)	(int)((x+15)&07)

#if 1
/* clicks to bytes */
#define	ctob(x)	(x<<12)

/* bytes to clicks */
#define	btoc(x)	((((unsigned)x+4095)>>12))
#else
#define ctob(x) (x)
#define btoc(x) (x)
#endif

/* major part of a device */
#define	major(x)	(int)(((unsigned)x>>8))

/* minor part of a device */
#define	minor(x)	(int)(x&0377)

/* make a device number */
#define	makedev(x,y)	(dev_t)((x)<<8 | (y))
#if 0
// From FreeBSD. This is probably a bad place for this...
typedef long long __register_t;
struct gpregs {
	__register_t	gp_ra;
	__register_t	gp_sp;
	__register_t	gp_gp;
	__register_t	gp_tp;
	__register_t	gp_t[7];
	__register_t	gp_s[12];
	__register_t	gp_a[8];
	__register_t	gp_sepc;
	__register_t	gp_sstatus;
};
#endif

typedef	struct { int r[1]; } *	physadr;
typedef	long		daddr_t;
typedef char *		caddr_t;
typedef	unsigned short	ino_t;
////typedef	long		time_t;
// typedef	_TIME_T_ time_t;
// #define  _TIME_T_DECLARED 1
typedef unsigned long long	 time_t;    /* a time */
typedef	long		label_t[32];	/* RISC-V has 32 registers */
//typedef struct gpregs		label_t;
typedef	short		dev_t;
typedef	long		off_t;

/*
 * Machine-dependent bits and macros
 */
#define PGSH  12
#define PGSZ  4096

#define USTK  0x400000
// RJL #define PHY   0x40000000
#define PHY   0x20000000

#define KBASE 0x7fc00000
#define KSTK  0x7ffa0000

#define	USERMODE(cs)	(((cs)&0xffff)!=0x10)
#define	BASEPRI(pl)	((pl)!=0xffff)
