#include "../../../sys/h/riscv-asm.h"
  ENTRY(pipe)
  li a7, 42
  ecall
  SET_ERRNO
  ret
  END(pipe)
