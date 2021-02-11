#include "../../../sys/h/riscv-asm.h"
ENTRY(lock)
  li a7, 53
  ecall
  SET_ERRNO
  ret
END(lock)
