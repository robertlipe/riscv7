#include "../../../sys/h/riscv-asm.h"
  ENTRY(execve)
  li a7, 59
  ecall
  ret
  END(execve)
