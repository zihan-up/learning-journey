#include "stm32f10x.h"                  // Device header
#include "Delay.h"

/**
	使用两个按键，实现使用按键来控制 LED：
	第一个按键的一脚要接在电源正极，常按按键，LED 点亮，松开按键，LED 熄灭。
	按键接在PA8，接在了电源正极，那么松开按键时，输入不确定；按下按键时，输入的是稳定的高电平，适用下拉输入模式；
	第二个按键的一脚要接在电源负极，按下并松开按键，实现切换 LED 状态（亮变灭、灭变亮）。
	按键接在PA10，一脚接在电源负极，那么松开按键时，输入不确定，按下按键时，输入的是稳定的低电平，适用上拉输入模式；
**/


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
void LED_SwitchStatus(void);



int main(void) {
    LED_Init();
    KEY_Init();
	
	uint8_t ledstate = 0; // LED的开关状态，又PA10控制，0灭1亮

    // 上拉输入模式下，默认是输入高电平
    while (1) {
        // 所以这里要监测低电平，低电平才说明已经按下
        if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_8) == Bit_SET) { // PA8已经按下,一定是点亮
            GPIO_SetBits(GPIOA, GPIO_Pin_3); // 给PA3引脚输出高电平,LED点亮
        } else if(ledstate){ // 如果没有按下PA8，那么就要看当前LED的状态，如果当前LED应该是亮的，那么就点亮
            GPIO_SetBits(GPIOA, GPIO_Pin_3);
			}else{ // 如果没有按下PA8，当前LED应该的状态也为灭，就熄灭
			GPIO_ResetBits(GPIOA, GPIO_Pin_3);  // 推挽输出模式，输出0就代表输出低电平，LED熄灭
		}
		
		if(KEY_GetKeyStatus() == PRESSED){ // 如果按下了PA10，那么就切换LED应有的状态
			ledstate = !ledstate;
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

// 初始化按键，按键接在PA8、PA10
void KEY_Init(void) {
    // 开启GPIOA的时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

    // 初始化PA8引脚
    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPD; // 下拉输入模式，In Put Up
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_8;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_Init(GPIOA, &GPIO_InitStruct);
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_Init(GPIOA, &GPIO_InitStruct);
}


KeyStatus KEY_GetKeyStatus(void){
	// 1. 判断按键是否已经按下
	if(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_10) == Bit_RESET){ // 检测到低电平，说明已经按下
		// 处理按键抖动
		Delay_Ms(20);
		while(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_10) == Bit_RESET); // 一直按着，就一直是低电平
		// 跳出while说明检测到高电平，说明被释放了，处理抖动
		Delay_Ms(20);
		if(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_10) == Bit_SET){
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
