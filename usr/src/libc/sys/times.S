#include "../../../sys/h/riscv-asm.h"
  ENTRY(times)
  li a7, 43
  ecall
  SET_ERRNO
  ret
  END(times)
