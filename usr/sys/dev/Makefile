include ../../../tools/common.mk
include ../../../tools/kernel.mk

OBJS=\
	bio.o \
	dsort.o \
	hd.o \
	cd.o \
	md.o \
	mem.o \
	mx1.o \
	mx2.o \
	partab.o \
	pk0.o \
	pk1.o \
	pk2.o \
	pk3.o \
	sc.o \
	serial.o \
	sys.o \
	tty.o 


LIB2.a:	$(OBJS)
	$(AR) -rv -o LIB2.a $?

# DROPPED	fd.o , cd.o, sr.o

-include *.d

clean:
	rm -f LIB1.a $(OBJS)
