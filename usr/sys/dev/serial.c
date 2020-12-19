/* V7/x86 source code: see www.nordier.com/v7x86 for details. */
/* Copyright (c) 1999 Robert Nordier.  All rights reserved. */

/*
 * Serial driver: XX
 */

#include "../h/param.h"
#include "../h/conf.h"
#include "../h/dir.h"
#include "../h/user.h"
#include "../h/tty.h"
#include "../h/systm.h"

#define NSR 1

struct tty serial[NSR];

extern ttrstrt();
int serialstart();

serialopen(dev, flag)
dev_t dev;
{
	struct tty *tp;
	int port, d;

	d = minor(dev);
	if (d >= NSR) {
		u.u_error = ENXIO;
		return;
	}
	tp = &serial[d];
//	tp->t_addr = (caddr_t)(d == 0 ? 0x3f8 : 0x2f8);
	tp->t_oproc = serialstart;
	if ((tp->t_state & ISOPEN) == 0) {
		tp->t_state = CARR_ON;
//		tp->t_ispeed = SSPEED;
//		tp->t_ospeed = SSPEED;
		tp->t_flags = RAW | ODDP | EVENP | ECHO;
		serialparam(tp);
//		port = (int)tp->t_addr;
//		outb(port + MCR, inb(port + MCR) | 8);
		ttychars(tp);
	}
	ttyopen(dev, tp);
}

serialclose(dev, flag)
dev_t dev;
{

	ttyclose(&serial[minor(dev)]);
}

serialread(dev)
dev_t dev;
{

	ttread(&serial[minor(dev)]);
}

serialwrite(dev)
dev_t dev;
{

	ttwrite(&serial[minor(dev)]);
}

serialintr(dev)
dev_t dev;
{
	struct tty *tp;
	int port, st, c;

	tp = &serial[dev & 1];
#if 0
	port = (int)tp->t_addr;
	switch (inb(port + IIR) & 7) {
	case 4:
		do {
			c = inb(port + RBR);
			ttyinput(c, tp);
		} while ((st = inb(port + LSR)) & DR);
		if ((st & THRE) == 0)
			break;
	case 2:
		tp->t_state &= ~BUSY;
		ttstart(tp);
	}
#endif
}

serialioctl(dev, cmd, addr, flag)
dev_t dev;
caddr_t addr;
{
	struct tty *tp;

	tp = &serial[minor(dev)];
	if (ttioccomm(cmd, tp, addr, dev)) {
		if (cmd == TIOCSETP || cmd == TIOCSETN)
			serialparam(tp);
	} else
		u.u_error = ENOTTY;
}

int serialstart(tp)
struct tty *tp;
{
	int port, c, i;

	if (tp->t_state & (TIMEOUT | BUSY | TTSTOP))
		return;
#if 0
	if ((c = getc(&tp->t_outq)) >= 0) {
		if (c >= 0200 && (tp->t_flags & RAW) == 0) {
			tp->t_state |= TIMEOUT;
			timeout(ttrstrt, (caddr_t)tp, (c & 0177) + 6);
		} else {
			tp->t_char = c;
			tp->t_state |= BUSY;
			port = (int)tp->t_addr;
			for (i = 8192; i; i--)
				if ((inb(port + LSR) & THRE))
					break;
			if (i == 0)
				printf("timeout in srstart\n");
			outb(port + THR, c);
		}
		if (tp->t_outq.c_cc <= TTLOWAT && tp->t_state & ASLEEP) {
			tp->t_state &= ~ASLEEP;
			wakeup((caddr_t)&tp->t_outq);
		}
	}
#endif
}

serialparam(tp)
struct tty *tp;
{
	int port, v, d, p;
#if 0
	v = srstab[tp->t_ispeed];
	if (v == 0)
		return;

	p = PARTN;
	if (tp->t_flags & RAW)
		d = DATA8;
	else {
		d = DATA7;
		if (tp->t_flags & EVENP)
			p = PARTE;
		else if (tp->t_flags & ODDP)
			p = PARTO;
	}
	port = (int)tp->t_addr;

	outb(port + IER, 0);
	outb(port + LCR, DLAB);
	outb(port + DLL, v);
	outb(port + DLM, v >> 8);
	outb(port + LCR, d | p | STOP1);
	outb(port + IIR, 0x81);
	inb(port + LSR);
	inb(port + RBR);
	outb(port + IER, 3);
#endif
}
