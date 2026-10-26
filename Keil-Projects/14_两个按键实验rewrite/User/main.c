#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"

/**
	使用两个按键，实现使用按键来控制 LED：
	KEY1：第一个按键的一脚要接在电源正极，常按按键，LED 点亮，松开按键，LED 熄灭。
	按键接在PA8，接在了电源正极，那么松开按键时，输入不确定；按下按键时，输入的是稳定的高电平，适用下拉输入模式；
	KEY2：第二个按键的一脚要接在电源负极，按下并松开按键，实现切换 LED 状态（亮变灭、灭变亮）。
	按键接在PA10，一脚接在电源负极，那么松开按键时，输入不确定，按下按键时，输入的是稳定的低电平，适用上拉输入模式；
**/


// KEY1,接在电源正极和PA8引脚；
void KEY1_Init(void);

// KEY2,接在电源负极和PA10引脚
void KEY2_Init(void);

// LED的初始化，阳极接入PA3引脚，阴极接入负极
void LED_Init(void);



int main(void) {
    KEY1_Init();
    KEY2_Init();
    LED_Init();

    while (1) {
        if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_8) == Bit_SET) {
            GPIO_SetBits(GPIOA, GPIO_Pin_3);
        } else {
            GPIO_ResetBits(GPIOA, GPIO_Pin_3);
        }
		// 后续可以通过中断来实现，后续再写
        if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_10) == Bit_RESET) { // 按键按下
            Delay_Ms(20);

            while (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_10) == Bit_RESET);

            Delay_Ms(20);

            if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_10) == Bit_SET) {
                // 切换LED
                if (GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_3) == Bit_SET) {
                    GPIO_ResetBits(GPIOA, GPIO_Pin_3);
                } else {
                    GPIO_SetBits(GPIOA, GPIO_Pin_3);
                }
            }

        }
    }
}


void KEY1_Init(void) { // PA8，下拉输入模式
    // 开启时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

    // 初始化引脚
    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPD;
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_8;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_Init(GPIOA, &GPIO_InitStruct);

}

void KEY2_Init(void) { // PA10, 上拉
    // 开启时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

    // 初始化引脚
    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_Init(GPIOA, &GPIO_InitStruct);
}

void LED_Init(void) { // PA3，通用推挽输出
    // 开启时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

    // 初始化引脚
    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_3;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_Init(GPIOA, &GPIO_InitStruct);
}
