  .global _nice
  .global nice
  _nice:
  nice:
  li a7, 34
  ecall
  ret
