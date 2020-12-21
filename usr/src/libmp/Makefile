include ../../../tools/common.mk

CFLAGS += -nostdinc -I../../include

SOURCES := $(wildcard *.c)

OBJECTS := $(SOURCES:.c=.o)

libmp.a: $(OBJECTS)
	$(AR) rc libmp.a $(OBJECTS)
	$(RANLIB) libmp.a
