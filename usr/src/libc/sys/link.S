#include "../../../sys/h/riscv-asm.h"
ENTRY(link)
  li a7, 9
  ecall
  ret
END(link)
