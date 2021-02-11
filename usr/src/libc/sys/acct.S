#include "../../../sys/h/riscv-asm.h"
  ENTRY(acct)
  li a7, 51
  ecall
  ret
  END(acct)
