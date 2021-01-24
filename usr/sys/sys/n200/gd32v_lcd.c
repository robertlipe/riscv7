// largely from
// https://raw.githubusercontent.com/sipeed/Longan_GD32VF_examples/master/gd32v_lcd/src/lcd/lcd.c
// Correction. That's where this code probably SHOULD have come from. This
// is closer to Longnan's own from
// https://github.com/sipeed/Longan_GD32VF_examples/blob/master/gd32v_lcd/src/lcd/lcd.c
// Or
// https://github.com/Xinyuan-LilyGO/LilyGO-T-DisplayGD32/blob/master/src/lcd/lcd.c

#include "gd32v_lcd.h"

#include "gd32vf103.h"
#include "oledfont.h"

#define ST7789_SLPOUT 0x11
#define ST7789_NORON 0x13

#define ST7789_INVON 0x21
#define ST7789_CASET 0x2A
#define ST7789_RASET 0x2B
#define ST7789_RAMWR 0x2C
#define ST7789_DISPOFF 0x28
#define ST7789_DISPON 0x29
#define TFT_MAD_COLOR_ORDER TFT_MAD_RGB
#define TFT_MAD_MY 0x80
#define TFT_MAD_MX 0x40
#define TFT_MAD_MV 0x20
#define TFT_MAD_ML 0x10

#define ST7789_MADCTL 0x36  // Memory data access control
#define TFT_MAD_RGB 0x08
#define ST7789_COLMOD 0x3A

#define ST7789_PORCTRL 0xB2    // Porch control
#define ST7789_GCTRL 0xB7      // Gate control
#define ST7789_VCOMS 0xBB      // VCOMS setting
#define ST7789_LCMCTRL 0xC0    // LCM control
#define ST7789_VDVVRHEN 0xC2   // VDV and VRH command enable
#define ST7789_VRHS 0xC3       // VRH set
#define ST7789_VDVSET 0xC4     // VDV setting
#define ST7789_FRCTR2 0xC6     // FR Control 2
#define ST7789_PWCTRL1 0xD0    // Power control 1
#define ST7789_PVGAMCTRL 0xE0  // Positive voltage gamma control
#define ST7789_NVGAMCTRL 0xE1  // Negative voltage gamma control

#define BMP 0
#if BMP
#include "n200/bmp.h"
#endif

u16 BACK_COLOR;        // Background color
int lcd_disabled = 0;  // Device has failed. Quit trying.
int cursor_x;
int cursor_y;
// Arbitrary max tries before declaring LCD dead.
// In practice, I've not seen it be > 1.
#define MAX_TRIES 1000

u16 colstart = 52;
u16 rowstart = 40;
u16 init_height_ = 240;
u16 init_width_ = 135;
u16 width_ = 135;
u16 height_ = 240;
u8 rotation_ = 0;

/******************************************************************************
       Function description: LCD serial data write function
       Entry data: serial data to be written to dat
       Return value: None
******************************************************************************/
static void LCD_WriteBus_(u8 dat) {
#if SPI0_CFG == 1
  OLED_CS_Clr();
  int timeout_ct = 0;
  if (lcd_disabled) return;

  while (RESET == spi_i2s_flag_get(SPI0, SPI_FLAG_TBE)) {
    if (timeout_ct++ >= MAX_TRIES) {
      led_alarm();
      lcd_disabled = 1;
      printf("SPIO failed. on transmit. Disabling.");
      return;
    }
  }
  spi_i2s_data_transmit(SPI0, dat);
  while (RESET == spi_i2s_flag_get(SPI0, SPI_FLAG_RBNE)) {
    if (timeout_ct++ >= MAX_TRIES) {
      led_alarm();
      lcd_disabled = 1;
      printf("SPIO failed. on receive. Disabling.");
      return;
    }
  }
  spi_i2s_data_receive(SPI0);

  OLED_CS_Set();
#elif SPI0_CFG == 2
  spi_dma_enable(SPI0, SPI_DMA_TRANSMIT);
#else
  u8 i;
  OLED_CS_Clr();
  for (i = 0; i < 8; i++) {
    OLED_SCLK_Clr();
    if (dat & 0x80)
      OLED_SDIN_Set();
    else
      OLED_SDIN_Clr();
    OLED_SCLK_Set();
    dat <<= 1;
  }
  OLED_CS_Set();
#endif
}

