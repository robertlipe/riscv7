#include "../../../sys/h/riscv-asm.h"
ENTRY(read)
  li a7, 3
  ecall
  ret
END(read)
