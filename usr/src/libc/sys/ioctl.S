#include "../../../sys/h/riscv-asm.h"
  ENTRY(ioctl)
  li a7, 54
  ecall
  SET_ERRNO
  ret
  END(ioctl)
