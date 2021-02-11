#include "../../../sys/h/riscv-asm.h"
  ENTRY(stime)
  li a7, 25
  ecall
  SET_ERRNO
  ret
  END(stime)
