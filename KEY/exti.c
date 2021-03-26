#include "exti.h"


//开启中断通道
void NVIC_Configuration(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	//配置中断源 (值为位置)
	NVIC_InitStructure.NVIC_IRQChannel = KEY0_INT_EXTI_IRQ;
	//配置抢占优先级
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	//配置子优先级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
	//使能中断通道
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	NVIC_InitStructure.NVIC_IRQChannel = KEY1_INT_EXTI_IRQ;
	NVIC_Init(&NVIC_InitStructure);
	
	NVIC_InitStructure.NVIC_IRQChannel = KEY2_INT_EXTI_IRQ;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
	NVIC_Init(&NVIC_InitStructure);
}


void KEY_Init(void)
{    	 
	//定义一个GPIO初始化的结构体
	GPIO_InitTypeDef  GPIO_InitStructure;
	
	//使能GPIO时钟	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
	
	//GPIOF9,F10初始化设置
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_3 | GPIO_Pin_2;//KEY0、KEY1和KEY2对应IO口
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN; //普通的输入模式
	//GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//推挽输出
	//GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
	GPIO_Init(GPIOE, &GPIO_InitStructure);//初始化GPIO
}


  
void EXIT_Key_Config()
{
	EXTI_InitTypeDef  EXTI_InitStructure;
	
	/* 第一步：初始化要连接到EXIT线的GPIO */
	KEY_Init();
	 
	/* 第二步：初始化EXTI */
	//初始化SYSCFG时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
	//连接到EXTI中断源到KEY0 KEY1 KEY2引脚
	SYSCFG_EXTILineConfig(KEY_EXTI_PORT,KEY0_EXTI_PIN);
	SYSCFG_EXTILineConfig(KEY_EXTI_PORT,KEY1_EXTI_PIN);
	SYSCFG_EXTILineConfig(KEY_EXTI_PORT,KEY2_EXTI_PIN);
	//配置中断源
	EXTI_InitStructure.EXTI_Line = GPIO_Pin_2;//KEY2
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;//中断事件
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising; //上升沿触发
	EXTI_InitStructure.EXTI_LineCmd  = ENABLE;  //使能中断或者时间线
	EXTI_Init(&EXTI_InitStructure);
	
	EXTI_InitStructure.EXTI_Line = GPIO_Pin_3;//KEY1
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;//中断事件
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; //下降沿触发
	EXTI_InitStructure.EXTI_LineCmd  = ENABLE;  //使能中断或者时间线
	EXTI_Init(&EXTI_InitStructure);
	
	EXTI_InitStructure.EXTI_Line = GPIO_Pin_4;//KEY0
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;//中断事件
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling; //上升沿或者下降沿触发
	EXTI_InitStructure.EXTI_LineCmd  = ENABLE;  //使能中断或者时间线
	EXTI_Init(&EXTI_InitStructure); 
	
	/* 第三步：配置NVIC中断控制器 */
	NVIC_Configuration();
	
	/* 第四步：编写中断服务函数 */
	
}
