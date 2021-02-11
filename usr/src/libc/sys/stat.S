#include "../../../sys/h/riscv-asm.h"
  ENTRY(stat)
  li a7, 18
  ecall
  SET_ERRNO
  ret
  END(stat)
