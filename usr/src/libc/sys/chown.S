#include "../../../sys/h/riscv-asm.h"
  ENTRY(chown)
  li a7, 16
  ecall
  ret
  END(chown)