/******************************************************************************
       Function description: LCD write data
       Entry data: data written by dat
       Return value: None
******************************************************************************/
void LCD_WriteData8_(u8 dat) {
  OLED_DC_Set();  // Write data
  LCD_WriteBus_(dat);
}

/******************************************************************************
           Function description: LCD write data
       Entry data: data written by dat
       Return value: None
******************************************************************************/
void LCD_WriteData16_(u16 dat) {
  OLED_DC_Set();  // Write data
  LCD_WriteBus_(dat >> 8);
  LCD_WriteBus_(dat);
}

/******************************************************************************
           Function description: LCD write command
       Entry data: command written by dat
       Return value: None
******************************************************************************/
void LCD_WriteReg_(u8 dat) {
  OLED_DC_Clr();  // Write command
  LCD_WriteBus_(dat);
}

/******************************************************************************
           Function description: Set start and end addresses
       Entry data: x1, x2 set the start and end addresses of the column
                   y1, y2 set the start and end addresses of the line
       Return value: None
******************************************************************************/
void LCD_SetAddress_(u16 x1, u16 y1, u16 x2, u16 y2) {
  if (USE_HORIZONTAL == 0) {
    LCD_WriteReg_(ST7789_CASET);  // Column address settings
    LCD_WriteData16_(x1 + 26);
    LCD_WriteData16_(x2 + 26);
    LCD_WriteReg_(ST7789_RASET);  // Row address setting
    LCD_WriteData16_(y1 + 1);
    LCD_WriteData16_(y2 + 1);
    LCD_WriteReg_(ST7789_RAMWR);  // Memory write
  } else if (USE_HORIZONTAL == 1) {
    LCD_WriteReg_(ST7789_CASET);  // Column address settings
    LCD_WriteData16_(x1 + 26);
    LCD_WriteData16_(x2 + 26);
    LCD_WriteReg_(ST7789_RASET);  // Row address setting
    LCD_WriteData16_(y1 + 1);
    LCD_WriteData16_(y2 + 1);
    LCD_WriteReg_(ST7789_RAMWR);  // Memory write
  } else if (USE_HORIZONTAL == 2) {
    LCD_WriteReg_(ST7789_CASET);  // Column address settings
    LCD_WriteData16_(x1 + 1);
    LCD_WriteData16_(x2 + 1);
    LCD_WriteReg_(ST7789_RASET);  // Row address setting
    LCD_WriteData16_(y1 + 26);
    LCD_WriteData16_(y2 + 26);
    LCD_WriteReg_(ST7789_RAMWR);  // Memory write
  } else {
    LCD_WriteReg_(ST7789_CASET);  // Column address settings
    LCD_WriteData16_(x1 + 1);
    LCD_WriteData16_(x2 + 1);
    LCD_WriteReg_(ST7789_RASET);  // Row address setting
    LCD_WriteData16_(y1 + 26);
    LCD_WriteData16_(y2 + 26);
    LCD_WriteReg_(ST7789_RAMWR);  // Memory write
  }
}

#if SPI0_CFG == 2
/*!
    \brief      configure the DMA peripheral
    \param[in]  none
    \param[out] none
    \retval     none
*/
void dma_config(void) {
  dma_parameter_struct dma_init_struct;

  /* SPI0 transmit dma config:DMA0,DMA_CH2 */
  dma_deinit(DMA0, DMA_CH2);
  dma_struct_para_init(&dma_init_struct);

  dma_init_struct.periph_addr = (uint32_t)&SPI_DATA(SPI0);
  dma_init_struct.memory_addr = (uint32_t)image;
  dma_init_struct.direction = DMA_MEMORY_TO_PERIPHERAL;
  dma_init_struct.memory_width = DMA_MEMORY_WIDTH_8BIT;
  dma_init_struct.periph_width = DMA_PERIPHERAL_WIDTH_8BIT;
  dma_init_struct.priority = DMA_PRIORITY_LOW;
  dma_init_struct.number = FRAME_SIZE;
  dma_init_struct.periph_inc = DMA_PERIPH_INCREASE_DISABLE;
  dma_init_struct.memory_inc = DMA_MEMORY_INCREASE_ENABLE;
  dma_init(DMA0, DMA_CH2, &dma_init_struct);
  /* configure DMA mode */
  dma_circulation_disable(DMA0, DMA_CH2);
  dma_memory_to_memory_disable(DMA0, DMA_CH2);
}
#endif

