include ../../../tools/common.mk

CFLAGS += -nostdinc -I../../include

SOURCES := $(wildcard *.c)

OBJECTS := $(SOURCES:.c=.o)
INCLUDES := $(OBJECTS:.o=.d)

libmp.a: $(OBJECTS)
	$(AR) rc libmp.a $(OBJECTS)
	$(RANLIB) libmp.a

clean:
	rm -f $(OBJECTS) $(INCLUDES) libmp.a

-include *.d
