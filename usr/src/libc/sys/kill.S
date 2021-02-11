#include "../../../sys/h/riscv-asm.h"
  ENTRY(kill)
  li a7, 37
  ecall
  SET_ERRNO
  ret
  END(kill)
