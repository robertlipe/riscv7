#include "../../../sys/h/riscv-asm.h"
  ENTRY(umask)
  li a7, 60
  ecall
  SET_ERRNO
  ret
  END(umask)
