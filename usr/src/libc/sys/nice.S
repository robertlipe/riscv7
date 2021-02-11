#include "../../../sys/h/riscv-asm.h"
ENTRY(nice)
  li a7, 34
  ecall
  SET_ERRNO
  ret
END(nice)
