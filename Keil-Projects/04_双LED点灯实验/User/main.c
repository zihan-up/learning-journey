#include "stm32f10x.h"                  // Device header
#include "Delay.h"
// 双LED点灯实验，一个在PA0，一个在PB11
void LED_Init(void);

void LED_Init(){
	// 1、开启GPIOA和GPIOB的时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB, ENABLE);
	// 2、初始化外设
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(GPIOA, &GPIO_InitStruct);
	
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_11;
	GPIO_Init(GPIOB, &GPIO_InitStruct);
}
int main(void) {
	LED_Init();
    while (1) {
		GPIO_ResetBits(GPIOB, GPIO_Pin_11);
		GPIO_SetBits(GPIOA, GPIO_Pin_0);
		Delay_Ms(500);
		GPIO_ResetBits(GPIOA, GPIO_Pin_0);
		GPIO_SetBits(GPIOB, GPIO_Pin_11);
		Delay_Ms(500);
    }
}
