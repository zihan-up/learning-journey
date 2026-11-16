#include "stm32f10x.h"    
#include "freertos.h"
#include "task.h"
#include "UART1.h"
#include "Delay.h"


TaskHandle_t hand1, hand2;

void task1(void *p) {
	
	// 获取FreeRTOS从启动开始, 到此时此刻(代码运行到14行), 
	// 已经过去了多少个FreeRTOS的时钟节拍(默认1ms = 1个FreeRTOS的时钟节拍)
	TickType_t xLastWakeTime = xTaskGetTickCount(); // xLastWakeTime: x
	
	while(1){
		
//		// TODO: 某些逻辑: 20ms ~ 100ms  ~ 300ms
//		if(){
//		}else if{
//		}else{
//			// 
//		}
	
		// vTaskDelay(1000); // 相对延时, vTaskDelay说延时多久就要延时多久
		
		
		// 当程序走到vTaskDelayUntil:   x+1000 -> 什么时候Delay结束
		//  此时此刻的时间可能x+20,   x+100,   x+300
		vTaskDelayUntil(&xLastWakeTime, 1000);// 准时醒来 (绝对延时)
		// 会修改xLastWakeTime(传入传出), vTaskDelayUntil函数结束
		// 会把xLastWakeTime, 改为此时此刻的时间(程序运行到30行结束的时间) : x+1000
		
		// 假设: 控制LED灯亮, 没1s亮/灭
		// TODO:亮灭灯
		
	}
}

int main(void){
	USART1_Init();
	Delay_Init();
	
	//Delay_ms(3000);
	
	xTaskCreate(task1,"Task1",128*4,NULL,tskIDLE_PRIORITY+2,&hand1);
	vTaskStartScheduler();
}


