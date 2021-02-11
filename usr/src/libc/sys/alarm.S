#include "../../../sys/h/riscv-asm.h"
  ENTRY(alarm)
  li a7, 27
  ecall
  ret
  END(alarm)
