#include "../../../sys/h/riscv-asm.h"
  ENTRY(wait)
  li a7, 7
  ecall
  SET_ERRNO
  ret
  END(wait)
