#include "../../../sys/h/riscv-asm.h"
  ENTRY(chroot)
  li a7, 61
  ecall
  SET_ERRNO
  ret
  END(chroot)
