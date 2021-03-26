#ifndef _EXIT_H_
#define _EXIT_H_

#include "sys.h"

#define   KEY_EXTI_PORT    EXTI_PortSourceGPIOE       
#define   KEY0_EXTI_PIN    EXTI_PinSource2            
#define   KEY1_EXTI_PIN    EXTI_PinSource3 
#define   KEY2_EXTI_PIN    EXTI_PinSource4 

#define   KEY2_INT_EXTI_IRQ    EXTI2_IRQn
#define   KEY1_INT_EXTI_IRQ    EXTI3_IRQn
#define   KEY0_INT_EXTI_IRQ    EXTI4_IRQn


void EXIT_Key_Config(void);
void KEY_Init(void);

#endif // _EXIT_H_
