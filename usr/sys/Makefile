# This really isn't as tested as the Makefile in conf/
# That's probably not idea.

# "Supported" boards. Honestly, probably only one works at a time.
# make BOARD=nano
# make BOARD=esp32c3 (never tested. theoretical stepping stone of 32b w/ SiFive)
# * make BOARD=visionfive (64-bit. Eventually 2 CPU.)


all:
	-killall qemu-system-riscv64
	+make $(MAKEFLAGS) -C sys
	+make $(MAKEFLAGS) -C dev
	+make $(MAKEFLAGS) -C conf
	# cd conf; make unix allsystems

.PHONY: clean
clean:
	make -C dev clean
	make -C conf clean
	make -C sys clean

-include */*.d */*/*.d
