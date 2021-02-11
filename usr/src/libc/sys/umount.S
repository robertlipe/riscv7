  .global _umount
  .global umount
  _umount:
  umount:
  li a7, 22
  ecall
  ret
