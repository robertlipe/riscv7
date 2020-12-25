symbol-file ../md0unix
file ../md0unix

set architecture riscv:rv32
target extended-remote 127.0.0.1:25502
set remote memory-write-packet-size 1024
set remote memory-write-packet-size fixed


break panic
p $pc = reset_handler

