/* UNIX V7 source code: see /COPYRIGHT or www.tuhs.org for details. */

#include	<stdio.h>
#include	<errno.h>

static int create(char* file, int rw);

FILE *
_endopen(file, mode, iop)
	char *file, *mode;
	FILE *iop;
{
	extern int errno;
	int rw, f;

	if (iop == NULL)
		return(NULL);

	rw = mode[1] == '+';

	switch (*mode) {

	case 'w':
		f = create(file, rw);
		break;

	case 'a':
		if ((f = open(file, rw? 2: 1)) < 0) {
			if (errno == ENOENT)
				f = create(file, rw);
		}
		lseek(f, 0L, 2);
		break;

	case 'r':
		f = open(file, rw? 2: 0);
		break;

	default:
		return(NULL);
	}

	if (f < 0)
		return(NULL);

	iop->_cnt = 0;
	iop->_file = f;

	if (rw)
		iop->_flag |= _IORW;
	else if(*mode == 'r')
		iop->_flag |= _IOREAD;
	else
		iop->_flag |= _IOWRT;

	return(iop);
}

static int
create(file, rw)
	char *file;
	int rw;
{
	int f;

	f = creat(file, 0666);
	if (rw && f>=0) {
		close(f);
		f = open(file, 2);
	}
	return(f);
}
