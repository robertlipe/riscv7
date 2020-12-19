  .global _sync
  .global sync
  _sync:
  sync:
  li a7, 36
  ecall
  ret