#if SPI0_CFG == 1
/*!
    \brief      configure the SPI peripheral
    \param[in]  none
    \param[out] none
    \retval     none
*/
void spi_config(void) {
  spi_parameter_struct spi_init_struct;
  /* deinitilize SPI and the parameters */
  OLED_CS_Set();
  spi_struct_para_init(&spi_init_struct);

  /* SPI0 parameter config */
  spi_init_struct.trans_mode = SPI_TRANSMODE_FULLDUPLEX;
  spi_init_struct.device_mode = SPI_MASTER;
  spi_init_struct.frame_size = SPI_FRAMESIZE_8BIT;
  spi_init_struct.clock_polarity_phase = SPI_CK_PL_HIGH_PH_2EDGE;
  spi_init_struct.nss = SPI_NSS_SOFT;
  spi_init_struct.prescale = SPI_PSC_8;
  spi_init_struct.endian = SPI_ENDIAN_MSB;
  spi_init(SPI0, &spi_init_struct);

  spi_crc_polynomial_set(SPI0, 7);
  spi_enable(SPI0);
}
#endif

void LCD_SetRotation_(uint8_t m) {
  rotation_ = m % 4;
  LCD_WriteReg_(ST7789_MADCTL);
  switch (rotation_) {
    case 0:
      colstart = 52;
      rowstart = 40;
      width_ = init_width_;
      height_ = init_height_;
      LCD_WriteData8_(TFT_MAD_COLOR_ORDER);
      break;

    case 1:
      colstart = 40;
      rowstart = 53;
      width_ = init_height_;
      height_ = init_width_;
      LCD_WriteData8_(TFT_MAD_MX | TFT_MAD_MV | TFT_MAD_COLOR_ORDER);
      break;
    case 2:
      colstart = 52;
      rowstart = 40;
      width_ = init_width_;
      height_ = init_height_;
      LCD_WriteData8_(TFT_MAD_MX | TFT_MAD_MY | TFT_MAD_COLOR_ORDER);
      break;
    case 3:
      colstart = 40;
      rowstart = 52;
      width_ = init_height_;
      height_ = init_width_;
      LCD_WriteData8_(TFT_MAD_MV | TFT_MAD_MY | TFT_MAD_COLOR_ORDER);
      break;
  }
}

#define spi_wait_idle()                     \
  do {                                      \
    while (SPI_STAT(SPI0) & SPI_STAT_TRANS) \
      ;                                     \
  } while (0)

#define lcd_mode_data()              \
  do {                               \
    gpio_bit_set(GPIOB, GPIO_PIN_0); \
  } while (0)

