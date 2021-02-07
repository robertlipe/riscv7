include ../../../tools/common.mk
include ../../../tools/user.mk

CFLAGS += -I../../include

GEN_SOURCES := $(wildcard ./*.c)

OBJECTS := $(GEN_SOURCES:.c=.o)
INCLUDES := $(OBJECTS:.o=.d)

libdbm.a: $(OBJECTS)
	$(AR) rc libdbm.a $(OBJECTS)
	$(RANLIB) libdbm.a

clean:
	rm -f $(OBJECTS) $(INCLUDES) libdbm.a
