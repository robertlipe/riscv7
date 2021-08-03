/* UNIX V7 source code: see /COPYRIGHT or www.tuhs.org for details. */
/* Changes: Copyright (c) 2007 Robert Nordier. All rights reserved. */

#include <stdio.h>
#include <string.h>

#define CHAR	01
#define BLOCK	02
#define ROOT	040
#define	SWAP	0100
#define	PIPE	0200

char *tables[] = 
{
	// This is a lie. Stack is handled in kernel.ld
	"\n// entry.S needs one stack per CPU. \
	\n//__attribute__ ((aligned (16))) char _stack0[4096 * NCPU]; \
	\n// scratch for timer interrupt, one per CPU. \
	\n//__attribute__ ((aligned (16))) char mscratch0[32 * NCPU]; \
	\n",
	0
};

char	*btab[] =
{
	"sd",
	"fd",
	"md",
	0
};
char	*ctab[] =
{
	"console",
	"mem",
	"tty",
	"sr",
	"serial",
	"sd",
	"fd",
	"md",
	"cd",
	0
};
struct tab
{
	char	*name;
	int	count;
	int	key;
	char	*coded;
	char	*codee;
	char	*codef;
	char	*codeg;
} table[] =
{
	"console",
	-1, CHAR,
	"",
	"	scopen, scclose, scread, scwrite, scioctl, nulldev, 0,",
	"",
	"int	scopen(), scclose(), scread(), scwrite(), scioctl();",

	"mem",
	-1, CHAR,
	"",
	"	nulldev, nulldev, mmread, mmwrite, nodev, nulldev, 0, ",
	"",
	"int	mmread(), mmwrite();",

	"tty",
	1, CHAR,
	"",
	"	syopen, nulldev, syread, sywrite, sysioctl, nulldev, 0,",
	"",
	"int	syopen(), syread(), sywrite(), sysioctl();",

	"sr",
	0, CHAR,
	"",
	"	sropen, srclose, srread, srwrite, srioctl, nulldev, sr,",
	"",
	"int	sropen(), srclose(), srread(), srwrite(), srioctl();\nstruct	tty	sr[1];",

	"serial",
	0, CHAR,
	"",
	"	serialopen, serialclose, serialread, serialwrite, serialioctl, nulldev, serial,",
	"",
	"int	serialopen(), serialclose(), serialread(), serialwrite(), serialioctl();\nstruct	tty	serial[1];",

	"sd",
	0, BLOCK+CHAR,
	"	sdopen,  nulldev, sdstrategy, &sdtab,",
	"	sdopen, nulldev, sdread, sdwrite, nodev, nulldev, 0,",
	"int	sdopen(), sdstrategy();\nstruct	buf	sdtab;",
	"int	sdread(), sdwrite();",

	"fd",
	0, BLOCK+CHAR,
	"	nulldev, nulldev, fdstrategy, &fdtab, ",
	"	nulldev, nulldev, fdread, fdwrite, nodev, nulldev, 0,",
	"int	fdstrategy();\nstruct	buf	fdtab;",
	"int	fdread(), fdwrite();",

	"md",
	0, BLOCK+CHAR,
	"	nulldev, nulldev, mdstrategy, &mdtab, ",
	"	nulldev, nulldev, mdread, mdwrite, nodev, nulldev, 0,",
	"int	mdstrategy();\nstruct	buf	mdtab;",
	"int	mdread(), mdwrite();",

	"cd",
	0, CHAR,
	"",
	"	nulldev, nulldev, cdread, nodev, nodev, nulldev, 0,",
	"",
	"int	cdread();",

	0
};

char	*stre[] =
{
	"#include \"../h/param.h\"",
	"#include \"../h/systm.h\"",
	"#include \"../h/buf.h\"",
	"#include \"../h/tty.h\"",
	"#include \"../h/conf.h\"",
	"#include \"../h/proc.h\"",
	"#include \"../h/text.h\"",
	"#include \"../h/dir.h\"",
	"#include \"../h/user.h\"",
	"#include \"../h/file.h\"",
	"#include \"../h/inode.h\"",
	"#include \"../h/acct.h\"",
	"",
	"int	nulldev();",
	"int	nodev();",
	0
};

