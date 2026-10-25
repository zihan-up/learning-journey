#include "stm32f10x.h"                  // Device header
#include "Delay.h"
/*
	需求：光敏电阻传感器实验，光线暗时，LED灯亮起；反之熄灭；
	分析，光线变暗时，光敏电阻阻值增大，所以电压比较器正极电压高于负极电压，
	电压比较器输出高阻态，由于上拉电阻的存在，最终DO引脚输出高电平，所以DO-LED熄灭
	
	当光线变亮的时候，光敏电阻阻值减小，电压比较器正极电压小于负极电压，
	电压比较器输出低电平，DO引脚输出低电平，DO-LED亮；
	
	DO接在了PB6，LED灯接在了PA3
*/
void LED_Init(void);
void DO_Init(void);

int main(void) {
	// 初始化LED灯
    LED_Init();
	// 初始化DO引脚
    DO_Init();
	
	while(1){
		// 如果PB6输入高电平，说明光线暗，开灯
		if(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_6) == Bit_SET){
			GPIO_SetBits(GPIOA, GPIO_Pin_3);
		}else{
			GPIO_ResetBits(GPIOA, GPIO_Pin_3);	
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


void DO_Init(void){
	// 开启GPIOB的时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

    GPIO_InitTypeDef GPIO_InitStruct;
    // 初始化PB6引脚
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING; // 推挽输出，Push Pull
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_6;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStruct);

}
