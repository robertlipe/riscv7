#include "../../../sys/h/riscv-asm.h"
  ENTRY(execve)
  li a7, 59
  ecall
  SET_ERRNO
  ret
  END(execve)
