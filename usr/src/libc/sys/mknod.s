  .global _mknod
  .global mknod
  _mknod:
  mknod:
  li a7, 14
  ecall
  ret
