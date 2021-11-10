/*!
    \file    gd32vf103.h
    \brief   general definitions for GD32VF103

    \version 2019-06-05, V1.0.0, firmware for GD32VF103
*/

/*
    Copyright (c) 2019, GigaDevice Semiconductor Inc.

    Redistribution and use in source and binary forms, with or without modification, 
are permitted provided that the following conditions are met:

    1. Redistributions of source code must retain the above copyright notice, this 
       list of conditions and the following disclaimer.
    2. Redistributions in binary form must reproduce the above copyright notice, 
       this list of conditions and the following disclaimer in the documentation 
       and/or other materials provided with the distribution.
    3. Neither the name of the copyright holder nor the names of its contributors 
       may be used to endorse or promote products derived from this software without 
       specific prior written permission.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED 
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. 
IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, 
INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT 
NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR 
PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, 
WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY 
OF SUCH DAMAGE.
*/

#ifndef GD32VF103_H
#define GD32VF103_H

// A Kernel-only <stdinttZZ
typedef __INT32_TYPE__    int32_t;
typedef __INT64_TYPE__    int64_t;
typedef __UINT32_TYPE__   uint32_t;
typedef __UINT64_TYPE__   uint64_t;

#ifdef cplusplus
 extern "C" {
#endif 

 /* IO definitions (access restrictions to peripheral registers) */
 /**

     <strong>IO Type Qualifiers</strong> are used
     \li to specify the access to peripheral variables.
     \li for automatic generation of peripheral register debug information.
 */
 #ifdef __cplusplus
   #define   __I     volatile             /*!< Defines 'read only' permissions                 */
 #else
   #define   __I     volatile const       /*!< Defines 'read only' permissions                 */
 #endif
 #define     __O     volatile             /*!< Defines 'write only' permissions                */
 #define     __IO    volatile             /*!< Defines 'read / write' permissions              */

 /* define value of high speed crystal oscillator (HXTAL) in Hz */
 #if !defined  HXTAL_VALUE  
   #ifdef GD32VF103R_START #define HXTAL_VALUE    ((uint32_t)25000000) /*!< value of the external oscillator in Hz */ #define HXTAL_VALUE_8M  HXTAL_VALUE #elif defined(GD32VF103V_EVAL) || defined(GD32VF103C_START) || defined(GD32VF103T_START)
   #define HXTAL_VALUE    ((uint32_t)8000000) /*!< value of the external oscillator in Hz */
   #define HXTAL_VALUE_25M  HXTAL_VALUE
   #else
   #error "Please select the target board type used in your application (in gd32vf103.h file)"
   #endif
 #endif /* high speed crystal oscillator value */

/* define startup timeout value of high speed crystal oscillator (HXTAL) */
#if !defined  (HXTAL_STARTUP_TIMEOUT)
#define HXTAL_STARTUP_TIMEOUT   ((uint16_t)0xFFFF)
#endif /* high speed crystal oscillator startup timeout */

/* define value of internal 8MHz RC oscillator (IRC8M) in Hz */
#if !defined  (IRC8M_VALUE) 
#define IRC8M_VALUE  ((uint32_t)8000000)
#endif /* internal 8MHz RC oscillator value */

/* define startup timeout value of internal 8MHz RC oscillator (IRC8M) */
#if !defined  (IRC8M_STARTUP_TIMEOUT)
#define IRC8M_STARTUP_TIMEOUT   ((uint16_t)0x0500)
#endif /* internal 8MHz RC oscillator startup timeout */

/* define value of internal 40KHz RC oscillator(IRC40K) in Hz */
#if !defined  (IRC40K_VALUE) 
#define IRC40K_VALUE  ((uint32_t)40000)
#endif /* internal 40KHz RC oscillator value */

/* define value of low speed crystal oscillator (LXTAL)in Hz */
#if !defined  (LXTAL_VALUE) 
#define LXTAL_VALUE  ((uint32_t)32768)
#endif /* low speed crystal oscillator value */

/* define interrupt number */
typedef enum IRQn
{

	CLIC_INT_RESERVED        	 = 0,      			/*!< RISC-V reserved		*/
	CLIC_INT_SFT         		 = 3,				/*!< Software interrupt		*/
	CLIC_INT_TMR         		 = 7,				/*!< CPU Timer interrupt	*/
	CLIC_INT_BWEI        		 = 17,				/*!< Bus Error interrupt	*/
	CLIC_INT_PMOVI       		 = 18,				/*!< Performance Monitor	*/

    /* interruput numbers */
    WWDGT_IRQn                   = 19,      /*!< window watchDog timer interrupt                          */
    LVD_IRQn                     = 20,      /*!< LVD through EXTI line detect interrupt                   */
    TAMPER_IRQn                  = 21,      /*!< tamper through EXTI line detect                          */
    RTC_IRQn                     = 22,      /*!< RTC alarm interrupt                                      */
    FMC_IRQn                     = 23,      /*!< FMC interrupt                                            */
    RCU_CTC_IRQn                 = 24,      /*!< RCU and CTC interrupt                                    */
    EXTI0_IRQn                   = 25,      /*!< EXTI line 0 interrupts                                   */
    EXTI1_IRQn                   = 26,      /*!< EXTI line 1 interrupts                                   */
    EXTI2_IRQn                   = 27,      /*!< EXTI line 2 interrupts                                   */
    EXTI3_IRQn                   = 28,      /*!< EXTI line 3 interrupts                                   */
    EXTI4_IRQn                   = 29,     /*!< EXTI line 4 interrupts                                   */
    DMA0_Channel0_IRQn           = 30,     /*!< DMA0 channel0 interrupt                                  */
    DMA0_Channel1_IRQn           = 31,     /*!< DMA0 channel1 interrupt                                  */
    DMA0_Channel2_IRQn           = 32,     /*!< DMA0 channel2 interrupt                                  */
    DMA0_Channel3_IRQn           = 33,     /*!< DMA0 channel3 interrupt                                  */
    DMA0_Channel4_IRQn           = 34,     /*!< DMA0 channel4 interrupt                                  */
    DMA0_Channel5_IRQn           = 35,     /*!< DMA0 channel5 interrupt                                  */
    DMA0_Channel6_IRQn           = 36,     /*!< DMA0 channel6 interrupt                                  */
    ADC0_1_IRQn                  = 37,     /*!< ADC0 and ADC1 interrupt                                  */
    CAN0_TX_IRQn                 = 38,     /*!< CAN0 TX interrupts                                       */
    CAN0_RX0_IRQn                = 39,     /*!< CAN0 RX0 interrupts                                      */
    CAN0_RX1_IRQn                = 40,     /*!< CAN0 RX1 interrupts                                      */
    CAN0_EWMC_IRQn               = 41,     /*!< CAN0 EWMC interrupts                                     */
    EXTI5_9_IRQn                 = 42,     /*!< EXTI[9:5] interrupts                                     */
    TIMER0_BRK_IRQn              = 43,     /*!< TIMER0 break interrupts                                  */
    TIMER0_UP_IRQn               = 44,     /*!< TIMER0 update interrupts                                 */
    TIMER0_TRG_CMT_IRQn          = 45,     /*!< TIMER0 trigger and commutation interrupts                */
    TIMER0_Channel_IRQn          = 46,     /*!< TIMER0 channel capture compare interrupts                */
    TIMER1_IRQn                  = 47,     /*!< TIMER1 interrupt                                         */
    TIMER2_IRQn                  = 48,     /*!< TIMER2 interrupt                                         */
    TIMER3_IRQn                  = 49,     /*!< TIMER3 interrupts                                        */
    I2C0_EV_IRQn                 = 50,     /*!< I2C0 event interrupt                                     */
    I2C0_ER_IRQn                 = 51,     /*!< I2C0 error interrupt                                     */
    I2C1_EV_IRQn                 = 52,     /*!< I2C1 event interrupt                                     */
    I2C1_ER_IRQn                 = 53,     /*!< I2C1 error interrupt                                     */
    SPI0_IRQn                    = 54,     /*!< SPI0 interrupt                                           */
    SPI1_IRQn                    = 55,     /*!< SPI1 interrupt                                           */
    USART0_IRQn                  = 56,     /*!< USART0 interrupt                                         */
    USART1_IRQn                  = 57,     /*!< USART1 interrupt                                         */
    USART2_IRQn                  = 58,     /*!< USART2 interrupt                                         */
    EXTI10_15_IRQn               = 59,     /*!< EXTI[15:10] interrupts                                   */
    RTC_ALARM_IRQn               = 60,     /*!< RTC alarm interrupt EXTI                                 */
    USBFS_WKUP_IRQn              = 61,     /*!< USBFS wakeup interrupt                                   */

    EXMC_IRQn                    = 67,     /*!< EXMC global interrupt                                    */

    TIMER4_IRQn                  = 69,     /*!< TIMER4 global interrupt                                  */
    SPI2_IRQn                    = 70,     /*!< SPI2 global interrupt                                    */
    UART3_IRQn                   = 71,     /*!< UART3 global interrupt                                   */
    UART4_IRQn                   = 72,     /*!< UART4 global interrupt                                   */
    TIMER5_IRQn                  = 73,     /*!< TIMER5 global interrupt                                  */
    TIMER6_IRQn                  = 74,     /*!< TIMER6 global interrupt                                  */
    DMA1_Channel0_IRQn           = 75,     /*!< DMA1 channel0 global interrupt                           */
    DMA1_Channel1_IRQn           = 76,     /*!< DMA1 channel1 global interrupt                           */
    DMA1_Channel2_IRQn           = 77,     /*!< DMA1 channel2 global interrupt                           */
    DMA1_Channel3_IRQn           = 78,     /*!< DMA1 channel3 global interrupt                           */
    DMA1_Channel4_IRQn           = 79,     /*!< DMA1 channel3 global interrupt                           */

    CAN1_TX_IRQn                 = 82,     /*!< CAN1 TX interrupt                                        */
    CAN1_RX0_IRQn                = 83,     /*!< CAN1 RX0 interrupt                                       */
    CAN1_RX1_IRQn                = 84,     /*!< CAN1 RX1 interrupt                                       */
    CAN1_EWMC_IRQn               = 85,     /*!< CAN1 EWMC interrupt                                      */
    USBFS_IRQn                   = 86,     /*!< USBFS global interrupt                                   */

	ECLIC_NUM_INTERRUPTS
} IRQn_Type;

// local mods. Borrowed heavily from the gd32v SDK and 
// https://github.com/WRansohoff/GD32VF103_templates/blob/master/common/device_headers/gd32vf103.h
typedef struct
{
  volatile uint32_t control_lo;
  volatile uint32_t control_hi;
  volatile uint32_t input_status;
  volatile uint32_t output_control;
  volatile uint32_t bit_op;
  volatile uint32_t bit_clear;
  volatile uint32_t lock;
} GPIO;
typedef struct
{
  volatile uint32_t CRL;
  volatile uint32_t CRH;
  volatile uint32_t IDR;
  volatile uint32_t ODR;
  volatile uint32_t BSRR;
  volatile uint32_t BRR;
  volatile uint32_t LCKR;
} GPIO_TypeDef;


typedef struct
{
  volatile uint32_t CTL;
  volatile uint32_t CFG0;
  volatile uint32_t INT;
  volatile uint32_t APB2RST;
  volatile uint32_t APB1RST; // 0x10
  volatile uint32_t AHBEN;
  volatile uint32_t APB2EN;
  volatile uint32_t APB1EN;
  volatile uint32_t BDCTL; // 0x20
  volatile uint32_t RSTSCK;
  volatile uint32_t AHBRST;
  volatile uint32_t CFG1;
  // There's some padding in here...
//  volatile uint32_t DSV; // 0x34
} RCU_regs;

/* GPIO register bit definitions from Include/gd32vf103_gpio.h

/* GPIO_CTL0 */
#define GPIO_CTL0_MD0              BITS(0, 1)                /*!< port 0 mode bits */
#define GPIO_CTL0_CTL0             BITS(2, 3)                /*!< pin 0 configuration bits */
#define GPIO_CTL0_MD1              BITS(4, 5)                /*!< port 1 mode bits */
#define GPIO_CTL0_CTL1             BITS(6, 7)                /*!< pin 1 configuration bits */
#define GPIO_CTL0_MD2              BITS(8, 9)                /*!< port 2 mode bits */
#define GPIO_CTL0_CTL2             BITS(10, 11)              /*!< pin 2 configuration bits */
#define GPIO_CTL0_MD3              BITS(12, 13)              /*!< port 3 mode bits */
#define GPIO_CTL0_CTL3             BITS(14, 15)              /*!< pin 3 configuration bits */
#define GPIO_CTL0_MD4              BITS(16, 17)              /*!< port 4 mode bits */
#define GPIO_CTL0_CTL4             BITS(18, 19)              /*!< pin 4 configuration bits */
#define GPIO_CTL0_MD5              BITS(20, 21)              /*!< port 5 mode bits */
#define GPIO_CTL0_CTL5             BITS(22, 23)              /*!< pin 5 configuration bits */
#define GPIO_CTL0_MD6              BITS(24, 25)              /*!< port 6 mode bits */
#define GPIO_CTL0_CTL6             BITS(26, 27)              /*!< pin 6 configuration bits */
#define GPIO_CTL0_MD7              BITS(28, 29)              /*!< port 7 mode bits */
#define GPIO_CTL0_CTL7             BITS(30, 31)              /*!< pin 7 configuration bits */

/* GPIO_CTL1 */
#define GPIO_CTL1_MD8              BITS(0, 1)                /*!< port 8 mode bits */
#define GPIO_CTL1_CTL8             BITS(2, 3)                /*!< pin 8 configuration bits */
#define GPIO_CTL1_MD9              BITS(4, 5)                /*!< port 9 mode bits */
#define GPIO_CTL1_CTL9             BITS(6, 7)                /*!< pin 9 configuration bits */
#define GPIO_CTL1_MD10             BITS(8, 9)                /*!< port 10 mode bits */
#define GPIO_CTL1_CTL10            BITS(10, 11)              /*!< pin 10 configuration bits */
#define GPIO_CTL1_MD11             BITS(12, 13)              /*!< port 11 mode bits */
#define GPIO_CTL1_CTL11            BITS(14, 15)              /*!< pin 11 configuration bits */
#define GPIO_CTL1_MD12             BITS(16, 17)              /*!< port 12 mode bits */
#define GPIO_CTL1_CTL12            BITS(18, 19)              /*!< pin 12 configuration bits */
#define GPIO_CTL1_MD13             BITS(20, 21)              /*!< port 13 mode bits */
#define GPIO_CTL1_CTL13            BITS(22, 23)              /*!< pin 13 configuration bits */
#define GPIO_CTL1_MD14             BITS(24, 25)              /*!< port 14 mode bits */
#define GPIO_CTL1_CTL14            BITS(26, 27)              /*!< pin 14 configuration bits */
#define GPIO_CTL1_MD15             BITS(28, 29)              /*!< port 15 mode bits */
#define GPIO_CTL1_CTL15            BITS(30, 31)              /*!< pin 15 configuration bits */

/* GPIO_ISTAT */
#define GPIO_ISTAT_ISTAT0          BIT(0)                    /*!< pin 0 input status */
#define GPIO_ISTAT_ISTAT1          BIT(1)                    /*!< pin 1 input status */
#define GPIO_ISTAT_ISTAT2          BIT(2)                    /*!< pin 2 input status */
#define GPIO_ISTAT_ISTAT3          BIT(3)                    /*!< pin 3 input status */
#define GPIO_ISTAT_ISTAT4          BIT(4)                    /*!< pin 4 input status */
#define GPIO_ISTAT_ISTAT5          BIT(5)                    /*!< pin 5 input status */
#define GPIO_ISTAT_ISTAT6          BIT(6)                    /*!< pin 6 input status */
#define GPIO_ISTAT_ISTAT7          BIT(7)                    /*!< pin 7 input status */
#define GPIO_ISTAT_ISTAT8          BIT(8)                    /*!< pin 8 input status */
#define GPIO_ISTAT_ISTAT9          BIT(9)                    /*!< pin 9 input status */
#define GPIO_ISTAT_ISTAT10         BIT(10)                   /*!< pin 10 input status */
#define GPIO_ISTAT_ISTAT11         BIT(11)                   /*!< pin 11 input status */
#define GPIO_ISTAT_ISTAT12         BIT(12)                   /*!< pin 12 input status */
#define GPIO_ISTAT_ISTAT13         BIT(13)                   /*!< pin 13 input status */
#define GPIO_ISTAT_ISTAT14         BIT(14)                   /*!< pin 14 input status */
#define GPIO_ISTAT_ISTAT15         BIT(15)                   /*!< pin 15 input status */

/* GPIO_OCTL */
#define GPIO_OCTL_OCTL0            BIT(0)                    /*!< pin 0 output bit */
#define GPIO_OCTL_OCTL1            BIT(1)                    /*!< pin 1 output bit */
#define GPIO_OCTL_OCTL2            BIT(2)                    /*!< pin 2 output bit */
#define GPIO_OCTL_OCTL3            BIT(3)                    /*!< pin 3 output bit */
#define GPIO_OCTL_OCTL4            BIT(4)                    /*!< pin 4 output bit */
#define GPIO_OCTL_OCTL5            BIT(5)                    /*!< pin 5 output bit */
#define GPIO_OCTL_OCTL6            BIT(6)                    /*!< pin 6 output bit */
#define GPIO_OCTL_OCTL7            BIT(7)                    /*!< pin 7 output bit */
#define GPIO_OCTL_OCTL8            BIT(8)                    /*!< pin 8 output bit */
#define GPIO_OCTL_OCTL9            BIT(9)                    /*!< pin 9 output bit */
#define GPIO_OCTL_OCTL10           BIT(10)                   /*!< pin 10 output bit */
#define GPIO_OCTL_OCTL11           BIT(11)                   /*!< pin 11 output bit */
#define GPIO_OCTL_OCTL12           BIT(12)                   /*!< pin 12 output bit */
#define GPIO_OCTL_OCTL13           BIT(13)                   /*!< pin 13 output bit */
#define GPIO_OCTL_OCTL14           BIT(14)                   /*!< pin 14 output bit */
#define GPIO_OCTL_OCTL15           BIT(15)                   /*!< pin 15 output bit */

/* GPIO_BOP */
#define GPIO_BOP_BOP0              BIT(0)                    /*!< pin 0 set bit */
#define GPIO_BOP_BOP1              BIT(1)                    /*!< pin 1 set bit */
#define GPIO_BOP_BOP2              BIT(2)                    /*!< pin 2 set bit */
#define GPIO_BOP_BOP3              BIT(3)                    /*!< pin 3 set bit */
#define GPIO_BOP_BOP4              BIT(4)                    /*!< pin 4 set bit */
#define GPIO_BOP_BOP5              BIT(5)                    /*!< pin 5 set bit */
#define GPIO_BOP_BOP6              BIT(6)                    /*!< pin 6 set bit */
#define GPIO_BOP_BOP7              BIT(7)                    /*!< pin 7 set bit */
#define GPIO_BOP_BOP8              BIT(8)                    /*!< pin 8 set bit */
#define GPIO_BOP_BOP9              BIT(9)                    /*!< pin 9 set bit */
#define GPIO_BOP_BOP10             BIT(10)                   /*!< pin 10 set bit */
#define GPIO_BOP_BOP11             BIT(11)                   /*!< pin 11 set bit */
#define GPIO_BOP_BOP12             BIT(12)                   /*!< pin 12 set bit */
#define GPIO_BOP_BOP13             BIT(13)                   /*!< pin 13 set bit */
#define GPIO_BOP_BOP14             BIT(14)                   /*!< pin 14 set bit */
#define GPIO_BOP_BOP15             BIT(15)                   /*!< pin 15 set bit */
#define GPIO_BOP_CR0               BIT(16)                   /*!< pin 0 clear bit */
#define GPIO_BOP_CR1               BIT(17)                   /*!< pin 1 clear bit */
#define GPIO_BOP_CR2               BIT(18)                   /*!< pin 2 clear bit */
#define GPIO_BOP_CR3               BIT(19)                   /*!< pin 3 clear bit */
#define GPIO_BOP_CR4               BIT(20)                   /*!< pin 4 clear bit */
#define GPIO_BOP_CR5               BIT(21)                   /*!< pin 5 clear bit */
#define GPIO_BOP_CR6               BIT(22)                   /*!< pin 6 clear bit */
#define GPIO_BOP_CR7               BIT(23)                   /*!< pin 7 clear bit */
#define GPIO_BOP_CR8               BIT(24)                   /*!< pin 8 clear bit */
#define GPIO_BOP_CR9               BIT(25)                   /*!< pin 9 clear bit */
#define GPIO_BOP_CR10              BIT(26)                   /*!< pin 10 clear bit */
#define GPIO_BOP_CR11              BIT(27)                   /*!< pin 11 clear bit */
#define GPIO_BOP_CR12              BIT(28)                   /*!< pin 12 clear bit */
#define GPIO_BOP_CR13              BIT(29)                   /*!< pin 13 clear bit */
#define GPIO_BOP_CR14              BIT(30)                   /*!< pin 14 clear bit */
#define GPIO_BOP_CR15              BIT(31)                   /*!< pin 15 clear bit */

/* GPIO_BC */
#define GPIO_BC_CR0                BIT(0)                    /*!< pin 0 clear bit */
#define GPIO_BC_CR1                BIT(1)                    /*!< pin 1 clear bit */
#define GPIO_BC_CR2                BIT(2)                    /*!< pin 2 clear bit */
#define GPIO_BC_CR3                BIT(3)                    /*!< pin 3 clear bit */
#define GPIO_BC_CR4                BIT(4)                    /*!< pin 4 clear bit */
#define GPIO_BC_CR5                BIT(5)                    /*!< pin 5 clear bit */
#define GPIO_BC_CR6                BIT(6)                    /*!< pin 6 clear bit */
#define GPIO_BC_CR7                BIT(7)                    /*!< pin 7 clear bit */
#define GPIO_BC_CR8                BIT(8)                    /*!< pin 8 clear bit */
#define GPIO_BC_CR9                BIT(9)                    /*!< pin 9 clear bit */
#define GPIO_BC_CR10               BIT(10)                   /*!< pin 10 clear bit */
#define GPIO_BC_CR11               BIT(11)                   /*!< pin 11 clear bit */
#define GPIO_BC_CR12               BIT(12)                   /*!< pin 12 clear bit */
#define GPIO_BC_CR13               BIT(13)                   /*!< pin 13 clear bit */
#define GPIO_BC_CR14               BIT(14)                   /*!< pin 14 clear bit */
#define GPIO_BC_CR15               BIT(15)                   /*!< pin 15 clear bit */

/* GPIO_LOCK */
#define GPIO_LOCK_LK0              BIT(0)                    /*!< pin 0 lock bit */
#define GPIO_LOCK_LK1              BIT(1)                    /*!< pin 1 lock bit */
#define GPIO_LOCK_LK2              BIT(2)                    /*!< pin 2 lock bit */
#define GPIO_LOCK_LK3              BIT(3)                    /*!< pin 3 lock bit */
#define GPIO_LOCK_LK4              BIT(4)                    /*!< pin 4 lock bit */
#define GPIO_LOCK_LK5              BIT(5)                    /*!< pin 5 lock bit */
#define GPIO_LOCK_LK6              BIT(6)                    /*!< pin 6 lock bit */
#define GPIO_LOCK_LK7              BIT(7)                    /*!< pin 7 lock bit */
#define GPIO_LOCK_LK8              BIT(8)                    /*!< pin 8 lock bit */
#define GPIO_LOCK_LK9              BIT(9)                    /*!< pin 9 lock bit */
#define GPIO_LOCK_LK10             BIT(10)                   /*!< pin 10 lock bit */
#define GPIO_LOCK_LK11             BIT(11)                   /*!< pin 11 lock bit */
#define GPIO_LOCK_LK12             BIT(12)                   /*!< pin 12 lock bit */
#define GPIO_LOCK_LK13             BIT(13)                   /*!< pin 13 lock bit */
#define GPIO_LOCK_LK14             BIT(14)                   /*!< pin 14 lock bit */
#define GPIO_LOCK_LK15             BIT(15)                   /*!< pin 15 lock bit */
#define GPIO_LOCK_LKK              BIT(16)                   /*!< pin sequence lock key */

// From Include/gd32vf103_rcu.h
/* RCU_APB2RST */
#define RCU_APB2RST_AFRST               BIT(0)                    /*!< alternate function I/O reset */
#define RCU_APB2RST_PARST               BIT(2)                    /*!< GPIO port A reset */
#define RCU_APB2RST_PBRST               BIT(3)                    /*!< GPIO port B reset */
#define RCU_APB2RST_PCRST               BIT(4)                    /*!< GPIO port C reset */
#define RCU_APB2RST_PDRST               BIT(5)                    /*!< GPIO port D reset */
#define RCU_APB2RST_PERST               BIT(6)                    /*!< GPIO port E reset */
#define RCU_APB2RST_ADC0RST             BIT(9)                    /*!< ADC0 reset */
#define RCU_APB2RST_ADC1RST             BIT(10)                   /*!< ADC1 reset */
#define RCU_APB2RST_TIMER0RST           BIT(11)                   /*!< TIMER0 reset */
#define RCU_APB2RST_SPI0RST             BIT(12)                   /*!< SPI0 reset */
#define RCU_APB2RST_USART0RST           BIT(14)                   /*!< USART0 reset */

// end local mods

/* includes */
#include "system_gd32vf103.h"
#include <stdint.h>

/* enum definitions */
typedef enum {DISABLE = 0, ENABLE = !DISABLE} EventStatus, ControlStatus;
// typedef enum {FALSE = 0, TRUE = !FALSE} bool;
typedef enum {RESET = 0, SET = 1,MAX = 0X7FFFFFFF} FlagStatus;
typedef enum {ERROR = 0, SUCCESS = !ERROR} ErrStatus;

/* bit operations */
#define REG32(addr)                  (*(volatile uint32_t *)(uint32_t)(addr))
#define REG16(addr)                  (*(volatile uint16_t *)(uint32_t)(addr))
#define REG8(addr)                   (*(volatile uint8_t *)(uint32_t)(addr))
#define BIT(x)                       ((uint32_t)((uint32_t)0x01U<<(x)))
#define BITS(start, end)             ((0xFFFFFFFFUL << (start)) & (0xFFFFFFFFUL >> (31U - (uint32_t)(end)))) 
#define GET_BITS(regval, start, end) (((regval) & BITS((start),(end))) >> (start))

/* main flash and SRAM memory map */
#define FLASH_BASE            ((uint32_t)0x08000000U)        /*!< main FLASH base address          */
#define SRAM_BASE             ((uint32_t)0x20000000U)        /*!< SRAM0 base address               */
#define OB_BASE               ((uint32_t)0x1FFFF800U)        /*!< OB base address                  */
#define DBG_BASE              ((uint32_t)0xE0042000U)        /*!< DBG base address                 */
#define EXMC_BASE             ((uint32_t)0xA0000000U)        /*!< EXMC register base address       */

/* peripheral memory map */
#define APB1_BUS_BASE         ((uint32_t)0x40000000U)        /*!< apb1 base address                */
#define APB2_BUS_BASE         ((uint32_t)0x40010000U)        /*!< apb2 base address                */
#define AHB1_BUS_BASE         ((uint32_t)0x40018000U)        /*!< ahb1 base address                */
#define AHB3_BUS_BASE         ((uint32_t)0x60000000U)        /*!< ahb3 base address                */

/* advanced peripheral bus 1 memory map */
#define TIMER_BASE            (APB1_BUS_BASE + 0x00000000U)  /*!< TIMER base address               */
#define RTC_BASE              (APB1_BUS_BASE + 0x00002800U)  /*!< RTC base address                 */
#define WWDGT_BASE            (APB1_BUS_BASE + 0x00002C00U)  /*!< WWDGT base address               */
#define FWDGT_BASE            (APB1_BUS_BASE + 0x00003000U)  /*!< FWDGT base address               */
#define SPI_BASE              (APB1_BUS_BASE + 0x00003800U)  /*!< SPI base address                 */
#define USART_BASE            (APB1_BUS_BASE + 0x00004400U)  /*!< USART base address               */
#define I2C_BASE              (APB1_BUS_BASE + 0x00005400U)  /*!< I2C base address                 */
#define CAN_BASE              (APB1_BUS_BASE + 0x00006400U)  /*!< CAN base address                 */
#define BKP_BASE              (APB1_BUS_BASE + 0x00006C00U)  /*!< BKP base address                 */
#define PMU_BASE              (APB1_BUS_BASE + 0x00007000U)  /*!< PMU base address                 */
#define DAC_BASE              (APB1_BUS_BASE + 0x00007400U)  /*!< DAC base address                 */

/* advanced peripheral bus 2 memory map */
#define AFIO_BASE             (APB2_BUS_BASE + 0x00000000U)  /*!< AFIO base address                */
#define EXTI_BASE             (APB2_BUS_BASE + 0x00000400U)  /*!< EXTI base address                */
#define GPIO_BASE             (APB2_BUS_BASE + 0x00000800U)  /*!< GPIO base address                */
#define RCU           ( ( RCU_regs * )         0x40021000 )
//#define GPIOA         ( ( GPIO * )        ((char*)APB2_BUS_BASE + 0x0800))
#if REVERT
#define GPIOA         ( ( GPIO * )        0x40010800U)
#define GPIOB         ( ( GPIO * )        0x40010C00U)
#define GPIOC         ( ( GPIO * )        0x40011000U)
#define GPIOD         ( ( GPIO * )        0x40011400U)
#define GPIOE         ( ( GPIO * )        0x40011800U)
//#define GPIOB         ( ( GPIO * )        ((char*)APB2_BUS_BASE + 0x0c00))
//#define GPIOC         ( ( GPIO * )        ((char*)APB2_BUS_BASE + 0x1000))
//#define GPIOD         ( ( GPIO * )        ((char*)APB2_BUS_BASE + 0x1400)) 
//#define GPIOE         ( ( GPIO * )        ((char*)APB2_BUS_BASE + 0x1800))
//#define ADC_BASE              (APB2_BUS_BASE + 0x00002400U)  /*!< ADC base address                 */
#endif

/* advanced high performance bus 1 memory map */
#define DMA_BASE              (AHB1_BUS_BASE + 0x00008000U)  /*!< DMA base address                 */
#define RCU_BASE              (AHB1_BUS_BASE + 0x00009000U)  /*!< RCU base address                 */
#define FMC_BASE              (AHB1_BUS_BASE + 0x0000A000U)  /*!< FMC base address                 */
#define CRC_BASE              (AHB1_BUS_BASE + 0x0000B000U)  /*!< CRC base address                 */
#define USBFS_BASE            (AHB1_BUS_BASE + 0x0FFE8000U)  /*!< USBFS base address               */

/* define marco USE_STDPERIPH_DRIVER */
#if !defined  USE_STDPERIPH_DRIVER
#define USE_STDPERIPH_DRIVER
#endif 
#ifdef USE_STDPERIPH_DRIVER
//#include "gd32vf103_libopt.h"
#endif /* USE_STDPERIPH_DRIVER */

#ifdef cplusplus
}
#endif
#endif 
