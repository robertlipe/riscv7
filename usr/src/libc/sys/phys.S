#include "../../../sys/h/riscv-asm.h"
  ENTRY(phys)
  li a7, 52
  ecall
  ret
  END(phys)
