#include "../../../sys/h/riscv-asm.h"
  ENTRY(profil)
  li a7, 44
  ecall
  ret
  END(profil)
