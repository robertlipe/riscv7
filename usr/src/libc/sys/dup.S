#include "../../../sys/h/riscv-asm.h"
  ENTRY(dup)
  li a7, 41
  ecall
  SET_ERRNO
  ret
  END(dup)

#  FIXME: this is a placeholder
  ENTRY(dup2)
  li a7, 99
  ecall
  SET_ERRNO
  ret
  END(dup2)
