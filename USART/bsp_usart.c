#include "bsp_usart.h"


//开启中断通道
void NVIC_Configuration(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	//嵌套向量中断控制器组选择
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置系统中断优先级分组2
	
	//配置中断源 (值为位置)
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	//配置抢占优先级(主优先级)
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;
	//配置子优先级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
	//使能中断通道
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	//初始化
	NVIC_Init(&NVIC_InitStructure);
}



/*
	名称：USART1初始化函数
	作用：1、开启串口对应端口的时钟、配置端口模式，上下拉，速度等
		  2、配置串口通信的各种属性
		  3、开启串口中断
	输入：无
	输出：无
*/
void Usart_Config(void)	
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	
	/*第一步：初始化USART对应的端口*/
	//使能GPIOA时钟
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE); //使能GPIOA时钟
	//USART1端口TX配置
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; //GPIOA9
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//复用功能
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//速度50MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //推挽复用输出
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; //上拉
	GPIO_Init(GPIOA,&GPIO_InitStructure); //初始化PA9
	//USART1端口RX配置
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10; //GPIOA10
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//复用功能
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//速度50MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //推挽复用输出
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; //上拉
	GPIO_Init(GPIOA,&GPIO_InitStructure); //初始化PA10
	//串口1对应引脚复用映射
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource9,GPIO_AF_USART1); //GPIOA9复用为USART1
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource10,GPIO_AF_USART1); //GPIOA10复用为USART1


	/*第二步：*USART1 初始化设置*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);//使能USART1时钟
	
	USART_InitStructure.USART_BaudRate = 115200;//波特率设置
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式
    USART_Init(USART1, &USART_InitStructure); //初始化串口1 
	
	
	/*第三步：使能串口1中断*/
	//使能串口接收中断
	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);
	//使能串口1全局中断通道
	NVIC_Configuration();	
	
	/*第四步：使能串口*/
	USART_Cmd(USART1, ENABLE);  //使能串口1
}


void  USART_SendByte(USART_TypeDef* USARTx, uint16_t Data)
{
	USART_SendData(USARTx, Data);
	//发送数据寄存器为空
	while(USART_GetFlagStatus(USARTx, USART_FLAG_TXE) == RESET)
		;
}


