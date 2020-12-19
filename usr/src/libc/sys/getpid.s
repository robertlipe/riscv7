  .global _getpid
  .global getpid
  _getpid:
  getpid:
  li a7, 20
  ecall
  ret
