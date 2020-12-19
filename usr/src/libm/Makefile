
include ../../../tools/common.mk

CFLAGS += -nostdinc -I../../include

SOURCES := $(wildcard *.c)

OBJECTS := $(SOURCES:.c=.o)

libm.a: $(OBJECTS)
	$(AR) rc libm.a $(OBJECTS)
	$(RANLIB) libm.a
