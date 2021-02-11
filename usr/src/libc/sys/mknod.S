#include "../../../sys/h/riscv-asm.h"
ENTRY(mknod)
  li a7, 14
  ecall
  SET_ERRNO
  ret
END(mknod)
