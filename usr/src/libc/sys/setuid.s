  .global _setuid
  .global setuid
  _setuid:
  setuid:
  li a7, 23
  ecall
  ret
