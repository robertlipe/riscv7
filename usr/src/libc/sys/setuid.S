#include "../../../sys/h/riscv-asm.h"
  ENTRY(setuid)
  li a7, 23
  ecall
  SET_ERRNO
  ret
  END(setuid)
