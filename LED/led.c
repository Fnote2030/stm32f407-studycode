#include "led.h" 

/*
	名称：led初始化函数
	功能：将led的PF9和PF10配置为输出模式、使能两个端口的时钟，
		  并初始化两个端口为高电平（灯熄灭的状态）
	参数：无
	返回值：无
*/
void LED_Init(void)
{    	 
	//定义一个GPIO初始化的结构体
	GPIO_InitTypeDef  GPIO_InitStructure;
	
	//使能GPIOF时钟	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);
	
	//GPIOF9,F10初始化设置
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10;//LED0和LED1对应IO口
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT; //普通输出模式
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
	GPIO_Init(GPIOF, &GPIO_InitStructure);//初始化GPIO
	
	GPIO_SetBits(GPIOF,GPIO_Pin_9 | GPIO_Pin_10);//GPIOF9,F10设置高，灯灭

}








