#include "../../../sys/h/riscv-asm.h"
ENTRY(mknod)
  li a7, 14
  ecall
  ret
END(mknod)
