# TOOLS=/Volumes/v32/riscv

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

# This is a hack. I couldn't get the multilibbed ld to play nice.
# I think that ld is making 32 bit files in the .a of the .o's.
# resulting in  target emulation elf64-littleriscv' does not matchelf32-littleriscv'
# Just use a non-multilibbed ld for now...
# LD=/Applications/SEGGER\ Embedded\ Studio\ for\ RISC-V\ 4.52c/gcc/riscv32-none-elf/bin/ld
# LD=/Applications/SEGGER\ Embedded\ Studio\ for\ RISC-V\ 5.10b/gcc/riscv32-none-elf/bin/ld

ROOT = $(PWD)/../

#   -march=rv32imac  \
#   -mabi=ilp32 \

CFLAGS=\
   -Wno-implicit-int \
   -Wno-implicit-function-declaration \
   -Wno-return-type \
   -MD \
   -O \
   -fno-omit-frame-pointer \
   -march=rv32imac  \
   -mabi=ilp32 \
   -g2

# Not in plau. Segger 32-bit linker used instead.
#LDFLAGS += \
#    -march=elf32lriscv \
#    -mabi=ilp32

ASFLAGS += \
    -march=rv32imac \
    -mabi=ilp32

#C_OBJECTS   += $(notdir $(C_SOURCES:.c=.o))
#AGM_OBJECTS += $(notdir $(ASM_SOURCES:.S=.o))
##%.o: %.c
#	@echo "CC $<"
#	@$(CC) -c $(CFLAGS) -MMD -MP $< -o $@
#%.o: %S
#	@echo "AS $<"
#	@$(CC) -c $(CFLAGS) -MMD -MP $< -o $@



# KCFLAGS = $(CFLAGS) \
#    -fno-hosted \

#CC=/Applications/SEGGER\ Embedded\ Studio\ for\ RISC-V\ 4.52c//bin/cc
#LD=/Applications/SEGGER\ Embedded\ Studio\ for\ RISC-V\ 4.52c//bin/ld
# CFLAGS=-g -Os -DNCPU=2
