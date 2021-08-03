set confirm off
# set architecture riscv:rv32

define reconnect
target extended-remote 127.0.0.1:2331
set remote memory-write-packet-size 1024
set remote memory-write-packet-size fixed
set backtrace limit 32

# set $pc = 0
set print asm-demangle on
symbol-file ../sd0unix
file ../sd0unix
# set disassemble-next-line on
set disassemble-next-line auto
end
reconnect 

# Configure SEGGER Semihosting. *shouldn't* be harmful if you don't the HW.
monitor speed auto
monitor semihosting ioclient 3
# eval "monitor exec SetRTTAddr %p", &_SEGGER_RTT

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

# Reload the firmware from scratch over the debugger. Very fast.
define reload
  load ../sd0unix
  reboot
end

# Restarts the firmware from (XIP) Flash. A warm boot.
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
