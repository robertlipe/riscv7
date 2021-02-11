include ../../../tools/common.mk
include ../../../tools/user.mk

CFLAGS += -I../../include

GEN_SOURCES := $(wildcard gen/*.c)
STDIO_SOURCES := $(wildcard stdio/*.c sys/*.c)
SYS_SOURCES := $(wildcard sys/*s csu/*.s crt/cerror.s)
ASM_SOURCES := $(wildcard gen/*.S)

C_SOURCES := $(GEN_SOURCES) $(STDIO_SOURCES)
S_SOURCES := $(SYS_SOURCES)

OBJECTS := $(C_SOURCES:.c=.o) $(S_SOURCES:.s=.o) $(ASM_SOURCES:.S=.o) $(SYS_SOURCES:.s=.o)
INCLUDES := $(OBJECTS:.o=.d)

libc.a: $(OBJECTS) Makefile
	$(AR) rc libc.a $(OBJECTS)
	$(RANLIB) libc.a

.PHONY:
clean:
	rm -f $(OBJECTS) $(INCLUDES) libc.a

-include *.d
