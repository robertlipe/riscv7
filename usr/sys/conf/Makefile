include ../../../tools/common.mk
include ../../../tools/kernel.mk

#all: mkconf
#	#cd ../sys; cc -c -O *.c; ./mklib; # rm *.o
#	cd ../sys ; make
#	#cd ../dev; cc -c -O *.c; ./mklib; # rm *.o
#	cd ../dev ; make
#vpath=../dev:../sys

unix:	../sys/LIB1.a ../dev/LIB2.a machine.o c.o shims.o Makefile mkconf kernel.ld
	#cd ../sys; cc -c -O *.c; ./mklib; # rm *.o
	# cd ../sys ; make $(MAKEFLAGS)
	$(MAKE)  $(MAKEFLAGS) -C ../sys 
	#cd ../dev; cc -c -O *.c; ./mklib; # rm *.o
	# cd ../dev ; make $(MAKEFLAGS)
	$(MAKE)  $(MAKEFLAGS) -C ../dev 
	# $(LD) -z max-page-size=4096 kernel.ld -o unix
	$(LD) $(LDFLAGS) -T kernel.ld -o unix \
	machine.o shims.o c.o \
	-Wl,--start-group ../sys/LIB1.a ../dev/LIB2.a  -Wl,--end-group
	$(OBJDUMP) -x --disassemble --source -g unix > unix.dis
	$(NM) -SsnCal unix > unix.sym
	$(OBJCOPY) unix  --output-format=binary  md0unix.bin
	cp unix /tmp/unix
	mv unix md0unix

c.o: c.c mkconf.c
c.c: mkconf
	./mkconf <md0conf

machine.o:	machine.S
	$(CC) $(CFLAGS) -c -o machine.o machine.S
shims.o:	shims.c
	$(CC) $(CFLAGS) -c -o shims.o shims.c

Nallsystems: hd0unix hd1unix md0unix

allsystems: mkconf
	#./mkconf <hd0conf
	#make unix
	##$(OBJDUMP) --disassemble unix > hdunix.sym
	#mv unix hd0unix
	#./mkconf <hd1conf
	#make unix
	##$(OBJDUMP) --disassemble unix > hd1unix.sym
	#mv unix hd1unix
	#./mkconf <md0conf
	make unix
	$(OBJDUMP) --disassemble unix > unix.sym
	mv unix md0unix

# This is built native on the host system. Escape any cross environment.
mkconf: mkconf.c
	cc -MD -DNCPU=2 -O -o mkconf mkconf.c

clean:
	rm -f hd0unix hd1unix md0unix
	rm -f unix mch.o c.o c.c mkconf
	rm -f ../sys/LIB1 ../sys/*.o ../dev/LIB2 ../dev/*.o *.o

rungdb: unix
	cp md0unix /tmp/unix
	touch /tmp/fs.img
	# Was: -kernel /tmp/unix -m 3G -smp 3 -nographic \
	echo "In another terminal, run gdb."
	echo "To regain control here, <ctrl>A, then <c> to quit."
	qemu-system-riscv32 -machine virt -bios none \
	-kernel /tmp/unix -m 3G -nographic \
	-drive file=/tmp/fs.img,if=none,format=raw,id=x0 \
	-device virtio-blk-device,drive=x0,bus=virtio-mmio-bus.0 \
	-S -gdb tcp::25502


-include *.d
