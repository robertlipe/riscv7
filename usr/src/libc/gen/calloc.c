/* UNIX V7 source code: see /COPYRIGHT or www.tuhs.org for details. */

/*	calloc - allocate and clear memory block
*/
#define CHARPERINT (sizeof(int)/sizeof(char))
#include <stddef.h>
// Intentionaly don't do this because this cfree() predates ANSI convention
#include <stdlib.h>
#include <stddef.h>

void*
calloc(num, size)
unsigned long num, size;
{
	register char *mp;
	// char *malloc();
	register int *q;
	register m;

	num *= size;
	mp = malloc(num);
	if(mp == NULL)
		return(NULL);
	q = (int *) mp;
	m = (num+CHARPERINT-1)/CHARPERINT;
	while(--m>=0)
		*q++ = 0;
	return(mp);
}

cfree(p, num, size)
char *p;
unsigned num, size;
{
	free(p);
}
