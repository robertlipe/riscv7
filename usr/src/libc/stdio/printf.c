/* UNIX V7 source code: see /COPYRIGHT or www.tuhs.org for details. */

#include	<stdio.h>
#if 0
printf(fmt, args)
char *fmt;
{
	_doprnt(fmt, &args, stdout);
	return(ferror(stdout)? EOF: 0);
}
#else
int printf(const char* format, ...)
{
}
#endif