char	*stre1[] =
{
	"struct	bdevsw	bdevsw[] =",
	"{",
	0,
};

char	*strf[] =
{
	"	0",
	"};",
	"",
	0,
};

char	*strf1[] =
{
	"",
	"struct	cdevsw	cdevsw[] =",
	"{",
	0,
};

char	strg[] =
{
"	0\n\
};\n\
dev_t	rootdev	= makedev(%d, %d);\n\
dev_t	swapdev	= makedev(%d, %d);\n\
dev_t	pipedev = makedev(%d, %d);\n\
int	nldisp = %d;\n\
daddr_t	swplo	= %ld;\n\
int	nswap	= %ld;\n\
"};

char	strg1[] =
{
"	\n\
struct	buf	buf[NBUF];\n\
struct	file	file[NFILE];\n\
struct	inode	inode[NINODE];\n"
};

char	*strg1a[] =
{
	"int	mpxchan();",
	"int	(*ldmpx)() = mpxchan;",
	0
};

char	strg2[] =
{
"struct	proc	proc[NPROC];\n\
struct	text	text[NTEXT];\n\
struct	buf	bfreelist;\n\
struct	acct	acctbuf;\n\
struct	inode	*acctp;\n"
};

char	*strh[] =
{
	"	0",
	"};",
	"",
	"int	ttyopen(), ttyclose(), ttread(), ttwrite(), ttyinput(), ttstart();",
	0
};

char	*stri[] =
{
	"int	pkopen(), pkclose(), pkread(), pkwrite(), pkioctl(), pkrint(), pkxint();",
	0
};

char	*strj[] =
{
	"struct	linesw	linesw[] =",
	"{",
	"	ttyopen, nulldev, ttread, ttwrite, nodev, ttyinput, ttstart, /* 0 */",
	0
};

char	*strk[] =
{
	"	pkopen, pkclose, pkread, pkwrite, pkioctl, pkrint, pkxint, /* 1 */",
	0
};

int	pack;
int	mpx;
int	rootmaj = -1;
int	rootmin;
int	swapmaj = -1;
int	swapmin;
int	pipemaj = -1;
int	pipemin;
long	swplo	= 4000;
int	nswap = 872;
int	pack;
int	nldisp = 1;

int main(void);
void puke(char *s[]);
int input(void);
int equal(char *a, char *b);

int 
main (void)
{
	register struct tab *p;
	register char *q;
	int i, n, ev;
	int flagf, flagb, dumpht;

	while(input());

	freopen("c.c", "w", stdout);
	/*
	 * declarations
	 */
	puke(tables);
	puke(stre);
	for (i=0; (q=btab[i]); i++) {
		for (p=table; p->name; p++)
		if (equal(q, p->name) &&
		   (p->key&BLOCK) && p->count && *p->codef)
			printf("%s\n", p->codef);
	}
	puke(stre1);
	for(i=0; (q=btab[i]); i++) {
		for(p=table; p->name; p++)
		if(equal(q, p->name) &&
		   (p->key&BLOCK) && p->count) {
			printf("%s	/* %s = %d */\n", p->coded, q, i);
			if(p->key & ROOT)
				rootmaj = i;
			if (p->key & SWAP)
				swapmaj = i;
			if (p->key & PIPE)
				pipemaj = i;
			goto newb;
		}
		printf("	nodev, nodev, nodev, 0, /* %s = %d */\n", q, i);
	newb:;
	}
	if (swapmaj == -1) {
		swapmaj = rootmaj;
		swapmin = rootmin;
	}
	if (pipemaj == -1) {
		pipemaj = rootmaj;
		pipemin = rootmin;
	}
	puke(strf);
	for (i=0; (q=ctab[i]); i++) {
		for (p=table; p->name; p++)
		if (equal(q, p->name) &&
		   (p->key&CHAR) && p->count && *p->codeg)
			printf("%s\n", p->codeg);
	}
	puke(strf1);
	for(i=0; (q=ctab[i]); i++) {
		for(p=table; p->name; p++)
		if(equal(q, p->name) &&
		   (p->key&CHAR) && p->count) {
			printf("%s	/* %s = %d */\n", p->codee, q, i);
			goto newc;
		}
		printf("	nodev, nodev, nodev, nodev, nodev, nulldev, 0, /* %s = %d */\n", q, i);
	newc:;
	}
	puke(strh);
	if (pack) {
		nldisp++;
		puke(stri);
	}
	puke(strj);
	if (pack)
		puke(strk);
	printf(strg, rootmaj, rootmin,
		swapmaj, swapmin,
		pipemaj, pipemin,
		nldisp,
		swplo, nswap);
	puts(strg1);
	if (!mpx)
		puke(strg1a);
	puts(strg2);
	if(rootmaj < 0)
		fprintf(stderr, "No root device given\n");
}

