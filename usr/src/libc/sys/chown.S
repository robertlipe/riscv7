#include "../../../sys/h/riscv-asm.h"
  ENTRY(chown)
  li a7, 16
  ecall
  SET_ERRNO
  ret
  END(chown)
