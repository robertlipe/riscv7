/* UNIX V7 source code: see /COPYRIGHT or www.tuhs.org for details. */

#include	<stdio.h>
#include	<stdarg.h>
fprintf(FILE *iop, const char* fmt, ...)
{
#if 0
	_doprnt(fmt, &args, iop);
	return(ferror(iop)? EOF: 0);
#else
	va_list ap;
	va_start(ap, fmt);
	int ret = -1;
//	ret = printf_(iop, fmt, ap);
	va_end(ap);
	return ret;
	
#endif
}