void 
puke (char **s)
{
	char *c;

	while((c = *s++)) {
		printf("%s\n", c);
	}
}

int 
input (void)
{
	char line[100];
	register struct tab *q;
	int count, n;
	long num;
	char keyw[32], dev[32];

	if (fgets(line, 100, stdin) == NULL)
		return(0);
	count = -1;
        // RJL: The original here had
	// n = sscanf(line, "%d%s%s%ld", &count, keyw, dev, &num);
        // which seems impossible as the first entry is never a decimal.
	n = sscanf(line, "%s%s%ld", keyw, dev, &num);
	if (count == -1 && n>0) {
		count = 1;
		n++;
	}
	if (n<2)
		goto badl;
	if (keyw[0] == '#') return(1); // Commment: do nothing, but parse more
	for(q=table; q->name; q++)
	if(equal(q->name, keyw)) {
		if(q->count < 0) {
			fprintf(stderr, "%s: no more, no less\n", keyw);
			return(1);
		}
		q->count += count;
		if(q->count > 1) {
			q->count = 1;
			fprintf(stderr, "%s: only one\n", keyw);
		}
		return(1);
	}
	if (equal(keyw, "nswap")) {
		if (n<3)
			goto badl;
		if (sscanf(dev, "%ld", &num) <= 0)
			goto badl;
		nswap = num;
		return(1);
	}
	if (equal(keyw, "swplo")) {
		if (n<3)
			goto badl;
		if (sscanf(dev, "%ld", &num) <= 0)
			goto badl;
		swplo = num;
		return(1);
	}
	if (equal(keyw, "pack")) {
		pack++;
		return(1);
	}
	if (equal(keyw, "mpx")) {
		mpx++;
		return(1);
	}
	if(equal(keyw, "done"))
		return(0);
	if (equal(keyw, "root")) {
		if (n<4)
			goto badl;
		for (q=table; q->name; q++) {
			if (equal(q->name, dev)) {
				q->key |= ROOT;
				rootmin = num;
				return(1);
			}
		}
		fprintf(stderr, "Can't find root\n");
		return(1);
	}
	if (equal(keyw, "swap")) {
// fprintf(stderr, "XXX swap string: %s, ", keyw);
		if (n<4)
			goto badl;
		for (q=table; q->name; q++) {
			if (equal(q->name, dev)) {
				q->key |= SWAP;
				swapmin = num;
				return(1);
			}
		}
		fprintf(stderr, "Can't find swap\n");
		return(1);
	}
	if (equal(keyw, "pipe")) {
		if (n<4)
			goto badl;
		for (q=table; q->name; q++) {
			if (equal(q->name, dev)) {
				q->key |= PIPE;
				pipemin = num;
				return(1);
			}
		}
		fprintf(stderr, "Can't find pipe\n");
		return(1);
	}
	fprintf(stderr, "%s: cannot find\n", keyw);
	return(1);
badl:
	fprintf(stderr, "Bad line: %s", line);
	return(1);
}

int 
equal (char *a, char *b)
{
	return(!strcmp(a, b));
}
