#pragma once

#if (__riscv_xlen == 64)
  #define STORE     sd
  #define LOAD      ld
  #define REGBYTES   8
#else
  #define STORE     sw
  #define LOAD      lw
  #define REGBYTES   4
#endif

#define	ENTRY(sym) \
	.text; .globl sym; .type sym,@function; .align 4; sym: .cfi_startproc;
#define	END(sym) .cfi_endproc; .size sym, . - sym

// Ugh. user-space should not include this file at all, but it does, so here is
// a userspace thing. I *think* it is safe to clobber a1 here to do a.
// Worse, we have to rely on an obscure feature of GAS. Since we're #defining
// and string continuing, our line numbers never go up so you can't branch to
// '1f:' when you're o the same line. Fortunately '\@' is exactly the ticket.

.macro SET_ERRNO
 .comm __errno, 4
#	beqz a0, TL\@
	beqz a0, 1f
	la	a1, __errno
	sw	a1, (a1)
	li 	a0, -1
1:	
.endm

#define xSET_ERRNO \
	beqz a0, FL\@ ;  \
	la	a1, _errno; \
	sw	a1, (a1); \
	li 	a0, -1; \
FL\@:	ret
