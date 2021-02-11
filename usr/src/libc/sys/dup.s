  .global _dup
  .global dup
  _dup:
  dup:
  li a7, 41
  ecall
  ret

#  FIXME: this is a placeholder
.global dup2
dup2:
  li a7, 99
  ecall
  ret
