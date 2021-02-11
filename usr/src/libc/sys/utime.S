#include "../../../sys/h/riscv-asm.h"
  ENTRY(utime)
  li a7, 30
  ecall
  ret
  END(utime)
