include ../../../tools/common.mk
include ../../../tools/user.mk

CFLAGS += -I../../include

GEN_SOURCES := $(wildcard gen/*.c)
STDIO_SOURCES := $(wildcard stdio/*.c sys/*.c)
SYS_SOURCES := $(wildcard sys/*s csu/*.s crt/cerror.s)

C_SOURCES := $(GEN_SOURCES) $(STDIO_SOURCES)
S_SOURCES := $(SYS_SOURCES) $(CRT_SOURCES)

OBJECTS := $(C_SOURCES:.c=.o) $(S_SOURCES:.s=.o)

libc.a: $(OBJECTS)
	$(AR) rc libc.a $(OBJECTS)
	$(RANLIB) libc.a

clean:
	rm -f $(OBJECTS) libc.a
