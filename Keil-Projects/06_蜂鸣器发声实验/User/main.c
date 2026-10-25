#include "stm32f10x.h"                  // Device header
#include "Delay.h"



int main(void) {
	// 1、开启时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	// 2、初始化GPOIB外设
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_OD;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_15;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(GPIOB, &GPIO_InitStruct);
	// GPIO_ResetBits(GPIOB, GPIO_Pin_15);
	// Delay_Ms(2000);
	// GPIO_SetBits(GPIOB, GPIO_Pin_15);
	
	
	// 延时时间初始设定为500ms，后面会慢慢减少
    uint16_t DelayTime = 500; 
    // 每次缩短的时间间隔，设定为10ms
    uint16_t Step = 20;      
    // 最小的延时时间，设定为10ms
    uint16_t MinDelay = 40; 
    while (1) {
		// 如果已经达到最小延时时长,那么让蜂鸣器持续发声
        if (DelayTime == MinDelay) {
            GPIO_ResetBits(GPIOB, GPIO_Pin_15);
            continue;
        }
        // 在蜂鸣器工作与关闭之间插入延时，即可实现"滴..滴..滴"的效果
        GPIO_ResetBits(GPIOB, GPIO_Pin_15);
        Delay_Ms(DelayTime);
        GPIO_SetBits(GPIOB, GPIO_Pin_15);
        Delay_Ms(DelayTime);

        // 减少延时时间，让滴滴声更急促
        DelayTime -= Step;
    }
}
