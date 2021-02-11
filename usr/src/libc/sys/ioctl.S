#include "../../../sys/h/riscv-asm.h"
  ENTRY(ioctl)
  li a7, 54
  ecall
  ret
  END(ioctl)