static LCD_InitPanel_() {
  static const uint8_t init_sequence[] = {
      ST7789_INVON, 0xff,  // display inversion
      0xb1, 0x05, 0x3a, 0x3a, 0xff,  // frame freq, color: RTNA + FPA + BNA
      ST7789_PORCTRL, 0x05, 0x3a, 0x3a, 0xff,  // frame freq, idle: RTNB + FPB + BPB
      0xb3, 0x05, 0x3a, 0x3a, 0x05, 0x3a, 0x3a, 0xff,  // ff: partial
      0xb4, 0x03, 0xff,
      ST7789_LCMCTRL, 0x62, 0x02, 0x04, 0xff,
      0xc1, 0xc0, 0xff,
      ST7789_VDVVRHEN, 0x0d, 0x00, 0xff,
      ST7789_VRHS, 0x8d, 0x6a, 0xff,
      ST7789_VDVSET, 0x8d, 0xee, 0xff,
      0xc5, 0x0e, 0xff,  // VCCOM
      ST7789_PVGAMCTRL, 0x10, 0x0e, 0x02, 0x03, 0x0e, 0x07, 0x02,
          0x07, 0x0a, 0x12, 0x27, 0x37, 0x00, 0x0d, 0x0e, 0x10, 0xff,
      ST7789_NVGAMCTRL, 0x10, 0x0e, 0x03, 0x03, 0x0f, 0x06, 0x02,
          0x08, 0x0a, 0x13, 0x26, 0x36, 0x00, 0x0d, 0x0e, 0x10, 0xff,
      ST7789_COLMOD, 0x55, 0xff,  // format of RGB picture data: 16bpp
      ST7789_MADCTL, 0x78, 0xff,  // Horiz data
      ST7789_DISPON, 0xff,  // Display on.
      ST7789_SLPOUT, 0xff,  // Turn off sleep mode
      0xff };

  // Initialize the display.
  for (const uint8_t *p = init_sequence; *p != 0xff; p++) {
    LCD_WriteReg_(*p++);
    if (*p == 0xff) continue;
    spi_wait_idle();
    lcd_mode_data();
    while (*p != 0xff) LCD_WriteData8_(*p++);
  }
}

/******************************************************************************
           Function description: LCD initialization function
       Entry data: None
       Return value: None
******************************************************************************/
void LCD_Init(void) {
  lcd_disabled = 0;
  rcu_periph_clock_enable(RCU_GPIOA);
  rcu_periph_clock_enable(RCU_GPIOB);

  // Power up GPIOA and GPIOB. A is probably enabled from LED.
  RCU->APB2EN |= RCU_APB2EN_PAEN | RCU_APB2EN_PBEN;
  // Power up SPI0. This bit seems to float randomly on cold power-up.
  RCU->APB2EN |= RCU_APB2EN_AFEN | RCU_APB2EN_SPI0EN;

  // Clear backlight early just so we can tell we've reset in case
  // the following doesn't work. In practice this doesn't help much.
  OLED_BLK_Clr();

#if SPI0_CFG == 1
  rcu_periph_clock_enable(RCU_AF);
  rcu_periph_clock_enable(RCU_SPI0);
  /* SPI0 GPIO config: NSS/PA4, SCK/PA5, MOSI/PA7 */
  gpio_init(GPIOA, GPIO_MODE_AF_PP, GPIO_OSPEED_50MHZ,
            GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7);
  gpio_init(GPIOB, GPIO_MODE_OUT_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_2);

  spi_config();

#elif SPI0_CFG == 2
  rcu_periph_clock_enable(RCU_DMA0);
  rcu_periph_clock_enable(RCU_SPI0);

  /* SPI0 GPIO config: NSS/PA4, SCK/PA5, MOSI/PA7 */
  gpio_init(GPIOA, GPIO_MODE_AF_PP, GPIO_OSPEED_50MHZ,
            GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_7);
  /* SPI0 GPIO config: MISO/PA6 */
  gpio_init(GPIOA, GPIO_MODE_IN_FLOATING, GPIO_OSPEED_50MHZ, GPIO_PIN_6);

  dma_config();

  dma_channel_enable(DMA0, DMA_CH2);
#elif SPI0_CFG == 3
  gpio_init(GPIOA, GPIO_MODE_OUT_PP, GPIO_OSPEED_50MHZ,
            GPIO_PIN_5 | GPIO_PIN_7);
  gpio_init(GPIOB, GPIO_MODE_OUT_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_2);

  gpio_bit_reset(GPIOA, GPIO_PIN_5 | GPIO_PIN_7);
  gpio_bit_reset(GPIOB, GPIO_PIN_2);
#endif

  gpio_init(GPIOB, GPIO_MODE_OUT_PP, GPIO_OSPEED_50MHZ,
            GPIO_PIN_0 | GPIO_PIN_1);
  gpio_bit_reset(GPIOB, GPIO_PIN_0 | GPIO_PIN_1);

  OLED_RST_Clr();
  delay_1ms(200);
  OLED_RST_Set();
  delay_1ms(20);
  OLED_BLK_Set();

  LCD_InitPanel_();
  LCD_SetRotation_(1);
  cursor_x = 0;
  cursor_y = 0;
}

