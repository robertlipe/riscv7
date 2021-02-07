/* UNIX V7 source code: see /COPYRIGHT or www.tuhs.org for details. */
#include <sys/types.h>
/*
 * Structure returned by ftime system call
 */
struct timeb {
	time_t	time;
	unsigned short millitm;
	short	timezone;
	short	dstflag;
};
