#include "../../../sys/h/riscv-asm.h"
  ENTRY(close)
  li a7, 6
  ecall
  ret
  END(close)
