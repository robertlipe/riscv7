
#if (__riscv_xlen == 64)
  #define STORE     sd
  #define LOAD      ld
  #define REGBYTES   8
#else
  #define STORE     sw
  #define LOAD      lw
  #define REGBYTES   4
#endif

#include "../sys/n200/riscv_encoding.h"

#define	EFAULT	14 // from ../h/user.h
#define	KERNBASE		0xc0000000
#define VM_MAXUSER_ADDRESS	KERNBASE

.data
ipl: .word 0

.text

# spl handling is totally untested
.globl spl0
spl0:
	lw a5, ipl
	lw a4, 0(a5)
	sw a0, 0(a5)
	mv a0, a4
	ret
.globl spl1
.globl spl4
.globl spl5
.globl spl6
.globl spl7
.globl splx
spl1:
	ret
spl4:
	ret
spl5:
	ret
spl6:
	ret
spl7:
	ret
splx:
 	ret
#if 1
.globl inb
.globl outb
.globl insw
.globl outsw
inb:
	ret
outb:
	ret
insw:
	ret
outsw:
 	ret
#endif

.globl copyin
copyin:
 	ret

.globl copyout
copyout:
 	ret

#.globl trap0
#trap0:
#	ret

#.globl trap
#trap:
#	ret

#.globl _resume
#_resume:
#	ret

.global savfp, restfp
savfp:
restfp:
	ret

.global idle
idle:
  wfi
	ret

.global waitloc
waitloc:
	ret

# I'm treating this like setjmp(). I could be wrong.
# int save(registers_array);
.global save
save:
#if 0
	/* Store the stack pointer */
	STORE	sp, 0(a0)
	addi	a0, a0, REGBYTES

	/* Store the general purpose registers and ra */
	STORE	s0, (0 * REGBYTES)(a0)
	STORE	s1, (1 * REGBYTES)(a0)
	STORE	s2, (2 * REGBYTES)(a0)
	STORE	s3, (3 * REGBYTES)(a0)
	STORE	s4, (4 * REGBYTES)(a0)
	STORE	s5, (5 * REGBYTES)(a0)
	STORE	s6, (6 * REGBYTES)(a0)
	STORE	s7, (7 * REGBYTES)(a0)
	STORE	s8, (8 * REGBYTES)(a0)
	STORE	s9, (9 * REGBYTES)(a0)
	STORE	s10, (10 * REGBYTES)(a0)
	STORE	s11, (11 * REGBYTES)(a0)
	STORE	ra,  (12 * REGBYTES)(a0)

	/* Return value */
	li	a0, 0
	ret
#else
	/* Store the general purpose registers and ra */
	STORE	ra, (0 * REGBYTES)(a0)
	STORE	sp, (1 * REGBYTES)(a0)
	STORE	s0, (2 * REGBYTES)(a0)
	STORE	s1, (3 * REGBYTES)(a0)
	STORE	s2, (4 * REGBYTES)(a0)
	STORE	s3, (5 * REGBYTES)(a0)
	STORE	s4, (6 * REGBYTES)(a0)
	STORE	s5, (7 * REGBYTES)(a0)
	STORE	s6, (8 * REGBYTES)(a0)
	STORE	s7, (9 * REGBYTES)(a0)
	STORE	s8, (10 * REGBYTES)(a0)
	STORE	s9, (11 * REGBYTES)(a0)
	STORE	s10, (12 * REGBYTES)(a0)
	STORE	s11, (13 * REGBYTES)(a0)

	/* Return value */
	li	a0, 0
	ret

#endif

# While save is setjmp, resume isn't quite longjmp.
# void resume(place_to_jump, registers_array);
.global resume
resume:
#if 0
	/* Restore the stack pointer */
	LOAD	sp, 0(a0)
	addi	a0, a0, REGBYTES

	/* Restore the general purpose registers and ra */
	LOAD	ra, (0 * REGBYTES)(a0)
	LOAD	sp, (1 * REGBYTES)(a0)
	LOAD	s2, (2 * REGBYTES)(a0)
	LOAD	s3, (3 * REGBYTES)(a0)
	LOAD	s4, (4 * REGBYTES)(a0)
	LOAD	s5, (5 * REGBYTES)(a0)
	LOAD	s6, (6 * REGBYTES)(a0)
	LOAD	s7, (7 * REGBYTES)(a0)
	LOAD	s8, (8 * REGBYTES)(a0)
	LOAD	s9, (9 * REGBYTES)(a0)
	LOAD	s10, (10 * REGBYTES)(a0)
	LOAD	s11, (11 * REGBYTES)(a0)
	LOAD	ra, (12 * REGBYTES)(a0)

	/* Load the return value */
	mv	a0, a1

	ret
