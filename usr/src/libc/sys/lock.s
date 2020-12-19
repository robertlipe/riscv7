  .global _lock
  .global lock
  _lock:
  lock:
  li a7, 53
  ecall
  ret
