#ifndef __SYSTEMINIT_H
#define __SYSTEMINIT_H
#include "sys.h"
#define STARTUP_HSE_TIMEOUT 0x8000
#define STARTUP_HSI_TIMEOUT 0x8000

//HSE 8MHz
void HSE_SystemClock(uint32_t PLLM, uint32_t PLLN, uint32_t PLLP, uint32_t PLLQ);
//HSI 16MHz
void HSI_SystemClock(uint32_t PLLM, uint32_t PLLN, uint32_t PLLP, uint32_t PLLQ);

#endif // __SYSTEMINIT_H

