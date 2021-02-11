  .global _sbrk
  .global sbrk
  _sbrk:
  sbrk:
  li a7, 17
  ecall
  ret
