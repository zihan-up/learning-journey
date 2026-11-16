#include "Delay.h"

void Delay_Init(void) {
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);  // 使能TIM2时钟

    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;// 定义结构体
    TIM_TimeBaseStructure.TIM_Period = 0x03E7;   // 设定自动重装值(最大 65535)
    TIM_TimeBaseStructure.TIM_Prescaler = 71;    // 72MHz / (71+1) = 1MHz (1µs 计数增加一次)
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;// TIM_CKD_DIV1标示定时器使用CK_CNT作为时钟
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; // 向上计数
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);// 使用上面配置的参数, 初始化TIM2

    // 配置中断
    TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 11;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}

int flag = 0;
// 中断处理函数
void TIM2_IRQHandler(void) {
    if (TIM_GetITStatus(TIM2, TIM_FLAG_Update) != RESET) {

        flag = 1; 
        TIM_ClearITPendingBit(TIM2, TIM_FLAG_Update);
    }
}

void Delay_1000us(void) {
    flag = 0;
    TIM_Cmd(TIM2, ENABLE);  // 开启TIM2
	
    TIM_SetCounter(TIM2, 0);  // 计数器清零
    while (flag == 0) { // 等待中断触发
    }

    TIM_Cmd(TIM2, DISABLE);  // 关闭TIM2
}

void Delay_ms(uint16_t ms) {
    for (uint16_t i = 0; i < ms; i++) {
        Delay_1000us();
    }
}

