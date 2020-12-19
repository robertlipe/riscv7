  .global _stat
  .global stat
  _stat:
  stat:
  li a7, 18
  ecall
  ret
