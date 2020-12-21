  .global _ftime
  .global ftime
  _ftime:
  ftime:
  li a7, 35
  ecall
  ret
