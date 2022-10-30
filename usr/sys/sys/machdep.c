/* UNIX V7 source code: see /COPYRIGHT or www.tuhs.org for details. */
/* Changes: Copyright (c) 1999 Robert Nordier. All rights reserved. */

#include "../h/param.h"
#include "../h/systm.h"
#include "../h/acct.h"
#include "../h/dir.h"
#include "../h/user.h"
#include "../h/inode.h"
#include "../h/proc.h"
#include "../h/seg.h"
#include "../h/types.h"
#include "../h/map.h"
#include "../h/reg.h"
#include "../h/buf.h"
#include "../sys/memlayout.h"

#if CPU_TYPE_gd32v == 1
#include "../sys/n200/riscv_encoding.h"
#include "../sys/n200/gd32vf103.h"
#include "../sys/n200/gd32v_lcd.h"
#include "../sys/n200/n200_eclic.h"
#include "../sys/n200/n200_timer.h"
#include "../sys/n200/ff.h"

uint32_t SystemCoreClock = 108000000;

#endif


extern int phymem;
extern long _kend;
extern mscratch0[];

#if NEITHER
#if 0
/*
 * Icode is the hex bootstrap
 * program executed in user mode
 * to bring up the system.
 */
int icode[] =
{
	0x186a106a,	/* push $initp; push $init */
	0xbb8006a,	/* push $0; mov $11,eax */
	0xcd000000,	/* int $0x30 */
	0xfeeb30,	/* jmp . */
	0x18,		/* initp: init; 0 */
	0x0,
	0x6374652f,	/* init: </etc/init\0> */
	0x696e692f,
	0x74
};
int	szicode = sizeof(icode);
#else
asm(R"(
 .text
 .globl icode
   la a0, init
   la a1, argv
   li a7, 11 # SYS_exec from sysent.c
   ecall
 exit:
   li a7, 1 # SYS_exit  from sysent.c
   ecall
   jal exit
 # char *argv[] = { init, 0 };
 argv:
   .long init
   .long 0
 init:
   .string "/init\0"
 .text
 .align 8
)");
#endif
#endif // NEITHER

// Global 'tick' value.
volatile uint32_t systick = 0;
// [...]


#if BOARD_nano

// System timer interrupt.
__attribute__( ( interrupt ) )
void eclic_mtip_handler( void ) {
  // Increment the global 'tick' value.
  systick++;
// logic inverted so GREEN lights quickly after boot.
  led_green(!(systick & 0x80));
  led_blue(systick & 0x100);
  led_red(systick & 0x040);

  clock(NULL);
  // Reset the 'mtime' value to zero. *This probably drifts.
  *( volatile uint64_t * )( TIMER_CTRL_ADDR + TIMER_MTIME ) = 0;

  // Visually pleasing, but makes a LOT of disruptive DMA and SPI traffic.
  // LCD_DrawPoint (systick % 160 ,0 ,systick *8);

  extern unsigned long LCD_time_to_blank;
  extern int LCD_blanked;
  if (systick > LCD_time_to_blank) {
       LCD_SetDisplayPower(0);
       LCD_blanked = 1;
  }
}

int
configure_eclic()
{
  // Set up the global timer to generate an interrupt every ms.
  // Figure out how many interrupts are available.
  uint32_t max_irqn = *( volatile uint32_t * )( ECLIC_ADDR_BASE + ECLIC_INFO_OFFSET );
  max_irqn &= ( 0x00001FFF );
  // Initialize the 'ECLIC' interrupt controller.
  eclic_init( max_irqn );
  eclic_mode_enable();
  // Set 'vector mode' so the timer interrupt uses the vector table.
  eclic_set_vmode( CLIC_INT_TMR );
  // Enable the timer interrupt (#7) with low priority and 'level'.
  eclic_enable_interrupt( CLIC_INT_TMR );
  eclic_set_irq_lvl_abs( CLIC_INT_TMR, 1 );
  eclic_set_irq_priority( CLIC_INT_TMR, 1 );

// TODO: see if this code can call clkstart... or wait for someone else to do so.
  // Set the timer's comparison value to (frequency / 1000).
  *( volatile uint64_t * )( TIMER_CTRL_ADDR + TIMER_MTIMECMP ) = ( TIMER_FREQ / 1000 );
  // Reset the timer value to zero.
  *( volatile uint64_t * )( TIMER_CTRL_ADDR + TIMER_MTIME ) = 0;

// This probably seems best left to someone else, too.
  // Re-enable interrupts globally.
  set_csr( mstatus, MSTATUS_MIE );
}
#endif  // BOARD_NANO


