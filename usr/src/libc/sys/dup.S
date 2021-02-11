#include "../../../sys/h/riscv-asm.h"
  ENTRY(dup)
  li a7, 41
  ecall
  ret
  END(dup)

#  FIXME: this is a placeholder
  ENTRY(dup2)
  li a7, 99
  ecall
  ret
  END(dup2)
