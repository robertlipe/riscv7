/* UNIX V7 source code: see /COPYRIGHT or www.tuhs.org for details. */
#pragma once

// #include <sys/types.h>
// NO NO NO. FIXME This gets GCC's types.h, which does a #define
// physadr to physaddr which breaks the compilation of sig.c Ugh!
// That's wrong in a couple of ways...We should be getting our own types.h
// and a rename probably shouldn't tank us.

#ifndef	DIRSIZ
#define	DIRSIZ	14
#endif
struct	direct
{
	ino_t	d_ino;
	char	d_name[DIRSIZ];
};
