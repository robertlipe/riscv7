#include "../../../sys/h/riscv-asm.h"
  ENTRY(close)
  li a7, 6
  ecall
  SET_ERRNO
  ret
  END(close)
