#include "../../../sys/h/riscv-asm.h"
ENTRY(umount)
  li a7, 22
  ecall
  SET_ERRNO
  ret
END(umount)
