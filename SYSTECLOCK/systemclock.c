#include "systemclock.h"


/*
	名称：HSE系统时钟设置函数
	功能：将HSE设置为系统时钟
	参数：uint32_t PLLM--HSE的分频倍数
		  uint32_t PLLN--倍频倍数
		  uint32_t PLLP--PLL/PLLP==PLLCLK ，获得锁相环时钟的分频倍数
		  uint32_t PLLQ--外设时钟的分频倍数
	返回值：无
*/
void HSE_SystemClock(uint32_t PLLM, uint32_t PLLN, uint32_t PLLP, uint32_t PLLQ)
{	
	uint16_t STARTUPTIME = 0x00;
	ErrorStatus HSE_ErrorStatus = ERROR;
	//复位RCC的所有寄存器	
	RCC_DeInit();
	//使能HSE
	RCC_HSEConfig(RCC_HSE_ON);
	do
	{
		HSE_ErrorStatus  = RCC_WaitForHSEStartUp();
		STARTUPTIME ++;
	}
	while(STARTUPTIME < STARTUP_HSE_TIMEOUT && HSE_ErrorStatus != SUCCESS);
	
	if(HSE_ErrorStatus == SUCCESS)//成功开启HSE
	{
		//调节电压调节器的模式为1
		RCC->APB1ENR |= RCC_APB1ENR_PWREN;
		PWR->CR |= PWR_CR_VOS;
		
        RCC_HCLKConfig(RCC_SYSCLK_Div1);
        RCC_PCLK1Config(RCC_HCLK_Div4);
        RCC_PCLK2Config(RCC_HCLK_Div2);
		//配置主PLL
		RCC_PLLConfig(RCC_PLLSource_HSE, PLLM, PLLN, PLLP, PLLQ);
		
		//启用PLL //启动之后不能更改配置
		RCC_PLLCmd(ENABLE);
		//是否启用
		while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET)//直到启用
		{
		}
		//配置FLASH预取值，指令缓存，数据缓存，等待周期
		FLASH->ACR = FLASH_ACR_PRFTEN | FLASH_ACR_ICEN |FLASH_ACR_DCEN |FLASH_ACR_LATENCY_5WS;
		//将PLLCLK配置为系统时钟
		RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
		
		//是否配置成功
		while(RCC_GetSYSCLKSource() != 0x08)
		{
		}
	}
	else
	{
		//HSE开启失败的处理函数
	}
}


/*
	名称：HSI系统时钟设置函数
	功能：将HSI设置为系统时钟
	参数：uint32_t PLLM--HSI的分频倍数
		  uint32_t PLLN--倍频倍数
		  uint32_t PLLP--PLL/PLLP==PLLCLK ，获得锁相环时钟的分频倍数
		  uint32_t PLLQ--外设时钟的分频倍数
	返回值：无
*/
void HSI_SystemClock(uint32_t PLLM, uint32_t PLLN, uint32_t PLLP, uint32_t PLLQ)
{	
	uint16_t STARTUPTIME = 0x00;
	volatile uint32_t HSI_ErrorStatus = 0x00;
	//复位RCC的所有寄存器	
	RCC_DeInit();
	//使能HSE
	RCC_HSICmd(ENABLE);
	do
	{
		HSI_ErrorStatus  = RCC->CR & RCC_CR_HSIRDY;
		STARTUPTIME ++;
	}
	while(STARTUPTIME < STARTUP_HSI_TIMEOUT && HSI_ErrorStatus == 0);
	
	if(HSI_ErrorStatus == RCC_CR_HSIRDY)//成功开启HSI
	{
		//调节电压调节器的模式为1
		RCC->APB1ENR |= RCC_APB1ENR_PWREN;
		PWR->CR |= PWR_CR_VOS;
		
        RCC_HCLKConfig(RCC_SYSCLK_Div1);
        RCC_PCLK1Config(RCC_HCLK_Div4);
        RCC_PCLK2Config(RCC_HCLK_Div2);
		//配置主PLL
		RCC_PLLConfig(RCC_PLLSource_HSI, PLLM, PLLN, PLLP, PLLQ);
		
		//启用PLL //启动之后不能更改配置
		RCC_PLLCmd(ENABLE);
		//是否启用
		while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET)//直到启用
		{
		}
		//配置FLASH预取值，指令缓存，数据缓存，等待周期
		FLASH->ACR = FLASH_ACR_PRFTEN | FLASH_ACR_ICEN |FLASH_ACR_DCEN |FLASH_ACR_LATENCY_5WS;
		//将PLLCLK配置为系统时钟
		RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
		
		//是否配置成功
		while(RCC_GetSYSCLKSource() != 0x08)
		{
		}
	}
	else
	{
		//HSE开启失败的处理函数
	}
}

