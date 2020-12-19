  .global _chdir
  .global chdir
  _chdir:
  chdir:
  li a7, 12
  ecall
  ret
