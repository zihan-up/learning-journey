#include <stdio.h>
#include "stm32f10x.h"
#include "Delay.h"
#include "OLED.h"

// LED灯的状态，分别表示不闪烁、快闪烁、慢闪烁
typedef enum{
	LED_OFF,
	LED_ON,
	LED_FAST_BLINK,
	LED_SLOW_BLINK
}LEDMode_t;

// LEDMode用于指示LED当前工作的模式
static LEDMode_t g_LEDMode = LED_OFF;

// 初始化USART1外设
void USART1_Init(void);

// 初始化PC13指示灯
void LED_Init(void);

// 配置开启USART1外设RXNE中断源
void USART1_RXNEITCongfig(void);

// NVIC配置开启USART1全局中断
void NVIC_USART1_Init(void);

// 中断服务程序
void USART1_IRQHandler(void);

int main(void) {
	LEDMode_t LastLEDMode = LED_OFF;
	// 先进行中断优先级分组配置
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    USART1_Init();
    // 初始化LED
    LED_Init();
	USART1_RXNEITCongfig();
	NVIC_USART1_Init();
	while (1) {
        /* 如果LED工作模式发生变化，则先处理一次模式切换 */
        if (g_LEDMode != LastLEDMode) {
            LastLEDMode = g_LEDMode;    // LED改变了，不要忘记更新最后状态
            switch (g_LEDMode) {
                case LED_OFF:
                    GPIO_SetBits(GPIOC, GPIO_Pin_13);      // LED熄灭
                    break;

                case LED_ON:
                    GPIO_ResetBits(GPIOC, GPIO_Pin_13);    // LED点亮
                    break;

                default:
                    break;
            }
        }

        /* 闪烁模式需要持续执行 */
        if (g_LEDMode == LED_SLOW_BLINK) {
            GPIO_ResetBits(GPIOC, GPIO_Pin_13);
            Delay_Ms(500);
            /* 延时结束后再次确认模式是否仍然没变 */
            if (g_LEDMode != LED_SLOW_BLINK) {
                continue;
            }
            GPIO_SetBits(GPIOC, GPIO_Pin_13);
            Delay_Ms(500);
        } else if (g_LEDMode == LED_FAST_BLINK) {
            GPIO_ResetBits(GPIOC, GPIO_Pin_13); 
            Delay_Ms(100);
            /* 延时结束后再次确认模式是否仍然没变 */
            if (g_LEDMode != LED_FAST_BLINK) {
                continue;
            }
            GPIO_SetBits(GPIOC, GPIO_Pin_13);
            Delay_Ms(100);
        }
    }
}

// USART1全局中断的中断服务程序
void USART1_IRQHandler(void){
	
	// if(USART_GetITStatus(USART1, USART_IT_RXNE) == SET){
		uint8_t ReceiveCmd = (uint8_t)USART_ReceiveData(USART1);
	// }
	switch (ReceiveCmd) {
        case '0':
            GPIO_SetBits(GPIOC, GPIO_Pin_13);    // LED 熄灭
            g_LEDMode = LED_OFF;
            break;

        case '1':
            GPIO_ResetBits(GPIOC, GPIO_Pin_13);    // LED 亮
            g_LEDMode = LED_ON;
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


// 初始化USART1外设
void USART1_Init(void){
	// 1、开启GPIOA和USART1的时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_USART1, ENABLE);
	
	// 2、初始化引脚，对于USART1来说，就是PA9和PA10
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode = GPIO_Pin_9;
	GPIO_InitStruct.GPIO_Pin = GPIO_Mode_AF_PP; // PA9是Tx，使用复用推挽输出模式
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz; // 输出模式才需要设置引脚的输出速度
	GPIO_Init(GPIOA, &GPIO_InitStruct);
	GPIO_InitStruct.GPIO_Mode = GPIO_Pin_10;
	GPIO_InitStruct.GPIO_Pin = GPIO_Mode_IN_FLOATING; // PA10是Rx，使用浮空输入模式
	GPIO_Init(GPIOA, &GPIO_InitStruct);

	// 3、初始化USART1外设本身
	USART_InitTypeDef USART_InitStruct;
	USART_InitStruct.USART_BaudRate = 115200;
	USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStruct.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_InitStruct.USART_Parity = USART_Parity_No;
	USART_InitStruct.USART_StopBits = USART_StopBits_1;
	USART_InitStruct.USART_WordLength = USART_WordLength_8b;
	USART_Init(USART1, &USART_InitStruct);
	
	// 4、开启USART1外设
	USART_Cmd(USART1, ENABLE);
}

// 初始化PC13指示灯
void LED_Init(void){
	// 1、开启时钟，PC13在GPIOC外设上，GPIOC外设在APB2总线上
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	
	// 2、初始化PC13引脚
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode = GPIO_Pin_13;
	GPIO_InitStruct.GPIO_Pin = GPIO_Mode_Out_OD;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(GPIOC, &GPIO_InitStruct);
	
	// 3、PC13默认输出高阻态，LED指示灯熄灭
	GPIO_SetBits(GPIOC, GPIO_Pin_13);
}

// 配置开启USART1外设RXNE中断源
void USART1_RXNEITCongfig(void){
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE); // 理解：设置RXNE为触发中断的标志位
	// 此函数调用后,每当接收数据寄存器非空,USART1外设就会发送中断请求给NVIC外设
}

// NVIC配置开启USART1全局中断
void NVIC_USART1_Init(void){
	// 这里主要是为了初始化NVIC外设，配置USART1触发的中断的优先级等参数
	NVIC_InitTypeDef NVIC_InitStruct;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStruct.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStruct);
}
