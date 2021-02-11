  .global _exit
  .global exit
  _exit:
  exit:
  li a7, 1
  ecall
  ret
