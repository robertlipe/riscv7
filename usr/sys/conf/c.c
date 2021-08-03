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
int	sdopen(), sdstrategy();
struct	buf	sdtab;
int	mdstrategy();
struct	buf	mdtab;
struct	bdevsw	bdevsw[] =
{
	sdopen,  nulldev, sdstrategy, &sdtab,	/* sd = 0 */
	nodev, nodev, nodev, 0, /* fd = 1 */
	nulldev, nulldev, mdstrategy, &mdtab, 	/* md = 2 */
	0
};

int	scopen(), scclose(), scread(), scwrite(), scioctl();
int	mmread(), mmwrite();
int	syopen(), syread(), sywrite(), sysioctl();
int	serialopen(), serialclose(), serialread(), serialwrite(), serialioctl();
struct	tty	serial[1];
int	sdread(), sdwrite();
int	mdread(), mdwrite();
int	cdread();

struct	cdevsw	cdevsw[] =
{
	scopen, scclose, scread, scwrite, scioctl, nulldev, 0,	/* console = 0 */
	nulldev, nulldev, mmread, mmwrite, nodev, nulldev, 0, 	/* mem = 1 */
	syopen, nulldev, syread, sywrite, sysioctl, nulldev, 0,	/* tty = 2 */
	nodev, nodev, nodev, nodev, nodev, nulldev, 0, /* sr = 3 */
	serialopen, serialclose, serialread, serialwrite, serialioctl, nulldev, serial,	/* serial = 4 */
	sdopen, nulldev, sdread, sdwrite, nodev, nulldev, 0,	/* sd = 5 */
	nodev, nodev, nodev, nodev, nodev, nulldev, 0, /* fd = 6 */
	nulldev, nulldev, mdread, mdwrite, nodev, nulldev, 0,	/* md = 7 */
	nulldev, nulldev, cdread, nodev, nodev, nulldev, 0,	/* cd = 8 */
	0
};

int	ttyopen(), ttyclose(), ttread(), ttwrite(), ttyinput(), ttstart();
struct	linesw	linesw[] =
{
	ttyopen, nulldev, ttread, ttwrite, nodev, ttyinput, ttstart, /* 0 */
	0
};
dev_t	rootdev	= makedev(0, 56);
dev_t	swapdev	= makedev(2, 57);
dev_t	pipedev = makedev(0, 56);
int	nldisp = 1;
daddr_t	swplo	= 2880;
int	nswap	= 32000;
	
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

