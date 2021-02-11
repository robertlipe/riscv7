  .global _chmod
  .global chmod
  _chmod:
  chmod:
  li a7, 15
  ecall
  ret
