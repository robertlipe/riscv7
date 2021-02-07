all: cmd libc/libc.a libdbm/libdbm.a libm/libm.a libmp/libmp.a games

cmd:
	$(MAKE) -C cmd

libc/libc.a:
	$(MAKE) -C libc

libm/libm.a:
	$(MAKE) -C libm

libdbm/libdbm.a:
	$(MAKE) -C libdbm

libmp/libmp.a:
	$(MAKE) -C libmp

# .PHONY games:
games:
	$(MAKE) -C games

clean:
	$(MAKE) -C libc clean
	$(MAKE) -C cmd clean
	$(MAKE) -C libm clean
	$(MAKE) -C libdbm clean
	$(MAKE) -C libmp clean
	$(MAKE) -C games clean

