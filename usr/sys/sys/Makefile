include ../kernel.mk
include ../../../tools/common.mk
include ../../../tools/kernel.mk

DEBUGGING=\
  n200/SEGGER_RTT.o

ALL_SRC_ := $(wildcard *.c)
DONT_COMPILE=elf.c xx.c
ALL_SRC = $(filter-out $(DONT_COMPILE),$(ALL_SRC_))
ALL_OBJ := $(patsubst %.c, %.o, $(ALL_SRC))    # list of .o files
ALL_DEPS := $(patsubst %.c, %.d, $(ALL_SRC))   # list of dependency files

OBJS=\
  $(ALL_OBJ) \
  $(DEBUGGING) \
  n200/n200_func.o \
  n200/gdv32_led.o \
  n200/delay1ms.o \
  n200/ff.o \
  n200/tf_card.o \
  n200/gd32vf103_gpio.o \
  n200/gd32vf103_spi.o \
  n200/gd32vf103_rcu.o \
  n200/gd32vf103_timer.o \
  n200/gd32vf103xb_boot.o

ifneq ($(BOARD_gd32_dev),undefined)
  OBJS += \
    n200/gd32vf103v_lcd_eval.o \
    n200/gd32vf103_exmc.o
else
  OBJS += \
    n200/gd32v_lcd.o
endif

CFLAGS += -In200/
CFLAGS += -DHXTAL_VALUE=108000000

# Slightly run since we put Makefile in the archive. The Linker knows to
# not include it in the object, but we should be less dumb here.
LIB1.a: Makefile \
	$(OBJS)
	$(AR) -rv -o LIB1.a $?

clean:
	rm -f LIB1.a $(OBJS)

-include *.d */*.d
