#include "../../../sys/h/riscv-asm.h"
  ENTRY(setgid)
  li a7, 46
  ecall
  ret
  END(setgid)
