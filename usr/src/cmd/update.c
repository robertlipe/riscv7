/* UNIX V7 source code: see /COPYRIGHT or www.tuhs.org for details. */

/*
 * Update the file system every 30 seconds.
 * For cache benefit, open certain system directories.
 */

#include <signal.h>
#include <stdlib.h>

char *fillst[] = {
	"/bin",
	"/usr",
	"/usr/bin",
	0,
};

void dosync()
{
	sync();
	signal(SIGALRM, dosync);
	alarm(30);
}

main()
{
	char **f;

	if(fork())
		exit(0);
	close(0);
	close(1);
	close(2);
	for(f = fillst; *f; f++)
		open(*f, 0);
	dosync();
	for(;;)
		pause();
}
