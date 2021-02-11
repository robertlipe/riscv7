#include "../../../sys/h/riscv-asm.h"
ENTRY(link)
  li a7, 9
  ecall
  SET_ERRNO
  ret
END(link)