/******************************************************************************
           Function description: LCD clear screen function
       Entry data: None
       Return value: None
******************************************************************************/
void LCD_Clear(u16 Color) {
  u16 i, j;
  LCD_SetAddress_(0, 0, width_ - 1, height_ - 1);
  for (i = 0; i < width_; i++) {
    for (j = 0; j < height_; j++) {
      LCD_WriteData16_(Color);
    }
  }
}

#if CHINESE
/******************************************************************************
           Function description: LCD display Chinese characters
       Entry data: x, y starting coordinates
                   index Chinese character number
                   size font size
       Return value: None
******************************************************************************/
void LCD_ShowChinese(u16 x, u16 y, u8 index, u8 size, u16 color) {
  u8 i, j;
  u8 *temp, size1;
  if (size == 16) {
    temp = Hzk16;
  }  //选择字号
  if (size == 32) {
    temp = Hzk32;
  }
  LCD_SetAddress_(x, y, x + size - 1, y + size - 1);  //设置一个汉字的区域
  size1 = size * size / 8;  //一个汉字所占的字节
  temp += index * size1;    //写入的起始位置
  for (j = 0; j < size1; j++) {
    for (i = 0; i < 8; i++) {
      if ((*temp & (1 << i)) != 0)  //从数据的低位开始读
      {
        LCD_WriteData16_(color);  //点亮
      } else {
        LCD_WriteData16_(BACK_COLOR);  //不点亮
      }
    }
    temp++;
  }
}
#endif  // CHINESE

/******************************************************************************
           Function description: LCD draws point
       Entry data: x, y starting coordinates
       Return value: None
******************************************************************************/
void LCD_DrawPoint(u16 x, u16 y, u16 color) {
  LCD_SetAddress_(x, y, x, y);  //设置光标位置
  LCD_WriteData16_(color);
}

/******************************************************************************
           Function description: LCD draws a large dot
       Entry data: x, y starting coordinates
       Return value: None
******************************************************************************/
void LCD_DrawPoint_big(u16 x, u16 y, u16 color) {
  LCD_Fill(x - 1, y - 1, x + 1, y + 1, color);
}

/******************************************************************************
           Function description: fill color in the specified area
       Entry data: xsta, ysta starting coordinates
                   xend, yend termination coordinates
       Return value: None
******************************************************************************/
void LCD_Fill(u16 xsta, u16 ysta, u16 xend, u16 yend, u16 color) {
  u16 i, j;
  LCD_SetAddress_(xsta, ysta, xend, yend);  //设置光标位置
  for (i = ysta; i <= yend; i++) {
    for (j = xsta; j <= xend; j++) LCD_WriteData16_(color);  //设置光标位置
  }
}

/******************************************************************************
           Function description: draw a line
       Entry data: x1, y1 starting coordinates
                   x2, y2 terminating coordinates
       Return value: None
******************************************************************************/
void LCD_DrawLine(u16 x1, u16 y1, u16 x2, u16 y2, u16 color) {
  u16 t;
  int xerr = 0, yerr = 0, delta_x, delta_y, distance;
  int incx, incy, uRow, uCol;
  delta_x = x2 - x1;  //计算坐标增量
  delta_y = y2 - y1;
  uRow = x1;  //画线起点坐标
  uCol = y1;
  if (delta_x > 0)
    incx = 1;  //设置单步方向
  else if (delta_x == 0)
    incx = 0;  //垂直线
  else {
    incx = -1;
    delta_x = -delta_x;
  }
  if (delta_y > 0)
    incy = 1;
  else if (delta_y == 0)
    incy = 0;  //水平线
  else {
    incy = -1;
    delta_y = -delta_x;
  }
  if (delta_x > delta_y)
    distance = delta_x;  //选取基本增量坐标轴
  else
    distance = delta_y;
  for (t = 0; t < distance + 1; t++) {
    LCD_DrawPoint(uRow, uCol, color);  //画点
    xerr += delta_x;
    yerr += delta_y;
    if (xerr > distance) {
      xerr -= distance;
      uRow += incx;
    }
    if (yerr > distance) {
      yerr -= distance;
      uCol += incy;
    }
  }
}

