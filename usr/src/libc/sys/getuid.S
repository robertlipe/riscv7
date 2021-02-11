#include "../../../sys/h/riscv-asm.h"
ENTRY(getuid)
  getuid:
  li a7, 24
  ecall
  ret
END(getuid)
