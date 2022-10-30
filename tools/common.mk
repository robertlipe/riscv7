# TOOLS=/Volumes/v32/riscv

# Flags and variables suitable for ALL builds, kernel or user. Probably
# shouldn't be used alone, but rather in a file that defines rules.
# It's written to be composable, with other files adding to these.

ifeq ($(BOARD), nano)
    ABI=\
       -march=rv32imac \
       -mabi=ilp32
    CPU=gd32v
else ifeq ($(BOARD), esp32c3)
   ABI=\
      -march=rv32imac \
      -mabi=ilp32
   CPU=esp32c3
else ifeq ($(BOARD), visionfive)
   ABI=\
      -march=rv64imac \
      -mabi=lp64
      -mfloat-abi=softfp \
   CPU=jh7110
else # ??? How to throw an error here?
endif



PREFIX = riscv64-unknown-elf-
CC = $(PREFIX)gcc
AS = $(PREFIX)gcc -c
LD = $(PREFIX)gcc
AR = $(PREFIX)ar
RANLIB = $(PREFIX)ranlib
OBJDUMP = $(PREFIX)objdump
OBJCOPY = $(PREFIX)objcopy
NM = $(PREFIX)nm
QEMU = qemu-system-riscv64

ROOT = $(PWD)/../

CFLAGS=\
   -DBOARD=$(BOARD) \
   -DBOARD_$(BOARD)=1 \
   -DCPU_TYPE_$(CPU)=1 \
   -Wno-implicit-int \
   -Wno-implicit-function-declaration \
   -Wno-return-type \
   -MD \
   -O2 \
   -fno-omit-frame-pointer \
   -g2 \
   $(ABI)

ASFLAGS += \
   $(ABI)
