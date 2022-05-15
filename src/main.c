/**
  ******************************************************************************
  * @file    main.c
  * @author  Ac6
  * @version V1.0
  * @date    01-December-2013
  * @brief   Default main function.
  ******************************************************************************
*/


#include <Camera_control.h>
#include "stm32f4xx.h"
#include <stdbool.h>
#include "usart.h"
#include "GPIO_config.h"


volatile uint8_t row = 0;

volatile bool status = false;
volatile bool status1 = false;

volatile bool done = false;

volatile bool stop1 = false;
volatile bool stop2 = false;

int main(void)
{

	bool err = true;

	SystemInit();
	MCO1_init();

	I2C1_init();
	I2C2_init();
	DataConfig1();
	DataConfig2();


	UART_init();
	Delay(10);

	while(err){
		err = Camera1_init();

		if (err == true) {
			UART_log("Failed to initialize\r\n");
			}
	}

	err = true;

	while(err){
		err = Camera2_init();

		if (err == true) {
			UART_log("Failed to initialize\r\n");
			}
	}

	ConfigureTimer();
	ConfigureTimer1();


	SignalConfig1();
	SignalConfig2();
	while(1){

	}
}

//VSYNC1
void EXTI1_IRQHandler(){
	if(done==false && stop1==false){
		ConfigureDMA1(0);
		status=true;
	}
	else if(stop1==false)
	{
		status = false;
		for(int i = 0; i<144; i++){
			for(int j = 0; j<174*2; j++){
				while (USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET);
				USART_SendData(USART2, frame_buffer[i][j]);
			}
		}
		done = false;
		stop1 = true;

	}
	if (EXTI_GetITStatus(EXTI_Line1) != RESET){
			EXTI_ClearITPendingBit(EXTI_Line1);
	}

}

//HREF1
void EXTI0_IRQHandler(){
	if(status){
		DMA_Cmd(DMA2_Stream1, ENABLE);
		while(DMA_GetFlagStatus(DMA2_Stream1, DMA_FLAG_TCIF1) == RESET){}
		DMA_Cmd(DMA2_Stream1, DISABLE);
		row+=1;
		if(row==144)done=true;
		else {
			ConfigureDMA1(row);
		}
	}

	if (EXTI_GetITStatus(EXTI_Line0) != RESET){
		EXTI_ClearITPendingBit(EXTI_Line0);
	}
}

//VSYNC2
void EXTI3_IRQHandler(){
	if(done==false && stop1 == true){
		ConfigureDMA2(0);
		status1=true;
	}
	else if(stop1 == true)
	{
		status1 = false;
		for(int i = 0; i<144; i++){
			for(int j = 0; j<174*2; j++){
				while (USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET);
				USART_SendData(USART2, frame_buffer[i][j]);
			}
		}
		done = false;
		stop1 = false;

	}
	if (EXTI_GetITStatus(EXTI_Line3) != RESET){
			EXTI_ClearITPendingBit(EXTI_Line3);
	}

}

//HREF2
void EXTI2_IRQHandler(){
	if(status1){
		DMA_Cmd(DMA2_Stream6, ENABLE);
		while(DMA_GetFlagStatus(DMA2_Stream6, DMA_FLAG_TCIF1) == RESET){}
		DMA_Cmd(DMA2_Stream6, DISABLE);
		row+=1;
		if(row==144)done=true;
		else {
			ConfigureDMA2(row);
		}
	}

	if (EXTI_GetITStatus(EXTI_Line2) != RESET){
		EXTI_ClearITPendingBit(EXTI_Line2);
	}
}

