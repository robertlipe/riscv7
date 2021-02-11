#include "../../../sys/h/riscv-asm.h"
ENTRY(write)
  li a7, 4
  ecall
SET_ERRNO
  ret
END(write)
