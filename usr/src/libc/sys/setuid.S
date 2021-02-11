#include "../../../sys/h/riscv-asm.h"
  ENTRY(setuid)
  li a7, 23
  ecall
  ret
  END(setuid)