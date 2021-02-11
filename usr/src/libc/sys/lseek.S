#include "../../../sys/h/riscv-asm.h"
ENTRY(lseek)
  li a7, 19
  ecall
  SET_ERRNO
  ret
END(lseek)
