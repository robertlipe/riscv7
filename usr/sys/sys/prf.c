/* UNIX V7 source code: see /COPYRIGHT or www.tuhs.org for details. */
/* Changes: Copyright (c) 1999 Robert Nordier. All rights reserved. */

#include "../h/param.h"
#include "../h/systm.h"
#include "../h/seg.h"
#include "../h/buf.h"
#include "../h/conf.h"

#include <stdarg.h>

/*
 * In case console is off,
 * panicstr contains argument to last
 * call to panic.
 */

char	*panicstr;
const char hexdigits[] = "0123456789abcdef";

/*
 * Scaled down version of C Library printf.
 * Only %s %u %d (==%u) %o %x %D are recognized.
 * Used to print diagnostic information
 * directly on console tty.
 * Since it is not interrupt driven,
 * all system activities are pretty much
 * suspended.
 * Printf should not be used for chit-chat.
 */
/* VARARGS 1 */
// RJL - this should be picked through for va_list compliance

void
// printf (register char *fmt, unsigned x1)
printf (const char* restrict fmt, ...)
{
	register c;
	char *s;
	int d;
        va_list list;
        va_start(list, fmt);
#if 1 // BOOGER
loop:
	while((c = *fmt++) != '%') {
//	while((c = va_arg(list, int)) != '%') {
		if(c == '\0') {
			return;
		}
		putchar(c);
	}
	// c must be at the % mark, so skip over that
//	c = va_arg(list,  int);
//	c++;
	c = *fmt++;
#else
	c = va_arg(list,  int);
	while ((c = *fmt++)) {
#endif
	switch (c) {
	case 'd': {
    unsigned int d = va_arg(list, unsigned int);
		if (d < 0) {
			putchar('-');
			d = -d;
		}
		printn(d, 10);
	}
	break;
	case 'p': {
    long adp = va_arg(list, int);
		printptr(adp);
	}
	break;
case 'u': {
    long adx = va_arg(list, int);
		printn(adx, 16);
  }
	break;
case 'o': {
    long adx = va_arg(list, int);
		printn(adx, 8);
  }
	break;
case 'x': {
    long adx = va_arg(list, int);
		printn(adx, 16);
	}
	break;
	case 's': {
		char *s = va_arg(list, char*);
		if (s == 0) {
			s = "(null)";
		}
		while((c = *s++)) {
			putchar(c);
		}
	}
	}
//#if BOOGER
	// TODO: rethink
	goto loop;
//}
//#else
//	}
}
//#endif

/*
 * Print an unsigned integer in base b.
 */
int
printn (
    unsigned long n,		/* XXX */
    int b
)
{
	register unsigned long a;	/* XXX */

	if (n < 0) {	/* shouldn't happen */
		putchar('-');
		n = -n;
	}
	if ((a = n/b)) {
		printn(a, b);
  	}
	putchar(hexdigits[(int)(n%b)]);
}

// better later
int
printptr (long n) {
  putchar('0');
  putchar('x');
  printn(n, 16);
}



/*
 * Panic is called on unresolvable
 * fatal errors.
 * It syncs, prints "panic: mesg" and
 * then loops.
 */
int
panic (char *fmt, ...)
{
        va_list list;
        va_start(list, fmt);

	// Less helpful now that panic is variadic.
	panicstr = fmt;
//	update();
	printf("panic: %s\n", list);
	spl7();
	for(;;) {
#if BOARD_nano
		led_alarm();
#endif
		// idle();
	}
}

/*
 * prdev prints a warning message of the
 * form "mesg on dev x/y".
 * x and y are the major and minor parts of
 * the device argument.
 */
int
prdev (char *str, int dev)
{

	printf("%s on dev %u/%u\n", str, major(dev), minor(dev));
}

/*
 * deverr prints a diagnostic from
 * a device driver.
 * It prints the device, block number,
 * and an octal word (usually some error
 * status register) passed as argument.
 */
int
deverror (register struct buf *bp, int o1, int o2)
{

	prdev("err", bp->b_dev);
	printf("bn=%D er=%o,%o\n", bp->b_blkno, o1, o2);
}
