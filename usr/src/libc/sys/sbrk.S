#include "../../../sys/h/riscv-asm.h"
  ENTRY(sbrk)
  li a7, 17
  ecall
  SET_ERRNO
  ret
  END(sbrk)