/*
 * Machine-dependent startup code
 */
int
startup (void)
{
	register i;
	long j;

	KASSERT(sizeof(unsigned int) == 4, "Invalid int size");
	KASSERT(sizeof(unsigned long) >= 4, "Invalid long size");
	KASSERT(sizeof(uint32_t) == 4, "Invalid uint32_t size");
	KASSERT(sizeof(uint64_t) == 8, "Invalid uint64_t size");
	KASSERT(lbolt == 0, "Lbolt wasn't zeroed");
	KASSERT(msgbuf[0] == 0, "msgbuf has trash");
extern char* msgbufp;
extern char msgbuf[];
	KASSERT(msgbuf == msgbufp, "msgbufp isn't &msgbufp");
#if BOARD_nano
  led_init();
  LCD_Init();
LCD_Clear(BLUE);

#endif

//        outb(0x3f2, 0xc); /* XXX turn floppy drive motor off */
  // set M Previous Privilege mode to Supervisor, for mret.
#if 0
  unsigned long x = get_mstatus();
  printf("Old Status: %x\n", (unsigned int) x);
#endif

//  x &= ~MSTATUS_MPP_MASK;
//  x |= MSTATUS_MPP_S;
//  set_mstatus(x);
//printf("New Status: %x\n", (unsigned int) x);

	// All exceptions go to machine mode.
	// printf("Old delegs: %x %s\n", get_medeleg(), get_mideleg());
#if 0
  set_medeleg(0xffff);
  set_mideleg(0xffff);
#endif

	/*
	 * free all of core
	 */
#if 0
	j = btoc(_kend) + 9; // RJL HACK
	j = &_kend; // RJL HACK
	for (i = 1; i < phymem/32; i++) {
		// if ((i >= 16 && i < j) || (i >= 160 && i < 256))
		//	continue;
		maxmem++;
		mfree(coremap, 1, i + j /* RJL HACK!*/);
	}
#else
	j = (long) &_kend + 5120;
phymem = 8192;
j = (long) &_kend + 1280;

	for (i = 1; i < phymem / 32; i++) {
		maxmem++;
		mfree(coremap, 1, i + j);
	}
#endif
	printf("mem = (%d) maxmem (%d)\n", maxmem, phymem);
	if(MAXMEM < maxmem)
		maxmem = MAXMEM;
	printf("adjusted mem = (%d)\n", ctob((long)maxmem));
	printf("Actual mem = (%d)\n", maxmem);
#if 0
// no VM == no swap.
	mfree(swapmap, nswap, 1 + j /* RJL HACK */);
#endif
	swplo--;

#if BOOGER
  // Initialize trap handler.
  extern void machinetrap();
  set_mtvec((unsigned long)&machinetrap);
  // enable machine-mode interrupts.
  set_mstatus(get_mstatus() /* | MSTATUS_MPP_M */ | MSTATUS_MIE);

  // enable machine-mode timer interrupts.
  set_mie(get_mie() | MIE_MTIE);
#endif
 // *(int *) 0xffd3 = 0;

#if 0
  extern long vtable;
  write_csr( CSR_MTVT, vtable );
  extern long default_interrupt_handler;
  write_csr( CSR_MTVEC, default_interrupt_handler);
#endif

#if CPU_TYPE_gd32v == 1
printf("Configuring eclic\n");
  configure_eclic();
#else
printf("enable interrupts somehow");
#endif

//Lcd_Init();
//LCD_Clear(BLUE);
#if 0

  FATFS fs;

  int mount_ok = 0;
  int fr = f_mount(&fs, "", 1);
    if (fr == 0)
        mount_ok = 0;
    else
        mount_ok = 1;

  FIL fil;
  fr = f_open(&fil, "1.txt", FA_READ);

  char ibuf[17];
  ibuf[0] = '\0';
  UINT br;
  fr = f_read(&fil, ibuf, sizeof(ibuf)-1, &br);
  ibuf[16] = '\0';

#if 1
  DIR dir;
  char path[32] = "/";
  static FILINFO fno;

  if (FR_OK == f_opendir(&dir, path)) {
    for(;;) {
      FRESULT res = f_readdir(&dir, &fno);
      if (res != FR_OK || fno.fname[0] == 0) break; 
      printf(" %s", fno.fname);
      if (fno.fattrib & AM_DIR) {
        printf("/");
      }
    }
    f_closedir(&dir);
  }
printf("sd buf: %d %s\n",br, ibuf);
#endif
#endif


// LCD_DrawRectangle(5, 10, 140, 75, CYAN);

  printf("startup done.");
}

