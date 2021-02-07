all: cmds libc/libc.a libdbm/libdbm.a libm/libm.a libmp/libmp.a games
.PHONY all:

cmds: libc/libc.a
	$(MAKE) -C cmd
.PHONY: cmds

libc/libc.a:
	$(MAKE) -C libc

libm/libm.a:
	$(MAKE) -C libm

libdbm/libdbm.a:
	$(MAKE) -C libdbm

libmp/libmp.a:
	$(MAKE) -C libmp

.PHONY: games
games: libc/libc.a
	$(MAKE) -C games

clean:
	$(MAKE) -C libc clean
	$(MAKE) -C cmd clean
	$(MAKE) -C libm clean
	$(MAKE) -C libdbm clean
	$(MAKE) -C libmp clean
	$(MAKE) -C games clean

