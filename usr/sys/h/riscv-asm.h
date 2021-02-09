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
