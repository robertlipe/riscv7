#include "../h/param.h"
#include "../h/systm.h"
#include "../h/buf.h"
#include "../h/tty.h"
#include "../h/conf.h"
#include "../h/proc.h"
#include "../h/text.h"
#include "../h/dir.h"
#include "../h/user.h"
#include "../h/file.h"
#include "../h/inode.h"
#include "../h/acct.h"

int	nulldev();
int	nodev();
struct	bdevsw	bdevsw[] =
{
	nodev, nodev, nodev, 0, /* hd = 0 */
	nodev, nodev, nodev, 0, /* fd = 1 */
	nodev, nodev, nodev, 0, /* md = 2 */
	0
};

int	scopen(), scclose(), scread(), scwrite(), scioctl();
int	mmread(), mmwrite();
int	syopen(), syread(), sywrite(), sysioctl();

struct	cdevsw	cdevsw[] =
{
	scopen, scclose, scread, scwrite, scioctl, nulldev, 0,	/* console = 0 */
	nulldev, nulldev, mmread, mmwrite, nodev, nulldev, 0, 	/* mem = 1 */
	syopen, nulldev, syread, sywrite, sysioctl, nulldev, 0,	/* tty = 2 */
	nodev, nodev, nodev, nodev, nodev, nulldev, 0, /* sr = 3 */
	nodev, nodev, nodev, nodev, nodev, nulldev, 0, /* hd = 4 */
	nodev, nodev, nodev, nodev, nodev, nulldev, 0, /* fd = 5 */
	nodev, nodev, nodev, nodev, nodev, nulldev, 0, /* md = 6 */
	nodev, nodev, nodev, nodev, nodev, nulldev, 0, /* cd = 7 */
	0
};

int	ttyopen(), ttyclose(), ttread(), ttwrite(), ttyinput(), ttstart();
struct	linesw	linesw[] =
{
	ttyopen, nulldev, ttread, ttwrite, nodev, ttyinput, ttstart, /* 0 */
	0
};
dev_t	rootdev	= makedev(-1, 0);
dev_t	swapdev	= makedev(-1, 0);
dev_t	pipedev = makedev(-1, 0);
int	nldisp = 1;
daddr_t	swplo	= 4000;
int	nswap	= 
	
struct	buf	buf[NBUF];
struct	file	file[NFILE];
struct	inode	inode[NINODE];
int	mpxchan();
int	(*ldmpx)() = mpxchan;
struct	proc	proc[NPROC];
struct	text	text[NTEXT];
struct	buf	bfreelist;
struct	acct	acctbuf;
struct	inode	*acctp;
