  .global _write
  .global write
  _write:
  write:
  li a7, 4
  ecall
  ret
