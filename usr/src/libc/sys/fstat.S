  .global _fstat
  .global fstat
  _fstat:
  fstat:
  li a7, 28
  ecall
  ret
