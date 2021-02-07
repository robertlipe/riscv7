include ../../../tools/common.mk
include ../../../tools/user.mk

SOURCEDIR=.
BUILDDIR=.
SOURCES:=$(wildcard $(SOURCEDIR)/*.c)
OBJ:=$(patsubst $(SOURCEDIR)/%.c,$(BUILDDIR)/%.o,$(SOURCES))
#CFLAGS += -nostdinc -I ../../include
#CFLAGS += -nostdlib -DCRUTCH=1
# LDFLAGS += -L../libc -lc
#STARTUP=../libc/csu/crt0.o



CMDS=\
arithmetic \
backgammon \
fish \
fortune \
hangman \
quiz \
wump

# OBJECTS := $(C_SOURCES:.c=.o) $(S_SOURCES:.s=.o)

#%: %.o
#	$(LD) $(LDFLAGS) -o $@ $^  -L../libc -lc

all: $(OBJ) $(CMDS) 

clean:
	rm -f $(CMDS) $(OBJ) *.d

xtroff:
	cd troff ; $(MAKE)

-include *.d
