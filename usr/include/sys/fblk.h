/* UNIX V7 source code: see /COPYRIGHT or www.tuhs.org for details. */
#include <sys/param.h>
struct fblk
{
	int    	df_nfree;
	daddr_t	df_free[NICFREE];
};
