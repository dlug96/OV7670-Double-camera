// Includes
#include "stm32f4xx.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_i2c.h"
#include "stm32f4xx_dma.h"
#include <stdbool.h>

// OV7670 camera settings
#define OV7670_REG_NUM 			17
#define OV7670_WRITE_ADDR 		0x42


// Image
volatile uint8_t frame_buffer[144][174*2];
volatile uint8_t frame_buffer2[144][174*2];

//MCO signal
extern void MCO1_init(void);

//I2C config
extern void I2C1_init(void);
extern void I2C2_init(void);

//Timer + DMA config
extern void ConfigureTimer(void);
extern void ConfigureTimer1(void);

extern void ConfigureDMA1(uint8_t row);
extern void ConfigureDMA2(uint8_t row);

//Camera config
extern bool Camera1_init(void);
extern bool Camera2_init(void);


