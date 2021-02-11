#include "../../../sys/h/riscv-asm.h"
  ENTRY(setgid)
  li a7, 46
  ecall
  SET_ERRNO
  ret
  END(setgid)
