/* UNIX V7 source code: see /COPYRIGHT or www.tuhs.org for details. */
#include <string.h>
#include <stddef.h>
/*
 * Returns the number of
 * non-NULL bytes in string argument.
 */

size_t strlen(s)
register const char *s;
{
	size_t n;

	n = 0;
	while (*s++)
		n++;
	return(n);
}
