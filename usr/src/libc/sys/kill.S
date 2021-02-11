#include "../../../sys/h/riscv-asm.h"
  ENTRY(kill)
  li a7, 37
  ecall
  ret
  END(kill)
