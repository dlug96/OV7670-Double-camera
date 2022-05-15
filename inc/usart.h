#ifndef USART_H_
#define USART_H_

void UART_init(void);

//Log a null terminated string

void UART_log(char *s);


 //Send a raw byte

void UART_sendb(uint8_t *val);


 //Read a byte

uint8_t UART_read(void);

#endif /* USART_H_ */
