  .global _getgid
  .global getgid
  _getgid:
  getgid:
  li a7, 47
  ecall
  ret
