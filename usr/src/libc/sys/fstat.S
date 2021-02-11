#include "../../../sys/h/riscv-asm.h"
  ENTRY(fstat)
  li a7, 28
  ecall
  SET_ERRNO
  ret
  END(fstat)
