#include "../../../sys/h/riscv-asm.h"
  ENTRY(chdir)
  li a7, 12
  ecall
  SET_ERRNO
  ret
  END(chdir)
