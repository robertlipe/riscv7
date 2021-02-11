  .global _getuid
  .global getuid
  _getuid:
  getuid:
  li a7, 24
  ecall
  ret
