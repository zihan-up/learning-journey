#include "stm32f10x.h"    
#include "freertos.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
#include "event_groups.h"
#include "UART1.h"
#include "Delay.h"


void sleep_pre(){
	// 手动关闭片上外设
}
void sleep_post(){
	// 手动开启片上外设
}


void a(TimerHandle_t xTimer ){
    printf1("i am a \r\n");
	
}
void b(){
    printf1("i am b \r\n");
}

void task1(void *p) {
	
	vTaskDelay(5000);
	printf1("i am task1 \r\n");
	// TODO: 定时, 10s之后执行 a函数
	
	
	// 1, 创建软件定时器
	// 参数1: 当前要定时的名字
	// 参数2: 定时器多久响 (单位FreeRTOS的系统的时钟节拍, 默认1ms)
	// 参数3: 当前这个定时器要不要循环触发(pdTRUE/pdFALSE)
	// 参数4: 当前这个定时器的id标识
	// 参数5: 定时器的回调函数
	// 返回值:  当前定时器的句柄
  TimerHandle_t tima = xTimerCreate("a", 10000, pdTRUE, NULL, a);
	
	
	
	// 2, 启动定时器(就是把配置参数要求的定时器, 移交给定时器任务管理)
	// 参数1: 要启动那个定时器(定时器的句柄)
	// 参数2: 阻塞时间( 我们向定时器任务移交定时器的本质是通过消息队列通信)
	//                 (如果消息队列满了, 这个时间就是等待时间)
	// 返回值: 函数执行成功pdPASS
	xTimerStart(tima, 10000);

	
	
	while(1){
	}
}
void task2(void *p) {
	
	vTaskDelay(3000);
	printf1("i am task2 \r\n");
	// TODO: 定时, 5s之后执行 b函数

	TimerHandle_t timb = xTimerCreate("b", 5000, pdTRUE, NULL, b);
	xTimerStart(timb, 10000);

	
	vTaskDelay(11000);
	
	xTimerStop(timb, 1000);
	vTaskDelay(11000);
	xTimerStart(timb, 10000);
	
	// 修改定时器的执行周期
	xTimerChangePeriod(timb, 1000, 1000);
//	BaseType_t xTimerChangePeriod(
//		TimerHandle_t xTimer,      // 目标定时器句柄
//		TickType_t xNewPeriod,     // 新的定时周期(时钟节拍)
//		TickType_t xTicksToWait    // 阻塞等待时间
//	);
	
	while(1){
	}
}


int main(void){
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
	USART1_Init();
	Delay_Init();

	
	xTaskCreate(task1,"Task1",128*4,NULL,tskIDLE_PRIORITY+2,NULL);
	xTaskCreate(task2,"Task2",128*4,NULL,tskIDLE_PRIORITY+2,NULL);
	vTaskStartScheduler();
}




