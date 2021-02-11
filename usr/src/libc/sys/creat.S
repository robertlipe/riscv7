#include "../../../sys/h/riscv-asm.h"
  ENTRY(creat)
  li a7, 8
  ecall
  ret
  END(creat)
