#include "../../../sys/h/riscv-asm.h"
ENTRY(umount)
  li a7, 22
  ecall
  ret
END(umount)
