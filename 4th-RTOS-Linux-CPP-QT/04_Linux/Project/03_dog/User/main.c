#include "stm32f10x.h"
#include "freertos.h"
#include "task.h"
#include "queue.h"
#include "UART1.h"
#include "Delay.h"
#include "ADC.h"
#include <string.h>

//int main(void){
//	USART1_Init();
//	Delay_Init();
//
//	// 检查是否是因为IWDG触发的复位
//	if (RCC_GetFlagStatus(RCC_FLAG_IWDGRST) != RESET) {
//		printf1("reset by IWDG \r\n");
//		RCC_ClearFlag();
//	} else {
//		printf1("Normal boot \r\n");
//	}

//	printf1("11111 \r\n");
//
//
//	IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);  // 允许修改
//	IWDG_SetPrescaler(IWDG_Prescaler_4);        // 设置预分频
//	IWDG_SetReload(4095);  // 设置重装值
//	IWDG_Enable();  // 启动 IWDG
//
//	while(1){
//		printf1("while \r\n");
//		//Delay_ms(300);
//		Delay_ms(700);
//
//		//Delay_ms(380);
//		IWDG_ReloadCounter();  // 喂狗
//
//		printf1("nihao\r\n");
//	}
//}

// -----------------窗口看门狗--------------------------------------------------

//int main(void) {
//    USART1_Init();
//    Delay_Init();
//	
//		printf1("111 \r\n");
//    RCC_APB1PeriphClockCmd(RCC_APB1Periph_WWDG, ENABLE);  // 使能WWDG时钟

//    WWDG_SetPrescaler(WWDG_Prescaler_8);  // 设置预分频系数(2^3=8)
//    WWDG_SetWindowValue(0x50);            // 设置窗口值(喂狗不能早于0x50)
//    WWDG_Enable(0x7F);                    // 计数器初值0x7F,启动WWDG

//    while (1) {
//        printf1("while \r\n");
//        // Delay_ms(50);  // 控制喂狗间隔, 确保在窗口期内喂狗
//        Delay_ms(80);
//        // Delay_ms(20);
//        WWDG_SetCounter(0x7F);  // 喂狗, 防止复位
//    }
//}



// 窗口看门狗的早期中断
void WWDG_IRQHandler(void) {
    if (WWDG_GetFlagStatus() != RESET) {  // 检查WWDG是否触发了EWI中断
      // printf1("WWDG_IRQHandler \r\n");
			
			// WWDG_SetCounter(0x7F);  // 不要在这极限喂狗,  毫无意义
			//                            这个中断存在的意义:在复位之前 保存某些数据, 避免数据丢失
			
			
			
			WWDG_ClearFlag();        // 清除WWDG中断标志
    }
}

int main(void) {
    USART1_Init();
    Delay_Init();
	
		
		//    // 检查是否是WWDG触发的复位
		//    if (RCC_GetFlagStatus(RCC_FLAG_WWDGRST) != RESET) {
		//        printf1("reset by WWDG \r\n");
		//        RCC_ClearFlag();
		//    } else {
		//        printf1("Normal boot \r\n");
		//    }
	
		printf1("111 \r\n");
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_WWDG, ENABLE);  // 使能WWDG时钟

    WWDG_SetPrescaler(WWDG_Prescaler_8);  // 设置预分频系数(2^3=8)
    WWDG_SetWindowValue(0x50);            // 设置窗口值(喂狗不能早于0x50)
    WWDG_Enable(0x7F);                    // 计数器初值0x7F,启动WWDG
	
	
	
	  // 配置:  允许窗口看门狗的早期中断触发:  值减到 0100 0000(再减一次超时咬人)的时候出发中断
	  WWDG_ClearFlag();                      // 清除中断标志
    WWDG_EnableIT();                        // 使能WWDG早期唤醒中断(EWI)
    NVIC_EnableIRQ(WWDG_IRQn);              // 使能WWDG中断

	

    while (1) {
        printf1("while \r\n");
        // Delay_ms(50);  // 控制喂狗间隔, 确保在窗口期内喂狗
        Delay_ms(80);
        // Delay_ms(20);
        // WWDG_SetCounter(0x7F);  // 喂狗, 防止复位
    }
}













