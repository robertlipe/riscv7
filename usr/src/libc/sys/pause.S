#include "../../../sys/h/riscv-asm.h"
  ENTRY(pause)
  li a7, 29
  ecall
  ret
  END(pause)
