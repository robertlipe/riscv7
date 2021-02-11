#include "../../../sys/h/riscv-asm.h"
  ENTRY(pipe)
  li a7, 42
  ecall
  ret
  END(pipe)
