# This really isn't as tested as the Makefile in conf/
# That's probably not idea.

all:
	-killall qemu-system-riscv64
	make $(MAKEFLAGS) -C sys
	make $(MAKEFLAGS) -C dev
	make $(MAKEFLAGS) -C conf
	# cd conf; make unix allsystems

.PHONY: clean
clean:
	make -C dev clean
	make -C conf clean
	make -C sys clean

-include */*.d */*/*.d
