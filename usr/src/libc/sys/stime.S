#include "../../../sys/h/riscv-asm.h"
  ENTRY(stime)
  li a7, 25
  ecall
  ret
  END(stime)
