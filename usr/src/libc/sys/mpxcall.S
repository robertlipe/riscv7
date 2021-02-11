#include "../../../sys/h/riscv-asm.h"
// FIXME(robertl): I don't think anything in the tree actually CALLS this.
  ENTRY(Xmpxcall)
  li a7, 56
  ecall
  ret
  END(Xmpxcall)