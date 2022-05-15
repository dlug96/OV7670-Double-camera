#include <Camera_control.h>


const uint8_t OV7670_reg[OV7670_REG_NUM][2] = { { 0x12, 0x80 },

		{ 0x12, 0xc },		// 0x8 = QCIF, YUV, 0xc = QCIF (RGB)
		{ 0xc, 0x8 }, 		//
		{ 0x11, 0b1000000 },//

		{ 0x40, 0b11010000 },	//Color mode

		{ 0x11, 0x01 },		//PCLK settings, 15fps
		{ 0x32, 0x80 },		//HREF
		{ 0x17, 0x17 },		//HSTART
		{ 0x18, 0x05 },		//HSTOP
		{ 0x03, 0x0a },		//VREF
		{ 0x19, 0x02 },		//VSTART
		{ 0x1a, 0x7a },		//VSTOP

		// Scalling numbers
		{ 0x70, 0x3a },		//X_SCALING
		{ 0x71, 0x35 },		//Y_SCALING
		{ 0x72, 0x11 },		//DCW_SCALING
		{ 0x73, 0xf0 },		//PCLK_DIV_SCALING
		{ 0xa2, 0x02 },		//PCLK_DELAY_SCALING
 };

void Delay(volatile long nCount) {
	while (nCount--) {
	}
}

void MCO1_init(void) {
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_ClockSecuritySystemCmd(ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

	// GPIO config
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;		//PA8 - XCLK
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	// GPIO AF config
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource8, GPIO_AF_MCO);

	// MCO clock source
	RCC_MCO1Config(RCC_MCO1Source_HSI, RCC_MCO1Div_1);
}

void I2C1_init(void) {
	GPIO_InitTypeDef GPIO_InitStructure;
	I2C_InitTypeDef I2C_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);

	// GPIO config
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	// GPIO AF config
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource6, GPIO_AF_I2C1);
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource7, GPIO_AF_I2C1);

	// I2C config
	I2C_DeInit(I2C1);
	I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;
	I2C_InitStructure.I2C_DutyCycle = I2C_DutyCycle_2;
	I2C_InitStructure.I2C_OwnAddress1 = 0x00;
	I2C_InitStructure.I2C_Ack = I2C_Ack_Enable;
	I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
	I2C_InitStructure.I2C_ClockSpeed = 100000;
	I2C_ITConfig(I2C1, I2C_IT_ERR, ENABLE);
	I2C_Init(I2C1, &I2C_InitStructure);
	I2C_Cmd(I2C1, ENABLE);
}

void I2C2_init(void) {
	GPIO_InitTypeDef GPIO_InitStructure;
	I2C_InitTypeDef I2C_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C2, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);

	// GPIO config
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10|GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	// GPIO AF config
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource10, GPIO_AF_I2C1);
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource3, GPIO_AF_I2C1);

	// I2C config
	I2C_DeInit(I2C1);
	I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;
	I2C_InitStructure.I2C_DutyCycle = I2C_DutyCycle_2;
	I2C_InitStructure.I2C_OwnAddress1 = 0x00;
	I2C_InitStructure.I2C_Ack = I2C_Ack_Enable;
	I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
	I2C_InitStructure.I2C_ClockSpeed = 100000;
	I2C_ITConfig(I2C2, I2C_IT_ERR, ENABLE);
	I2C_Init(I2C2, &I2C_InitStructure);
	I2C_Cmd(I2C2, ENABLE);
}

bool I2C1_write_reg(uint8_t reg_addr, uint8_t* data) {
	uint32_t timeout = 0x7FFFFF;
	while (I2C_GetFlagStatus(I2C1, I2C_FLAG_BUSY)) {
		if ((timeout--) == 0)return true;
	}
	// Send start bit
	I2C_GenerateSTART(I2C1, ENABLE);
	while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT)) {
		if ((timeout--) == 0)return true;
	}
	// Send slave address (camera write address)
	I2C_Send7bitAddress(I2C1, OV7670_WRITE_ADDR, I2C_Direction_Transmitter);
	while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED)) {
		if ((timeout--) == 0)return true;
	}
	// Send register address
	I2C_SendData(I2C1, reg_addr);
	while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED)) {
		if ((timeout--) == 0)return true;

	}
	// Send new register value
	I2C_SendData(I2C1, *data);
	while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED)) {
		if ((timeout--) == 0)return true;
	}
	// Send stop bit
	I2C_GenerateSTOP(I2C1, ENABLE);
	return false;
}

