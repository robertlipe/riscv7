/* UNIX V7 source code: see /COPYRIGHT or www.tuhs.org for details. */
#include <sys/types.h>
#ifndef	DIRSIZ
#define	DIRSIZ	14
#endif
struct	direct
{
	ino_t	d_ino;
	char	d_name[DIRSIZ];
};
