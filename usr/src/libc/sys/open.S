  #include "../../../sys/h/riscv-asm.h"
  ENTRY(open)
  li a7, 5
  ecall
  SET_ERRNO
  ret
  END(open)
