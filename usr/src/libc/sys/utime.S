#include "../../../sys/h/riscv-asm.h"
  ENTRY(utime)
  li a7, 30
  ecall
  SET_ERRNO
  ret
  END(utime)
