#include "../../../sys/h/riscv-asm.h"  .global _exit
  ENTRY(exit)
  li a7, 1
  ecall
  ret
  END(exit)
