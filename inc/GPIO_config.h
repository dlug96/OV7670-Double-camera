#include "stm32f4xx.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_exti.h"
#include "stm32f4xx_syscfg.h"
#include "stm32f4xx_dma.h"
#include <stdbool.h>


//VSYNC & HREF config
extern void SignalConfig1(void);
extern void SignalConfig2(void);

//D0-7 config
extern void DataConfig1(void);
extern void DataConfig2(void);