/*
 * set up a physical address
 * into users virtual address space.
 */
int
sysphys (void)
{
	if(!suser())
		return;
	u.u_error = EINVAL;
}

/*
 * Start the clock.
 */
#if BOARD_nano
int
platform_clkstart (void)
{
//  KASSERT(lbolt == 0, "timer running too soon");

  // Set the timer's comparison value to (frequency / 1000).
  *( volatile uint64_t * )( TIMER_CTRL_ADDR + TIMER_MTIMECMP ) = ( TIMER_FREQ / 1000 );

  // Reset the timer value to zero.
  *( volatile uint64_t * )( TIMER_CTRL_ADDR + TIMER_MTIME ) = 0;

  // Re-enable interrupts globally.
//  set_mstatus(/*get_mstatus(), */ MSTATUS_MIE);
  set_csr( mstatus, MSTATUS_MIE );
}
#endif // BOARD_NANO

/*
 * Let a process handle a signal by simulating a call
 */
int
sendsig (caddr_t p, int signo)
{
	register unsigned n;

	n = u.u_ar0[ESP] - 4;
	grow(n);
	suword((caddr_t)n, u.u_ar0[EIP]);
	u.u_ar0[ESP] = n;
	u.u_ar0[EFL] &= ~TBIT;
	u.u_ar0[EIP] = (long)p;
}

#if 0
/*
 * Set the time from the real time clock.
 */
int
readrtc (void)
{
        static short days[] = {
    		0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334
	};
	int yr, mt, dm, hr, mn, sc;

	if ((inrtc(0xd) & 0x80) == 0)
		return;
	while (inrtc(0xa) & 0x80)
		;
	sc = getrtc(0);
	mn = getrtc(2);
	hr = getrtc(4);
	dm = getrtc(7);
	mt = getrtc(8);
	yr = getrtc(9);
	yr += yr >= 70 ? -70 : 30;
	time =	(((yr * 365 + (yr + 1) / 4 +
		days[mt - 1] + ((yr + 2) % 4 == 0 && mt >= 3) +
		dm - 1) * 24 + hr) * 60 + mn) * 60 + sc;
	time += TIMEZONE * 60;
}

int
getrtc (int addr)
{
	int x;

	x = inrtc(addr);
	return (x >> 4) * 10 + (x & 15);
}

int
inrtc (int addr)
{
	outb(0x70, addr);
	return inb(0x71);
}
#endif

// new RISC-V code starts here

reset_handler() { main() ; }

void platform_putc(int c) {
}

void platform_clkstart (void) {
}
