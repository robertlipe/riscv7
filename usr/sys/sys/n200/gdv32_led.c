#include "gd32vf103.h"
#include "gd32v_pjt_include.h"
#include "gd32vf103_gpio.h"
#include "gd32vf103_rcu.h"
#include "gdv32_led.h"

// Mapping of symbolic internal names to GPIO pins
#define LED_GREEN GPIO_OCTL_OCTL1
#define LED_BLUE  GPIO_OCTL_OCTL2
#define LED_RED   GPIO_OCTL_OCTL13

#if defined(BOARD_gd32_dev)
// The Nano code should do something like this, too...
#define LED1_PIN                         GPIO_PIN_0
#define LED1_GPIO_PORT                   GPIOC
#define LED1_GPIO_CLK                    RCU_GPIOC

#define LED2_PIN                         GPIO_PIN_2
#define LED2_GPIO_PORT                   GPIOC
#define LED2_GPIO_CLK                    RCU_GPIOC

#define LED3_PIN                         GPIO_PIN_0
#define LED3_GPIO_PORT                   GPIOE
#define LED3_GPIO_CLK                    RCU_GPIOE

#define LED4_PIN                         GPIO_PIN_1
#define LED4_GPIO_PORT                   GPIOE
#define LED4_GPIO_CLK                    RCU_GPIOE

static uint32_t GPIO_PORT[] = {LED1_GPIO_PORT, LED2_GPIO_PORT,
                                   LED3_GPIO_PORT, LED4_GPIO_PORT};
static uint32_t GPIO_PIN[] = {LED1_PIN, LED2_PIN, LED3_PIN, LED4_PIN};
static rcu_periph_enum GPIO_CLK[] = {LED1_GPIO_CLK, LED2_GPIO_CLK,
                                         LED3_GPIO_CLK, LED4_GPIO_CLK};
#endif

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
#if defined(BOARD_gd32_dev)
#if 0
  ((GPIO*)GPIOC)->control_hi   &= ~( GPIO_CTL1_MD0 | GPIO_CTL1_CTL2 );
  ((GPIO*)GPIOC)->control_hi   |=  ( 0x1 << 20 );
  ((GPIO*)GPIOE)->control_hi   &= ~( GPIO_CTL1_MD0 | GPIO_CTL1_CTL1 );
  ((GPIO*)GPIOE)->control_hi   |=  ( 0x1 << 20 );
#endif
  rcu_periph_clock_enable(GPIO_CLK[0]);
  rcu_periph_clock_enable(GPIO_CLK[1]);
  rcu_periph_clock_enable(GPIO_CLK[2]);
  rcu_periph_clock_enable(GPIO_CLK[3]);

  gpio_init(GPIO_PORT[0], GPIO_MODE_OUT_PP, GPIO_OSPEED_50MHZ, GPIO_PIN[0]);
  gpio_init(GPIO_PORT[1], GPIO_MODE_OUT_PP, GPIO_OSPEED_50MHZ, GPIO_PIN[1]);
  gpio_init(GPIO_PORT[2], GPIO_MODE_OUT_PP, GPIO_OSPEED_50MHZ, GPIO_PIN[2]);
  gpio_init(GPIO_PORT[3], GPIO_MODE_OUT_PP, GPIO_OSPEED_50MHZ, GPIO_PIN[3]);

  GPIO_BC(GPIO_PORT[0]) = GPIO_PIN[0];
  GPIO_BC(GPIO_PORT[1]) = GPIO_PIN[1];
  GPIO_BC(GPIO_PORT[2]) = GPIO_PIN[2];
  GPIO_BC(GPIO_PORT[3]) = GPIO_PIN[3];

#endif

}

led_blue(int on)
{
	if (on) {
		((GPIO*) GPIOA)->bit_clear = LED_BLUE;
	} else {
		((GPIO*) GPIOA)->bit_op = LED_BLUE;
	}
}

led_green(int on)
{
	if (on) {
		((GPIO*) GPIOA)->bit_clear = LED_GREEN;
	} else {
		((GPIO*) GPIOA)->bit_op = LED_GREEN;
	}
}

led_red(int on)
{
	if (on) {
		((GPIO*) GPIOC)->bit_clear = LED_RED;
	} else {
		((GPIO*) GPIOC)->bit_op = LED_RED;
	}
}

void set_leds(int leds)
{
	if (leds & kLedGreen)
		((GPIO*) GPIOA)->bit_clear = LED_GREEN;
	if (leds & kLedBlue)
		((GPIO*) GPIOA)->bit_clear = LED_BLUE;
	if (leds & kLedRed)
		((GPIO*) GPIOC)->bit_clear = LED_RED;
}

void clear_leds(int leds)
{
	if (leds & kLedGreen)
		((GPIO*) GPIOA)->bit_op = LED_GREEN;
	if (leds & kLedBlue)
		((GPIO*) GPIOA)->bit_op = LED_BLUE;
	if (leds & kLedRed)
		((GPIO*) GPIOC)->bit_op = LED_RED;
}

// Just do something to visually indicate we're booting. Should be
// recognizable in peripheral vision.
led_boot() {
     const int snooze = 20000;
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
     const int snooze = 20000;
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