bool I2C2_write_reg(uint8_t reg_addr, uint8_t* data) {
	uint32_t timeout = 0x7FFFFF;
	while (I2C_GetFlagStatus(I2C2, I2C_FLAG_BUSY)) {
		if ((timeout--) == 0)return true;
	}
	// Send start bit
	I2C_GenerateSTART(I2C2, ENABLE);
	while (!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_MODE_SELECT)) {
		if ((timeout--) == 0)return true;
	}
	// Send slave address (camera write address)
	I2C_Send7bitAddress(I2C2, OV7670_WRITE_ADDR, I2C_Direction_Transmitter);
	while (!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED)) {
		if ((timeout--) == 0)return true;
	}
	// Send register address
	I2C_SendData(I2C2, reg_addr);
	while (!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_BYTE_TRANSMITTED)) {
		if ((timeout--) == 0)return true;

	}
	// Send new register value
	I2C_SendData(I2C2, *data);
	while (!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_BYTE_TRANSMITTED)) {
		if ((timeout--) == 0)return true;
	}
	// Send stop bit
	I2C_GenerateSTOP(I2C2, ENABLE);
	return false;
}

void ConfigureTimer(void){
	GPIO_InitTypeDef gpioPCLK;
	TIM_ICInitTypeDef icTIM1;

	//GPIOE config
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);

	gpioPCLK.GPIO_Mode = GPIO_Mode_AF;
	gpioPCLK.GPIO_OType = GPIO_OType_OD;
	gpioPCLK.GPIO_Pin = GPIO_Pin_9;
	gpioPCLK.GPIO_PuPd = GPIO_PuPd_NOPULL;
	gpioPCLK.GPIO_Speed = GPIO_High_Speed;
	GPIO_Init(GPIOE, &gpioPCLK);
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource9, GPIO_AF_TIM1);


	//Timer config
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);

	icTIM1.TIM_Channel = TIM_Channel_1;
	icTIM1.TIM_ICPolarity = TIM_ICPolarity_Rising;
	icTIM1.TIM_ICSelection = TIM_ICSelection_DirectTI;
	icTIM1.TIM_ICPrescaler = TIM_ICPSC_DIV1;
	icTIM1.TIM_ICFilter = 0;
	TIM_ICInit(TIM1, &icTIM1);

	TIM_CtrlPWMOutputs(TIM1, ENABLE);
	TIM_Cmd(TIM1, ENABLE);
	TIM_DMAConfig(TIM1, TIM_DMABase_CCR1, TIM_DMABurstLength_1Transfer);
	TIM_DMACmd(TIM1, TIM_DMA_CC1, ENABLE);

}

void ConfigureTimer1(void){
	GPIO_InitTypeDef gpioPCLK;
	TIM_ICInitTypeDef icTIM1_1;

	//GPIOE config
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);

	gpioPCLK.GPIO_Mode = GPIO_Mode_AF;
	gpioPCLK.GPIO_OType = GPIO_OType_OD;
	gpioPCLK.GPIO_Pin = GPIO_Pin_13;
	gpioPCLK.GPIO_PuPd = GPIO_PuPd_NOPULL;
	gpioPCLK.GPIO_Speed = GPIO_High_Speed;
	GPIO_Init(GPIOE, &gpioPCLK);
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource13, GPIO_AF_TIM1);


	//Timer config
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);

	icTIM1_1.TIM_Channel = TIM_Channel_3;
	icTIM1_1.TIM_ICPolarity = TIM_ICPolarity_Rising;
	icTIM1_1.TIM_ICSelection = TIM_ICSelection_DirectTI;
	icTIM1_1.TIM_ICPrescaler = TIM_ICPSC_DIV1;
	icTIM1_1.TIM_ICFilter = 0;
	TIM_ICInit(TIM1, &icTIM1_1);

	TIM_CtrlPWMOutputs(TIM1, ENABLE);
	TIM_Cmd(TIM1, ENABLE);
	TIM_DMAConfig(TIM1, TIM_DMABase_CCR1, TIM_DMABurstLength_1Transfer);
	TIM_DMACmd(TIM1, TIM_DMA_CC1, ENABLE);

}


