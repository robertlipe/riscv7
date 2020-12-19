  .global _umask
  .global umask
  _umask:
  umask:
  li a7, 60
  ecall
  ret
