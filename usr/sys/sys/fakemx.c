/* UNIX V7 source code: see /COPYRIGHT or www.tuhs.org for details. */

/*
 * Fake multiplexor routines to satisfy references
 * if you don't want it.
 */

#include "../h/param.h"
#include "../h/dir.h"
#include "../h/user.h"
#include "../h/tty.h"
#include "../h/inode.h"
#include "../h/mx.h"

int 
sdata (struct chan *cp)
{
}

int 
mcttstart (struct tty *tp)
{
}

int 
mpxchan (void)
{
	u.u_error = EINVAL;
}

int 
mcstart (struct chan *p, caddr_t q)
{
}

int 
scontrol (struct chan *chan, int s, int c)
{
}
