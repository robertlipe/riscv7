#CFLAGS += 
#   -L../libc -lc 
LD = $(PREFIX)ld
LDFLAGS=-melf32lriscv
# LDFLAGS = -nostartfiles -nodefaultlibs -march=rv32imac -mabi=ilp32 # -L../libc -lc

# yeah, this is bad...
%: %.o
	$(LD) $(LDFLAGS) $(STARTUP) $^  \
	-L../libc \
	-lc -L/usr/local/Cellar/riscv-gnu-toolchain/master/lib/gcc/riscv64-unknown-elf/10.2.0/rv32i/ilp32/ -lgcc -o $@
