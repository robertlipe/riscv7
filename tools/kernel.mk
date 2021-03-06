# included after common.mk for kernel-specfic flags

# GCC10 disallows common. conf.o depends on this. Use -fcommon
# no-host, freestanding, nostdlib = kernel mode.
CFLAGS += \
   -fno-hosted \
   -ffreestanding \
   -nostdlib \
   -mno-relax \
   -fcommon \
   -DNCPU=2


JUNK= \
   -mcmodel=medany \

# function and data sections do funny things on final link.
CFLAGS += \
    -Wno-implicit-function-declaration \
    -Wno-implicit-int \
    -fno-function-sections \
    -fno-data-sections


# LDFLAGS += -Wl,--gc-sections -nostartfiles -nodefaultlibs -nodefaultlibs -z muldefs -march=rv32imac -mabi=ilp32
LDFLAGS += -Wl,--gc-sections -nostartfiles -nodefaultlibs -march=rv32imac -mabi=ilp32
