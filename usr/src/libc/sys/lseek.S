  .global _lseek
  .global lseek
  _lseek:
  lseek:
  li a7, 19
  ecall
  ret
