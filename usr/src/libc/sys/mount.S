#include "../../../sys/h/riscv-asm.h"
ENTRY(mount)
  li a7, 21
  ecall
  SET_ERRNO
  ret
END(mount)
