#include "../../../sys/h/riscv-asm.h"
  ENTRY(times)
  li a7, 43
  ecall
  ret
  END(times)
