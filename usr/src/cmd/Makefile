include ../../../tools/common.mk
include ../../../tools/user.mk

# It's hard work to make a Makefile look this easy...

# Sources that we know don't compile yet:
DONT_COMPILE=fsck.c prof.c graph.c sort.c
ALL_SRC_ := $(wildcard *.c)
ALL_SRC = $(filter-out $(DONT_COMPILE),$(ALL_SRC_))

ALL_OBJ := $(patsubst %.c, %.o, $(ALL_SRC))  # list of .o files
ALL_PRG := $(patsubst %.c, %, $(ALL_SRC))    # list of executables
ALL_DEPS := $(patsubst %.c, %.d, $(ALL_SRC))   # list of dependency files

all: $(ALL_PRG)

clean:
	rm -f $(sort $(ALL_OBJ) $(ALL_PRG) $(ALL_DEPS))
