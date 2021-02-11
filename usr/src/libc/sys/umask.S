#include "../../../sys/h/riscv-asm.h"
  ENTRY(umask)
  li a7, 60
  ecall
  ret
  END(umask)
