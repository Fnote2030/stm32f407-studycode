#ifndef __BSP_USART_H
#define __BSP_USART_H
#include "sys.h"

void Usart_Config(void);
void USART_SendByte(USART_TypeDef* USARTx, uint16_t Data);
	

#endif //__BSP_USART_H