void ConfigureDMA1(uint8_t row){

	DMA_InitTypeDef dmaPerToMem;

	//DMA config - peripheral to memory
	//DMA2 Stream 1 Channel 6

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2, ENABLE);

	DMA_DeInit(DMA2_Stream1);

	dmaPerToMem.DMA_BufferSize = 174*2;
	dmaPerToMem.DMA_Channel = DMA_Channel_6;
	dmaPerToMem.DMA_DIR=DMA_DIR_PeripheralToMemory;
	dmaPerToMem.DMA_FIFOMode = DMA_FIFOMode_Disable;
	dmaPerToMem.DMA_FIFOThreshold = DMA_FIFOThreshold_Full;
	dmaPerToMem.DMA_Memory0BaseAddr = (uint32_t) frame_buffer[row];
	dmaPerToMem.DMA_MemoryBurst = DMA_MemoryBurst_Single;
	dmaPerToMem.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
	dmaPerToMem.DMA_MemoryInc = DMA_MemoryInc_Enable;
	dmaPerToMem.DMA_Mode = DMA_Mode_Normal;
	dmaPerToMem.DMA_PeripheralBaseAddr = (uint32_t) (&GPIOC->IDR);
	dmaPerToMem.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
	dmaPerToMem.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
	dmaPerToMem.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	dmaPerToMem.DMA_Priority = DMA_Priority_Medium;
	DMA_Init(DMA2_Stream1, &dmaPerToMem);

}

void ConfigureDMA2(uint8_t row){

	DMA_InitTypeDef dmaPerToMem;

	//DMA config - peripheral to memory
	//DMA2 Stream 1 Channel 6

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2, ENABLE);

	DMA_DeInit(DMA2_Stream6);

	dmaPerToMem.DMA_BufferSize = 174*2;
	dmaPerToMem.DMA_Channel = DMA_Channel_0;
	dmaPerToMem.DMA_DIR=DMA_DIR_PeripheralToMemory;
	dmaPerToMem.DMA_FIFOMode = DMA_FIFOMode_Disable;
	dmaPerToMem.DMA_FIFOThreshold = DMA_FIFOThreshold_Full;
	dmaPerToMem.DMA_Memory0BaseAddr = (uint32_t) frame_buffer2[row];
	dmaPerToMem.DMA_MemoryBurst = DMA_MemoryBurst_Single;
	dmaPerToMem.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
	dmaPerToMem.DMA_MemoryInc = DMA_MemoryInc_Enable;
	dmaPerToMem.DMA_Mode = DMA_Mode_Normal;
	dmaPerToMem.DMA_PeripheralBaseAddr = (uint32_t) (&GPIOD->IDR);
	dmaPerToMem.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
	dmaPerToMem.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
	dmaPerToMem.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	dmaPerToMem.DMA_Priority = DMA_Priority_Medium;
	DMA_Init(DMA2_Stream6, &dmaPerToMem);

}

bool Camera1_init(void) {
	uint8_t data = 0;
	bool err;

	// Configure camera registers
	for (uint8_t i = 0; i < OV7670_REG_NUM; i++) {
		data = OV7670_reg[i][1];
  		err = I2C1_write_reg(OV7670_reg[i][0], &data);

		if (err == true) {
			UART_log("Failed to update register\r\n");
			break;
		}

		Delay(0xFFFF);
	}

	return err;
}

bool Camera2_init(void) {
	uint8_t data = 0;
	bool err;

	// Configure camera registers
	for (uint8_t i = 0; i < OV7670_REG_NUM; i++) {
		data = OV7670_reg[i][1];
  		err = I2C2_write_reg(OV7670_reg[i][0], &data);

		if (err == true) {
			UART_log("Failed to update register\r\n");
			break;
		}

		Delay(0xFFFF);
	}

	return err;
}


