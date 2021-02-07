
include ../../../tools/common.mk

CFLAGS += -nostdinc -I../../include

SOURCES := $(wildcard *.c)

OBJECTS := $(SOURCES:.c=.o)
INCLUDES := $(OBJECTS:.o=.d)

libm.a: $(OBJECTS)
	$(AR) rc libm.a $(OBJECTS)
	$(RANLIB) libm.a

clean:
	rm -f $(OBJECTS) $(INCLUDES) libm.a

-include *.d
