#include <stdio.h>
#include "stm32f10x.h"
#include "Delay.h"
#include "OLED.h"

// LED灯的状态，分别表示不闪烁、快闪烁、慢闪烁
typedef enum{
	LED_NORMAL,
	LED_FAST_BLINK,
	LED_SLOW_BLINK
}LEDWorkingMode;

// LEDMode用于指示LED当前工作的模式
static LEDWorkingMode g_LEDMode = LED_NORMAL;

// 初始化USART1外设
void USART1_Init(void);

// 初始化PC13指示灯
void LED_Init(void);

// 单片机接收PC端发来的1个字节的数据, 并返回
uint8_t USART1_ReceiveByte(void);

// 处理PC发送的指令, 控制LED的状态
void LED_Control(uint8_t byteRcvd);

int main(void) {
    // 初始化 USART1 的 TX/RX 引脚
    USART1_Init();
    // 初始化LED
    LED_Init();
	
	while(1){
		// 如果PC端没有发指令，那么就会阻塞在USART1_ReceiveByte中，所以不会闪烁
		// 闪烁需要持续的while循环，才有闪烁的效果，阻塞了就没有闪烁的效果
		// 熄灭和点亮是一次性的操作，所以不受影响
		uint8_t RcvdByte = USART1_ReceiveByte();
        LED_Control(RcvdByte);  // 处理指令，控制LED

        if (g_LEDMode == LED_SLOW_BLINK) {
            GPIO_SetBits(GPIOC, GPIO_Pin_13);
            Delay_Ms(500);
            GPIO_ResetBits(GPIOC, GPIO_Pin_13);
            Delay_Ms(500);
        }

        if (g_LEDMode == LED_FAST_BLINK) {
            GPIO_SetBits(GPIOC, GPIO_Pin_13);
            Delay_Ms(100);
            GPIO_ResetBits(GPIOC, GPIO_Pin_13);
            Delay_Ms(100);
        }
	}
	
}


// 处理PC发送的指令, 控制LED的状态
void LED_Control(uint8_t byteRcvd){
	switch (byteRcvd) {
        case '0':
            GPIO_SetBits(GPIOC, GPIO_Pin_13);    // LED 熄灭
            g_LEDMode = LED_NORMAL;
            break;

        case '1':
            GPIO_ResetBits(GPIOC, GPIO_Pin_13);    // LED 亮
            g_LEDMode = LED_NORMAL;
            break;

        case '2':
            // LED设置为慢闪烁状态
            g_LEDMode = LED_SLOW_BLINK;
            break;

        case '3':
            // LED设置为快闪烁状态
            g_LEDMode = LED_FAST_BLINK;
            break;

        default:
            break;
    }
}

// 单片机接收PC端发来的1个字节的数据, 并返回
uint8_t USART1_ReceiveByte(void){
	// 1.等待接收数据寄存器是非空的,也就是等待RXNE标志位被置为1
    while (USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == RESET);

    // 2.将接收数据寄存器当中的1个字节的数据, 读出来
    // 该函数会自动将RXNE标志位置为0
    return (uint8_t)USART_ReceiveData(USART1);

}


// 初始化PC13指示灯
void LED_Init(void){
	// 开启GPIOC时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	
	// 配置PC13引脚为通用开漏输出，PC13指示灯为开漏接法
	// 所以更推荐PC13引脚为开漏输出模式，输出低电平和高阻抗
	GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD; // 通用开漏输出模式
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_Init(GPIOC, &GPIO_InitStructure);

	// PC13默认输出高阻抗,初始状态熄灭LED
    GPIO_SetBits(GPIOC, GPIO_Pin_13);
}

// 初始化USART1外设
void USART1_Init(void){
	// 开启 GPIOA 时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

    GPIO_InitTypeDef GPIO_InitStructure;
    // 配置 TX(PA9)引脚 为复用推挽输出
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; // 复用推挽输出
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    // 配置 RX(PA10)引脚 为浮空输入
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; // 浮空输入模式
    GPIO_Init(GPIOA, &GPIO_InitStructure);

	// 1.开启USART1外设时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);

    // 2.利用USART_Init函数完成USART1外设的初始化
    USART_InitTypeDef USART_InitStruct;
    USART_InitStruct.USART_BaudRate = 115200;   // 波特率设置为115200
    USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;    // 不使用硬件流控
    USART_InitStruct.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;    // 设置为可收可发模式
    USART_InitStruct.USART_Parity = USART_Parity_No;    // 不进行数据校验
    USART_InitStruct.USART_StopBits = USART_StopBits_1;     // 选择1位停止位
    USART_InitStruct.USART_WordLength = USART_WordLength_8b;    // 数据位是8位
    USART_Init(USART1, &USART_InitStruct);

    // 3.使能开启USART1外设
    USART_Cmd(USART1, ENABLE);
}


