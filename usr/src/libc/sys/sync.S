#include "../../../sys/h/riscv-asm.h"
  ENTRY(sync)
  li a7, 36
  ecall
  ret
  END(sync)
