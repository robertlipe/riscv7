/* UNIX V7 source code: see /COPYRIGHT or www.tuhs.org for details. */
#include <stdio.h>
#include <stdlib.h>

main(argc, argv)
char **argv;
{
	extern errno;
	if (argc > 1)
		acct(argv[1]);
	else
		acct((char *)0);
	if (errno) {
		perror("accton");
		exit(1);
	}
	exit(0);
}
