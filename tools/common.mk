# TOOLS=/Volumes/v32/riscv

# Flags and variables suitable for ALL builds, kernel or user. Probably
# shouldn't be used alone, but rather in a file that defines rules.
# It's written to be composable, with other files adding to these.

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
   -DBOARD_$(BOARD) \
   -Wno-implicit-int \
   -Wno-implicit-function-declaration \
   -Wno-return-type \
   -MD \
   -O \
   -fno-omit-frame-pointer \
   -march=rv32imac  \
   -mabi=ilp32 \
   -g2

ASFLAGS += \
    -march=rv32imac \
    -mabi=ilp32
