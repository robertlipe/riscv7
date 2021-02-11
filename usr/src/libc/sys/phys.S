#include "../../../sys/h/riscv-asm.h"
  ENTRY(phys)
  li a7, 52
  ecall
  SET_ERRNO
  ret
  END(phys)
