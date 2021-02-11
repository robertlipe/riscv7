#include "../../../sys/h/riscv-asm.h"
  ENTRY(fstat)
  li a7, 28
  ecall
  ret
  END(fstat)