#else
	LOAD	ra, (0 * REGBYTES)(a1)
	LOAD	sp, (1 * REGBYTES)(a1)
	LOAD	s0, (2 * REGBYTES)(a1)
	LOAD	s1, (3 * REGBYTES)(a1)
	LOAD	s2, (4 * REGBYTES)(a1)
	LOAD	s3, (5 * REGBYTES)(a1)
	LOAD	s4, (6 * REGBYTES)(a1)
	LOAD	s5, (7 * REGBYTES)(a1)
	LOAD	s6, (8 * REGBYTES)(a1)
	LOAD	s7, (9 * REGBYTES)(a1)
	LOAD	s8, (10 * REGBYTES)(a1)
	LOAD	s9, (11 * REGBYTES)(a1)
	LOAD	s10, (12 * REGBYTES)(a1)
	LOAD	s11, (13 * REGBYTES)(a1)
	#  Not clear why we have an a0 and an a1 since we save ra...
#	LOAD 	ra, (a0)
	ret

#endif

# If you're looking at this in a debugger, you need to be prepared to
# implement the handlers, ala https://github.com/freebsd/freebsd/blob/master/sys/riscv/riscv/support.S

// From Freebsd copuout.S
fsu_fault_nopcb:
	li	a0, EFAULT
	ret

 // int subyte(volatile void *, int)
.global subyte,suword
subyte:
	li	a2, VM_MAXUSER_ADDRESS
	bgt	a0, a2, fsu_fault_nopcb
	sb	a1, 0(a0)		/* Try storing the data */
	li	a0, 0			/* Success */
	ret				/* Return */
 // int subyte(volatile void *, int)
suword:
	li	a1, VM_MAXUSER_ADDRESS-1
	bgt	a0, a1, fsu_fault_nopcb
	sw	a1, 0(a0)		/* Try storing the data */
	li	a0, 0			/* Success */
	ret				/* Return */

.globl fubyte
fubyte:
	li	a1, VM_MAXUSER_ADDRESS
	bgt	a0, a1, fsu_fault_nopcb
	lbu	a0, 0(a0)		/* Try loading the data */
	ret;

.globl fuword
fuword:
	li	a1, VM_MAXUSER_ADDRESS
	bgt	a0, a1, fsu_fault_nopcb
	lw	a0, 0(a0)		/* Try loading the data */
	ret;


.globl invd, cli, sti
invd:
cli:
sti:
	ret

.globl addupc
addupc:
	ret;

// RJL: How much memory in (what units?) is in the system? Different per board.
.globl  phymem
#phymem: .word 1024
phymem: .word 32*1024

#.data
.globl  u
.align 10
#u:
# .set    u,U
.lcomm u, 944

.globl  pdir, upt
#.set    mem,0x40000000
#if 0
.set    pdir,0x7ff9a000
.set    upt,0x7ff9b000
#else
# Top of RAM = 0x6000 - 1
.set  upt, 0x02005a00
.set  pdir, 0x02005b00
#endif

#.set    kpt,0x7ff9c000
#.set    kptu,kpt+[925*4]
#.set    kptk,kpt+[927*4]
#.set    kstk,0x7ffa0000


#if 1
 .data
 .globl icode
 icode:
   la a0, init
   la a1, argv
   li a7, 11 # SYS_exec from sysent.c
   ecall
 exit:
   li a7, 1 # SYS_exit  from sysent.c
   ecall
   jal exit
 init:
   .ascii "/init\0"
 # char *argv[] = { init, 0 };
 .p2align 2
 argv:
   .long init
   .long 0

  .globl szicode
  szicode:
  .word . - icode

#endif
