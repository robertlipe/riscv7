#include "../../../sys/h/riscv-asm.h"
  ENTRY(ftime)
  li a7, 35
  ecall
  ret
  END(ftime)
