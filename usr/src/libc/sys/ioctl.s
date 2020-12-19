  .global _ioctl
  .global ioctl
  _ioctl:
  ioctl:
  li a7, 54
  ecall
  ret
