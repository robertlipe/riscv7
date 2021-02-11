#  FIXME: this is a placeholder
#include "../../../sys/h/riscv-asm.h"
ENTRY(setjmp)
  li a7, 99
  ecall
  ret
END(setjmp)

