#include "stm32f10x.h"                  // Device header
#include "Delay.h"
/*
	需求：按下按键并松开，视为一次切换LED状态



*/
void LED_Init(void);
void KEY_Init(void);

typedef enum{
	UNPRESSED,
	PRESSED
}KeyStatus;
/**
	获取按键是否按下并释放的状态
	返回值只有两种可能性
	1. 按键按下且已经释放，返回 PRESSED
	2. 按键还没有按下，此函数返回 UNPRESSED
**/
KeyStatus KEY_GetKeyStatus(void);

// 切换LED的状态
void LED_SwitchStatus(void);

int main(void) {
    LED_Init();
    KEY_Init();
    while (1) {
        if(KEY_GetKeyStatus() == PRESSED){
			LED_SwitchStatus();
		}
    }
}

// 初始化LED，LED接在PA3
void LED_Init(void) {
    // 开启GPIOA的时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

    GPIO_InitTypeDef GPIO_InitStruct;
    // 初始化PA3引脚
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP; // 推挽输出，Push Pull
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_3;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStruct);
}

// 初始化按键，按键接在PB10上
void KEY_Init(void) {
    // 开启GPIOB的时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB, ENABLE);

    // 初始化PB10引脚
    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU; // 上拉输入模式，In Put Up
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStruct);
}


KeyStatus KEY_GetKeyStatus(void){
	// 1. 判断按键是否已经按下
	if(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_10) == Bit_RESET){ // 检测到低电平，说明已经按下
		// 处理按键抖动
		Delay_Ms(20);
		while(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_10) == Bit_RESET); // 一直按着，就一直是低电平
		// 跳出while说明检测到高电平，说明被释放了，处理抖动
		Delay_Ms(20);
		if(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_10) == Bit_SET){
			return PRESSED;
		}
	}
	// 按键还没有按下
	return UNPRESSED;
}

void LED_SwitchStatus(void){
	if(GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_3) == Bit_SET){
		GPIO_ResetBits(GPIOA, GPIO_Pin_3);
	}else{
		GPIO_SetBits(GPIOA, GPIO_Pin_3);
	}
}
