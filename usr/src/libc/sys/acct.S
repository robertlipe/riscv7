#include "../../../sys/h/riscv-asm.h"
  ENTRY(acct)
  li a7, 51
  ecall
  SET_ERRNO
  ret
  END(acct)
