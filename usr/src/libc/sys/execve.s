  .global _execve
  .global execve
  _execve:
  execve:
  li a7, 59
  ecall
  ret