/******************************************************************************
           Function description: draw a rectangle
       Entry data: x1, y1 starting coordinates
                   x2, y2 terminating coordinates
       Return value: None
******************************************************************************/
void LCD_DrawRectangle(u16 x1, u16 y1, u16 x2, u16 y2, u16 color) {
  LCD_DrawLine(x1, y1, x2, y1, color);
  LCD_DrawLine(x1, y1, x1, y2, color);
  LCD_DrawLine(x1, y2, x2, y2, color);
  LCD_DrawLine(x2, y1, x2, y2, color);
}

/******************************************************************************
           Function description: draw circle
       Entry data: x0, y0 center coordinates
                   r radius
       Return value: None
******************************************************************************/
void LCD_DrawCircle(u16 x0, u16 y0, u8 r, u16 color) {
  int a, b;
  // int di;
  a = 0;
  b = r;
  while (a <= b) {
    LCD_DrawPoint(x0 - b, y0 - a, color);  // 3
    LCD_DrawPoint(x0 + b, y0 - a, color);  // 0
    LCD_DrawPoint(x0 - a, y0 + b, color);  // 1
    LCD_DrawPoint(x0 - a, y0 - b, color);  // 2
    LCD_DrawPoint(x0 + b, y0 + a, color);  // 4
    LCD_DrawPoint(x0 + a, y0 - b, color);  // 5
    LCD_DrawPoint(x0 + a, y0 + b, color);  // 6
    LCD_DrawPoint(x0 - b, y0 + a, color);  // 7
    a++;
    if ((a * a + b * b) >
        (r * r))  // Determine whether the points to be drawn are too far away
    {
      b--;
    }
  }
}

/******************************************************************************
           Function description: display characters
       Entry data: x, y starting point coordinates
                   num characters to display
                   mode 1 superimposed mode 0 non-superimposed mode
       Return value: None
******************************************************************************/
void LCD_ShowChar(u16 x, u16 y, u8 num, u8 mode, u16 color) {
  u8 temp;
  u8 pos, t;
  u16 x0 = x;
  if (x > width_ - 16 || y > height_ - 16) return;  // Settings window
  num = num - ' ';                                  // Get offset value
  LCD_SetAddress_(x, y, x + 8 - 1, y + 16 - 1);     // Set cursor position
  if (!mode)                                        // Non-overlapping
  {
    for (pos = 0; pos < 16; pos++) {
      temp = asc2_1608[(u16)num * 16 + pos];  // Call 1608 font
      for (t = 0; t < 8; t++) {
        if (temp & 0x01)
          LCD_WriteData16_(color);
        else
          LCD_WriteData16_(BACK_COLOR);
        temp >>= 1;
        x++;
      }
      x = x0;
      y++;
    }
  } else  // overlapping mode
  {
    for (pos = 0; pos < 16; pos++) {
      temp = asc2_1608[(u16)num * 16 + pos];  // Call 1608 font
      for (t = 0; t < 8; t++) {
        if (temp & 0x01) LCD_DrawPoint(x + t, y + pos, color);  // Draw a dot
        temp >>= 1;
      }
    }
  }
}

/******************************************************************************
           Function description: display string
       Entry data: x, y starting point coordinates
                   *p string start address
       Return value: None
******************************************************************************/
void LCD_ShowString(u16 x, u16 y, const u8 *p, u16 color) {
  while (*p != '\0') {
    if (x > width_ - 16) {
      x = 0;
      y += 16;
    }
    if (y > height_ - 16) {
      x = 0;
      y = LCD_H - 16;
      LCD_VerticalScroll(16);
      LCD_Clear(RED);
    }
    LCD_ShowChar(x, y, *p, 0, color);
    x += 8;
    p++;
  }
}

