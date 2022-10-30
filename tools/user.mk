CFLAGS += -nostdinc -I$(realpath $(ROOT)/../../usr/include)
LIBC := -nostdlib -L../libc -lc
LD = $(PREFIX)ld
STARTUP=../libc/csu/crt0.o
XLDFLAGS=-melf32lriscv

# LDFLAGS = -L../libc -lc
# LDFLAGS = -nostartfiles -nodefaultlibs -march=rv32imac -mabi=ilp32 # -L../libc -lc

# Even when we're calling the linker, do it through the compiler driver.
%: %.o
	$(CC) $(CFLAGS) -o $@ $^ $(LIBC) -lgcc # link
%: %.c
	$(CC) $(CFLAGS) -o $@ $^ $(LIBC) -lgcc # compile
