#include "../../../sys/h/riscv-asm.h"
#  FIXME: this is a placeholder
ENTRY(signal)
  li a7, 99
  ecall
  SET_ERRNO
  ret
END(signal)
