include ../../../tools/common.mk
include ../../../tools/user.mk

CFLAGS += -I../../include

GEN_SOURCES := $(wildcard gen/*.c)
STDIO_SOURCES := $(wildcard stdio/*.c sys/*.c)
SYS_SOURCES := $(wildcard csu/*.s crt/cerror.s)
ASM_SOURCES := $(wildcard gen/*.S sys/*.S)

C_SOURCES := $(GEN_SOURCES) $(STDIO_SOURCES)
S_SOURCES := $(SYS_SOURCES) $(ASM_SOURCES)

OBJECTS := $(C_SOURCES:.c=.o) $(S_SOURCES:.s=.o) $(ASM_SOURCES:.S=.o) $(SYS_SOURCES:.s=.o)
INCLUDES := $(OBJECTS:.o=.d)

libc.a: $(OBJECTS) Makefile
	$(AR) rc libc.a $(OBJECTS)
	$(RANLIB) libc.a

# Somehow $(INCLUDES) includes the .S files, so deleting that leads to pain.
# just harcode the object list now.
.PHONY:
clean:
	rm -f stdio/*.o gen/*.o sys/*.o csu/*.o crt/*.o libc.a
	# This clobbers source and I don't want to debug it tonight
	# rm -f $( OBJECTS) $( INCLUDES) libc.a

-include *.d
