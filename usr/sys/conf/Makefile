
include ../kernel.mk
include ../../../tools/common.mk
include ../../../tools/kernel.mk

# this technically overcompiles. At 1.6s cold kernel builds, I don't care.
unix: ../sys/LIB1.a ../dev/LIB2.a machine.o c.o shims.o Makefile mkconf kernel.ld
	$(MAKE)  $(MAKEFLAGS) -C ../sys
	$(MAKE)  $(MAKEFLAGS) -C ../dev
	# $(LD) -z max-page-size=4096 kernel.ld -o unix
	$(LD) $(LDFLAGS) -T kernel.ld -o unix \
	machine.o shims.o c.o \
	-Wl,--start-group ../sys/LIB1.a ../dev/LIB2.a  -Wl,--end-group
	$(OBJDUMP) -x --disassemble --source -g unix > unix.dis
	$(NM) -SsnCal unix > unix.sym
	$(OBJCOPY) unix  --output-format=binary  sd0unix.bin
	# cp unix /tmp/unix
	mv unix sd0unix

c.o: c.c mkconf.c sd0conf
c.c: mkconf
	./mkconf <sd0conf

#machine.o:	machine.S
#	$(CC) $(CFLAGS) -c -o machine.o machine.S
#shims.o:	shims.c
#	$(CC) $(CFLAGS) -c -o shims.o shims.c

Nallsystems: hd0unix hd1unix sd0unix

allsystems: mkconf
	#./mkconf <hd0conf
	#make unix
	##$(OBJDUMP) --disassemble unix > hdunix.sym
	#mv unix hd0unix
	#./mkconf <hd1conf
	#make unix
	##$(OBJDUMP) --disassemble unix > hd1unix.sym
	#mv unix hd1unix
	#./mkconf <sd0conf
	make unix
	$(OBJDUMP) --disassemble unix > unix.sym
	mv unix sd0unix

# This is built native on the host system. Escape any cross environment.
mkconf: mkconf.c
	cc -MD -DNCPU=2 -O -o mkconf mkconf.c

.PHONY:
clean:
	rm -f hd0unix hd1unix sd0unix
	rm -f unix mch.o c.o c.c mkconf
	rm -f ../sys/LIB1.a ../sys/*.o ../dev/LIB2.a ../dev/*.o *.o

rungdb: unix
	cp sd0unix /tmp/unix
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
