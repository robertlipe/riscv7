#include "gd32vf103.h"
#include "gd32v_pjt_include.h"
#include "gd32vf103_gpio.h"
#include "gd32vf103_rcu.h"

#define LED_GREEN GPIO_OCTL_OCTL1
#define LED_BLUE  GPIO_OCTL_OCTL2
#define LED_RED   GPIO_OCTL_OCTL13

__attribute__( ( optimize( "O0" ) ) )
void delay_cycles( uint32_t cyc ) {
  uint32_t d_i;
  for ( d_i = 0; d_i < cyc*10; ++d_i ) { __asm__( "nop" );
  }
}

Xled_init() {
    rcu_periph_clock_enable(RCU_GPIOA);
    rcu_periph_clock_enable(RCU_GPIOC);
    gpio_init(GPIOC, GPIO_MODE_OUT_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_13);
    gpio_init(GPIOA, GPIO_MODE_OUT_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_1|GPIO_PIN_2);
}
#if THIS_SHOULD_WORK
led_red(int on) {
	PC_OUT(13, !!on);
}
led_green(int on) {
	PC_OUT(1, !!on);
}
led_blue(int on) {
	PC_OUT(2, !!on);
}

#else

// This is probably not fully correct. The LEDs seems to work only the 
// second time after the device is hard booted.  Might be bad timer.
// Maybe this code isn't even to blame. {/shrug} RJL 2020-10-12
led_init()
{
  // Turn on GPIOA and GPIOC.
  RCU->APB2EN |=  ( RCU_APB2RST_PARST |
                    RCU_APB2RST_PCRST );
#if 1 // ALMOST_THERE
  ( ( GPIO_TypeDef * ) 0x40010800 )->CRL &= ~( ( ( 0x3UL << ( 4U ) ) ) | ( ( 0x3UL << ( 6U ) ) ) |
                     ( ( 0x3UL << ( 8U ) ) ) | ( ( 0x3UL << ( 10U ) ) ) );
  ( ( GPIO_TypeDef * ) 0x40010800 )->CRL |= ( ( 0x2 << ( 4U ) ) |
                     ( 0x2 << ( 8U ) ) );
  ((GPIO*)GPIOC)->control_hi   &= ~( GPIO_CTL1_MD13 | GPIO_CTL1_CTL13 );
  ((GPIO*)GPIOC)->control_hi   |=  ( 0x1 << 20 );
  led_boot();
#else
  GPIOA->control_lo   &= ~( GPIO_CRL_MODE1 | GPIO_CRL_CNF1 |
                     GPIO_CRL_MODE2 | GPIO_CRL_CNF2 );
  GPIOA->control_lo   |=  ( ( 0x2 << GPIO_CRL_MODE1_Pos ) |
                     ( 0x2 << GPIO_CRL_MODE2_Pos ) );
  GPIOC->control_hi   &= ~( GPIO_CRH_MODE13 | GPIO_CRH_CNF13 );
  GPIOC->control_hi   |=  ( 0x2 << GPIO_CRH_MODE13_Pos );
#endif

#if 0
  ( ( GPIO_TypeDef * ) 0x40011000 )->CRH &= ~( ( ( 0x3UL << ( 20U ) ) ) | ( ( 0x3UL << ( 22U ) ) ) );
  ( ( GPIO_TypeDef * ) 0x40011000 )->CRH |= ( 0x2 << ( 20U ) );




  ( ( GPIO_TypeDef * ) 0x40010800 )->ODR |= ( 0x1 << 1 |
                     0x1 << 2 );
  ( ( GPIO_TypeDef * ) 0x40011000 )->ODR |= ( 0x1 << 13 );

  led_boot();
  return;



   ( ( GPIO_TypeDef * ) 0x40010800 )->ODR &= ~( 0x1 << 1 );
    delay_cycles( ( 500000 ) );
	led_green(0);
    delay_cycles( ( 500000 ) );
	led_green(1);


return ;
    delay_cycles( ( 500000 ) );

    ( ( GPIO_TypeDef * ) 0x40011000 )->ODR &= ~( 0x1 << 13 );
    delay_cycles( ( 500000 ) );

    ( ( GPIO_TypeDef * ) 0x40010800 )->ODR &= ~( 0x1 << 2 );
    delay_cycles( ( 500000 ) );

    ( ( GPIO_TypeDef * ) 0x40010800 )->ODR |= ( 0x1 << 1 );
    delay_cycles( ( 500000 ) );

    ( ( GPIO_TypeDef * ) 0x40011000 )->ODR |= ( 0x1 << 13 );
    delay_cycles( ( 500000 ) );

    ( ( GPIO_TypeDef * ) 0x40010800 )->ODR |= ( 0x1 << 2 );
    delay_cycles( ( 500000 ) );
#endif
}


led_blue(int on)
{
#if 0
	if (on) {
		    ((GPIO*) GPIOA)->output_control &= ~( LED_BLUE );
	} else {
		    ((GPIO*) GPIOA)->output_control |= ( LED_BLUE );
	}
#else
	if (on) {
		((GPIO*) GPIOA)->bit_clear = LED_BLUE;
	} else {
		((GPIO*) GPIOA)->bit_op = LED_BLUE;
	}
#endif
}
led_green(int on)
{
#if 0
	if (on) {
		    ((GPIO*)GPIOA)->output_control &= ~( LED_GREEN );
	} else {
		    ((GPIO*)GPIOA)->output_control |= ( LED_GREEN );
	}
#else
	volatile uint32_t* reg = &((GPIO*) GPIOA)->bit_op;
	reg += !!on;
	*(uint32_t*)reg = LED_GREEN;
#endif
}
led_red(int on)
{
	if (on) {
		    ((GPIO*)GPIOC)->output_control &= ~( LED_RED );
	} else {
		    ((GPIO*)GPIOC)->output_control |= ( LED_RED );
	}
}
#endif

// Just do something to visually indicate we're booting. Should be
// recognizable in peripheral vision.
led_boot() {
     const int snooze = 200000;
     for (int i = 0; i < 2; i++) {
    	led_red(1);
    	led_green(0);
    	led_blue(0);
    delay_cycles(snooze);
    	led_red(0);
    	led_green(1);
    delay_cycles(snooze);
    	led_green(0);
    	led_blue(1);
    delay_cycles(snooze);
    	led_blue(0);
    }
}

led_alarm() {
     const int snooze = 200000;
    	led_red(0);
    	led_green(0);
    	led_blue(0);
     for (int i = 1; i < 20; i++) {
    	led_red(0);
        delay_cycles(snooze/i);
    	led_red(1);
        delay_cycles(snooze/i);
     }
}
