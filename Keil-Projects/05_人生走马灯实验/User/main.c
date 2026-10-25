#include "stm32f10x.h"                  // Device header
#include "Delay.h"
// 人生走马灯，PA0-PA7
void LED_Init(void);

void LED_Init(){
	// 1、开启GPIOA时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	// 2、初始化外设
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_All; // 直接初始化GPIOA的所有引脚
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(GPIOA, &GPIO_InitStruct);
}
int main(void) {
	LED_Init();
	// value初始值表示向GPIO_PIN_0的输出数据寄存器写1，其它引脚写0
    uint16_t Value = 0x0080;
    while (1) {
		for(uint8_t i = 0;i < 8;i++){
			GPIO_Write(GPIOA, Value);
			Value >>= 1; // 左移一位，点亮下一个 LED
			Delay_Ms(150);
		}
		Value = 0x0080;
    }
}
