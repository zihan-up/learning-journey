#include "stm32f10x.h"                  // Device header
#include "Delay.h"



// 需求：完成单个LED点灯实验
// LED灯接在了A0，在GPIOA外设上，需要开启GPIOA外设的时钟，GPIOA在APB2总线上
// 使用的是通用推挽输出的接法，LED的长引脚接在了A0上，另一端接的低电平
int main(void) {
	// 1、开启时钟，时钟是RCC负责开启的
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	// 2、初始化引脚
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(GPIOA, &GPIO_InitStruct);
	// 3、写对应的逻辑
	GPIO_SetBits(GPIOA, GPIO_Pin_0);
	
    while (1) {
		// 加上闪烁的逻辑：
		GPIO_SetBits(GPIOA, GPIO_Pin_0);
		Delay_Ms(500);
		GPIO_ResetBits(GPIOA, GPIO_Pin_0);
		Delay_Ms(500);
    }
}
