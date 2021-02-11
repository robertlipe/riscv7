#include "../../../sys/h/riscv-asm.h"
  ENTRY(getpid)
  li a7, 20
  ecall
  ret
  END(getpid)
