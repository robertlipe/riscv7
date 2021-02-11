#include "../../../sys/h/riscv-asm.h"
  ENTRY(unlink)
  li a7, 10
  ecall
  ret
  END(unlink)
