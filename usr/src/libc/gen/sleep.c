/* UNIX V7 source code: see /COPYRIGHT or www.tuhs.org for details. */

#include <signal.h>
#include <setjmp.h>

static jmp_buf jmp;
static int sleepx();

sleep(n)
unsigned n;
{
	unsigned altime;
	int (*alsig)() = SIG_DFL;

	if (n==0)
		return;
	altime = alarm(1000);	/* time to maneuver */
	if (setjmp(jmp)) {
		signal(SIGALRM, alsig);
		alarm(altime);
		return;
	}
	if (altime) {
		if (altime > n)
			altime -= n;
		else {
			n = altime;
			altime = 1;
		}
	}
	alsig = signal(SIGALRM, sleepx);
	alarm(n);
	for(;;)
		pause();
	/*NOTREACHED*/
}

static
int sleepx()
{
	longjmp(jmp, 1);
}
