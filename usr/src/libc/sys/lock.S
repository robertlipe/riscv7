#include "../../../sys/h/riscv-asm.h"
ENTRY(lock)
  li a7, 53
  ecall
  ret
END(lock)
