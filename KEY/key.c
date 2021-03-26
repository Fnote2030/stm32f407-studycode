#include "key.h"
#include "delay.h"


/*
	名称：按键初始化函数
	功能：将key的PE2、PE3和PE4配置为输入模式、使能三个端口的时钟，
	参数：无
	返回值：无
*/
void KEY_Init(void)
{    	 
	//定义一个GPIO初始化的结构体
	GPIO_InitTypeDef  GPIO_InitStructure;
	
	//使能GPIOE时钟	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
	
	//GPIOE2、E3、E4初始化设置
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4;//KEY0、KEY1、KEY2对应IO口
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN; //普通输入模式
	//GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//推挽输出
	//GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//没有上拉或者下拉
	GPIO_Init(GPIOE, &GPIO_InitStructure);//初始化GPIO
}


/*
	名称：按键状态检测函数
	功能：检测按键对应端口的IDR状态，GPIOx->IDR & GPIO_Pin==1，返回KEY_ON;
		  GPIOx->IDR & GPIO_Pin==0,返回KEY_OFF
	参数：GPIO_TypeDef * GPIOx--按键的端口组别，uint16_t GPIO_Pin--按键的端口号
	返回值：KEY_OFF--按键按下，KEY_ON--按键没有按下
*/
uint8_t KEY_Scan(GPIO_TypeDef * GPIOx,uint16_t GPIO_Pin)
{
	//按键按下为低电位
	if(GPIO_ReadInputDataBit(GPIOx,GPIO_Pin) == KEY_OFF) //按下按键
	{
		delay_ms(100);
		if(GPIO_ReadInputDataBit(GPIOx,GPIO_Pin) == KEY_OFF) //按下按键
			return KEY_OFF;
		else
			return KEY_ON;
	}		
	else
	{
		return KEY_ON;
	}
}
