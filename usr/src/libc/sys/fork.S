#include "../../../sys/h/riscv-asm.h"
#  FIXME: this is a placeholder
ENTRY(fork)
  li a7, 99
  ecall
  SET_ERRNO
  ret
END(fork)
