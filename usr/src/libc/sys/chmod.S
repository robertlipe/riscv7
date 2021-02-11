#include "../../../sys/h/riscv-asm.h"
  ENTRY(chmod)
  li a7, 15
  ecall
  ret
  END(chmod)
