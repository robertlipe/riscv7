#include "../../../sys/h/riscv-asm.h"
  ENTRY(access)
  li a7, 33
  ecall
  ret
  END(access)
