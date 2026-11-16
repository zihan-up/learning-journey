#include "stm32f10x.h"    
#include "freertos.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
#include "event_groups.h"
#include "UART1.h"
#include "Delay.h"

#define BIT_0 ( 1 << 0 )  // 天黑       00000000000000000000000000000001
#define BIT_1 ( 1 << 1 )  //            00000000000000000000000000000010
#define BIT_2 ( 1 << 2 )  // 光照强     00000000000000000000000000000100
#define BIT_3 ( 1 << 3 )  //            00000000000000000000000000001000
#define BIT_4 ( 1 << 4 )
#define BIT_5 ( 1 << 5 )  // 有声音
#define BIT_6 ( 1 << 6 )
#define BIT_7 ( 1 << 7 )
#define BIT_8 ( 1 << 8 )
#define BIT_9 ( 1 << 9 )
#define BIT_10 ( 1 << 10 )
#define BIT_11 ( 1 << 11 )
#define BIT_12 ( 1 << 12 )
#define BIT_13 ( 1 << 13 )
#define BIT_14 ( 1 << 14 )
#define BIT_15 ( 1 << 15 )
#define BIT_16 ( 1 << 16 )
#define BIT_17 ( 1 << 17 )
#define BIT_18 ( 1 << 18 )
#define BIT_19 ( 1 << 19 )
#define BIT_20 ( 1 << 20 )
#define BIT_21 ( 1 << 21 )
#define BIT_22 ( 1 << 22 )
#define BIT_23 ( 1 << 23 )

EventGroupHandle_t events;


void task1(void *p) {
	
	vTaskDelay(10000);
	
	// 去设置事件标志组的bit位
	// 第一个参数: 事件标志组句柄
	// 第二个参数: 想设置那个标志
	// 返回值:返回事件标志组的状态 (返回值:获取此时此刻时间标志组各个bit结果)
	EventBits_t bits = xEventGroupSetBits(events, BIT_0);
	
	// 00000000000000000000000000000001
	// bits
	if(bits & BIT_0){
	}
	
		
	while(1){
	}
}
void task2(void *p) {
	vTaskDelay(5000);
	EventBits_t bits = xEventGroupSetBits(events, BIT_5);
	while(1){
	}
}
void task3(void *p) {

	// 检测 事件0是否发生, 事件5是否发生
	
	// 等待一个或多个事件位被置位
	// 第一个参数: 事件标志组句柄
	// 第二个参数: 要等待的位
	// 第三个参数: 等等待的位时间发生, 结束等待, 结束等待的时候要不要清除事件: pdTRUE清除, pdFALSE不清除
	// 第四个参数: 等待所有事件发生, 还是等待只要发生一个即可: pdTRUE:等待所有位都被置1, pdFALSE:只要任意一个位被置1就返回
	// 第五个参数: 超时时间
	// 返回值:返回事件标志组的状态 (返回值:获取此时此刻时间标志组各个bit结果)
	//EventBits_t bits = xEventGroupWaitBits(events, BIT_0 | BIT_5, pdTRUE , pdFALSE, portMAX_DELAY );
	EventBits_t bits = xEventGroupWaitBits(events, BIT_0 | BIT_5, pdTRUE , pdFALSE, 1000);
	
	// 
	if(bits & BIT_0){
		printf1("0 ok \r\n");
	}
	if(bits & BIT_5){
		printf1("5 ok \r\n");
	}
	if(bits & BIT_4){
		printf1("4 ok \r\n");
	}
	
	while(1){
	}
}
int main(void){
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
	USART1_Init();
	Delay_Init();

	// 创建事件标志组
	events = xEventGroupCreate();
	
	
	xTaskCreate(task1,"Task1",128*4,NULL,tskIDLE_PRIORITY+2,NULL);
	xTaskCreate(task2,"Task2",128*4,NULL,tskIDLE_PRIORITY+2,NULL);
	xTaskCreate(task3,"Task3",128*4,NULL,tskIDLE_PRIORITY+2,NULL);
	vTaskStartScheduler();
}

