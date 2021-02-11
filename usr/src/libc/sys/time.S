#include "../../../sys/h/riscv-asm.h"
  ENTRY(time)
  li a7, 13
  ecall
  ret
  END(time)
