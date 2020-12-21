
set confirm off
# set architecture riscv:rv32
target extended-remote 127.0.0.1:2331
set remote memory-write-packet-size 1024
set remote memory-write-packet-size fixed
set backtrace limit 32
monitor speed auto

# set $pc = 0
set print asm-demangle on
symbol-file ../md0unix
file ../md0unix
# set disassemble-next-line on
set disassemble-next-line auto

#break death
#break panic
# break printn
#break machinetrap
# disassemble _entry
# alias reboot = p $pc = 0
#break newproc
# b configure_eclic

break panic
# break main.c:77

define reload
  load ../md0unix
end

define reboot
  set $pc = 0
  cont
end

define dr
  p/x *(GPIO*) 0x40010800U
  p/x *(GPIO*) 0x40011000U
end

# This isn't debugged at all. It's a placeholder.
define panic
  set $r=(uint32_t*) registers
  printf "RA      x1      x2 ....\n"
  printf "%08x %08x %08x\n", $r[1], $r[2], $r[3]
  info line *($mepc)
  info line *(ra)
  set $pc = $r_mepc
  set $ra = $r_ra;
  set bt limit 8
  bt
end


b LCD_VerticalScroll
