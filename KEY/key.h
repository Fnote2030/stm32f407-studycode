#ifndef __KEY_H
#define __KEY_H
#include "sys.h"

#define  KEY_ON   1
#define  KEY_OFF  0

void KEY_Init(void);
uint8_t KEY_Scan(GPIO_TypeDef * GPIOx,uint16_t GPIO_Pin);

#endif // __KEY_H

