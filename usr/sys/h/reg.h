/* UNIX V7 source code: see /COPYRIGHT or www.tuhs.org for details. */
/* Changes: Copyright (c) 1999 Robert Nordier. All rights reserved. */

#pragma once

#if 0
/*
 * Location of the users' stored
 * registers relative to R0 (EAX for the x86).
 * Usage is u.u_ar0[XX].
 */
#define	EAX	(0)
#define	ECX	(-1)
#define	EDX	(-2)
#define	EBX	(-3)
#define	ESP	(8)
#define	EBP	(-9)
#define	ESI	(-4)
#define	EDI	(-5)
#define	EIP	(5)
#define	EFL	(7)

#define	TBIT	0x100		/* EFLAGS trap flag */

struct trap {
    int dev;
    int pl;
    int edi;
    int esi;
    int ebx;
    int edx;
    int ecx;
    int eax;
    int ds;
    int es;
    int num;
    int err;
    int eip;
    int cs;
    int efl;
    int esp;
    int ss;
};
#else
#define EIP 1
#define	EFL	(7)
#define	ESP	(8)

#define	TBIT	0x100		/* EFLAGS trap flag */

// Loosely from freebsd's reg.h
struct trap {
// OLD intel names
	long dev;
	long pl;
	long eip;
	long cs;
	long efl;
	long esp;
// INCOMING: RISC-V names
	long	ra;		/* return address */
	long	sp;		/* stack pointer */
	long	gp;		/* global pointer */
	long	tp;		/* thread pointer */
	long	t[7];		/* temporaries */
	long	s[12];		/* saved registers */
	long	a[8];		/* function arguments */
	long	sepc;		/* exception program counter */
	long	sstatus;	/* status register */
};
#endif
