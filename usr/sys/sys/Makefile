
include ../../../tools/common.mk
include ../../../tools/kernel.mk



OBJS=\
acct.o alloc.o clock.o fakemx.o fio.o iget.o machdep.o main.o \
malloc.o nami.o pipe.o prf.o prim.o rdwri.o sig.o slp.o subr.o \
sys1.o sys2.o sys3.o sys4.o sysent.o text.o trap.o utab.o  \
  n200/n200_func.o \
  n200/gdv32_led.o \
  n200/gd32v_lcd.o \
  n200/delay1ms.o \
  n200/ff.o \
  n200/tf_card.o \
  n200/gd32vf103_gpio.o \
  n200/gd32vf103_spi.o \
  n200/gd32vf103_rcu.o \
  n200/gd32vf103_timer.o \
  n200/gd32vf103xb_boot.o
CFLAGS += -In200/
CFLAGS += -DHXTAL_VALUE=108000000

LIB1.a: Makefile \
	$(OBJS)
	$(AR) -rv -o LIB1.a $?


clean:
	rm -f LIB1.a $(OBJS)

-include *.d */*.d
