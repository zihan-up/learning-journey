#include "stm32f10x.h"                  // Device header
#include "Delay.h"

void LED_Init(void);
void KEY_Init(void);

int main(void) {
    LED_Init();
    KEY_Init();

    // 上拉输入模式下，默认是输入高电平
    while (1) {
        // 所以这里要监测低电平，低电平才说明已经按下
        if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_10) == Bit_RESET) { // 输入的是低电平，说明已经按下
            GPIO_SetBits(GPIOA, GPIO_Pin_3); // 给PA3引脚输出高电平,LED点亮
        } else { // 此时是上拉输入模式，若输入高电平，是上拉电阻的缘故，所以没有按下按键
            GPIO_ResetBits(GPIOA, GPIO_Pin_3);  // 推挽输出模式，输出0就代表输出低电平，LED熄灭
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
