/* UNIX V7 source code: see /COPYRIGHT or www.tuhs.org for details. */

/*
 * Return the ptr in sp at which the character c appears;
 * NULL if not found
 */

#include <string.h>

const char *
index(const char *sp, int c)
{
	do {
		if (*sp == c)
			return(sp);
	} while (*sp++);
	return(NULL);
}