void LCD_Putc(char c, u16 color) {
  int x = cursor_x;
  int y = cursor_y;
  if (c == '\n') {
    x = 0;
    y += 16;
    LCD_ClearToEol();
  } else if (c == '\r') {
    y++;
  } else {
    LCD_ShowChar(x, y, c, 0, color);
    x += 8;
  }

  if (x > LCD_W - 8) {
    x = 0;
    y += 16;
  }
  if (y > LCD_H - 16) {
    x = 0;
    // y = LCD_H - 16;
    y = 0;
    LCD_VerticalScroll(16);
    // LCD_Clear(RED);
  }
  cursor_x = x;
  cursor_y = y;
}

void LCD_Erase() {
  if (cursor_x > 0) {
    cursor_x--;
    LCD_ShowChar(cursor_x, cursor_y, ' ', 0, GREEN);
  }
}

void LCD_ClearToEol() {
  while (cursor_x++ < 320 / 8) {
    LCD_Putc(' ', GREEN);
    cursor_x += 8;
  }
  cursor_x = 0;
}


LCD_VerticalScroll(unsigned lines) {
  return;
}

// END LOCAL

#define SHOW_NUM_NEEDED 0
#if SHOW_NUM_NEEDED
/******************************************************************************
           Function description: display numbers
       Entry data: base m, n exponent
       Return value: None
******************************************************************************/
u32 mypow(u8 m, u8 n) {
  u32 result = 1;
  while (n--) result *= m;
  return result;
}

/******************************************************************************
           Function description: display numbers
       Entry data: x, y starting point coordinates
                   num number to display
                   len number of digits to display
       Return value: None
******************************************************************************/
void LCD_ShowNum(u16 x, u16 y, u32 num, u8 len, u16 color) {
  u8 t, temp;
  u8 enshow = 0;
  for (t = 0; t < len; t++) {
    temp = (num / mypow(10, len - t - 1)) % 10;
    if (enshow == 0 && t < (len - 1)) {
      if (temp == 0) {
        LCD_ShowChar(x + 8 * t, y, ' ', 0, color);
        continue;
      } else
        enshow = 1;
    }
    LCD_ShowChar(x + 8 * t, y, temp + 48, 0, color);
  }
}

/******************************************************************************
           Function description: display decimal
       Entry data: x, y starting point coordinates
                   num decimal to display
                   len number of digits to display
       Return value: None
******************************************************************************/
void LCD_ShowNum1(u16 x, u16 y, float num, u8 len, u16 color) {
  u8 t, temp;
  // u8 enshow=0;
  u16 num1;
  num1 = num * 100;
  for (t = 0; t < len; t++) {
    temp = (num1 / mypow(10, len - t - 1)) % 10;
    if (t == (len - 2)) {
      LCD_ShowChar(x + 8 * (len - 2), y, '.', 0, color);
      t++;
      len += 1;
    }
    LCD_ShowChar(x + 8 * t, y, temp + 48, 0, color);
  }
}
}
#endif  // SHOW_NUM_NEEDED

#if BMP
/******************************************************************************
           Function description: display 160x40 16bit (RGB565) picture
       Entry data: x, y starting point coordinates
       Return value: None
******************************************************************************/
void LCD_ShowPicture(u16 x1, u16 y1, u16 x2, u16 y2) {
  int i;
  LCD_SetAddress_(x1, y1, x2, y2);
  for (i = 0; i < 12800; i++) {
    // LCD_WriteData8_(image[i*2+1]);
    LCD_WriteData8_(image[i]);
  }
}

void LCD_ShowLogo(void) {
  int i;
  LCD_SetAddress_(0, 0, 159, 75);
  for (i = 0; i < 25600; i++) {
    LCD_WriteData8_(logo_bmp[i]);
  }
}

#endif  //  BMP
