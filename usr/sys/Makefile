# This really isn't as tested as the Makefile in conf/
# That's probably not idea.
all:
	-killall qemu-system-riscv64
	make -C sys
	make -C dev
	make -C conf
	# cd conf; make unix allsystems

clean:
	make -C dev clean
	make -C conf clean
	make -C sys clean

-include */*.d */*/*.d
