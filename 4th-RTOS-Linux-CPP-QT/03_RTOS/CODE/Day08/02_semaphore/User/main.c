#include "stm32f10x.h"    
#include "freertos.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
#include "UART1.h"
#include "Delay.h"


//// -------------------------------计数信号量-------------------------------------
//SemaphoreHandle_t semaph ;

//void task1(void *p) {
//	
//	
//	while(1){
//	}
//	
//	while(1){

//		vTaskDelay(5000);
//		
//		// 释放信号量: 底层向消息队列添加数据
//		// 参数: 向哪一个信号量句柄 释放信号量
//		// 返回值: pdPASS释放获取信号量成功, 否则失败(重复释放信号量会返回失败)
//		xSemaphoreGive(semaph);
//	}
//}
//void task2(void *p) {
//	while(1){
//		
//		UBaseType_t num =  uxSemaphoreGetCount(semaph);
//		printf1("num:%d \r\n", num);
//		
//		// 获取信号量
//		// 参数1: 去那个信号量的句柄中获取信号量
//		// 参数2: 如果没有信号量可以获取, 等待多少时间
//		// 返回值: pdPASS成功获取信号量, 否则失败
//		// BaseType_t ret = xSemaphoreTake(semaph, portMAX_DELAY);
//		BaseType_t ret = xSemaphoreTake(semaph, 1000);

//		if(ret == pdPASS){
//				printf1("task2 \r\n");
//		}else{
//				printf1("no \r\n");
//		}
//		
//		
//	}
//}
//int main(void){
//	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
//	USART1_Init();
//	Delay_Init();

//	
//	// 创建一个计数信号量
//	// 第一个参数: 最多的时候允许有多少个信号量
//	// 第二个参数: 创建这个计数信号量的时候, 初始放入多少个信号量
//	// 返回值: 信号量的句柄
//	semaph =  xSemaphoreCreateCounting(5, 3);

//	
//	
//	xTaskCreate(task1,"Task1",128*4,NULL,tskIDLE_PRIORITY+2,NULL);
//	xTaskCreate(task2,"Task2",128*4,NULL,tskIDLE_PRIORITY+2,NULL);
//	vTaskStartScheduler();
//}





// -------------------------------互斥信号量-------------------------------------


//int num = 0;
//void task1(void *p) {
//	
//	int times = 1500000;
//	while(times > 0){
//		times--;
//		taskENTER_CRITICAL();
//		num++;
//		taskEXIT_CRITICAL();
//	}
//	
//	printf1("num1: %d \r\n", num);
//	while(1){
//	}
//}
//void task2(void *p) {
//	int times = 1500000;
//	while(times > 0){
//		times--;
//		taskENTER_CRITICAL();
//		num++;
//		taskEXIT_CRITICAL();
//	}
//	
//	printf1("num2: %d \r\n", num);
//	while(1){
//	}
//}
//int main(void){
//	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
//	USART1_Init();
//	Delay_Init();

//	
//	
//	xTaskCreate(task1,"Task1",128*4,NULL,tskIDLE_PRIORITY+2,NULL);
//	xTaskCreate(task2,"Task2",128*4,NULL,tskIDLE_PRIORITY+2,NULL);
//	vTaskStartScheduler();
//}



// ---------------------互斥信号量-----------------------------------------
SemaphoreHandle_t semaph ;


int num = 0;
void task1(void *p) {
	
	int times = 1500000;
	while(times > 0){
		times--;
		
		//taskENTER_CRITICAL();
		//xSemaphoreTake(semaph, portMAX_DELAY);
		num++;
		//xSemaphoreGive(semaph);
		// taskEXIT_CRITICAL();
		
	}
	
	printf1("num1: %d \r\n", num);
	while(1){
	}
}
void task2(void *p) {
	int times = 1500000;
	while(times > 0){
		times--;
		
		//taskENTER_CRITICAL();
		//xSemaphoreTake(semaph, portMAX_DELAY);
		num++;
		//xSemaphoreGive(semaph);
		// taskEXIT_CRITICAL();
	}
	
	printf1("num2: %d \r\n", num);
	while(1){
	}
}
int main(void){
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
	USART1_Init();
	Delay_Init();

	// 创建互斥信号量
	semaph =  xSemaphoreCreateMutex();
	// 注意: 互斥信号量(和之前二值/计数信号量不同), 创建完互斥信号, 应该要先提供一个互斥信号量
	xSemaphoreGive(semaph);
	
	
	
	xTaskCreate(task1,"Task1",128*4,NULL,tskIDLE_PRIORITY+2,NULL);
	xTaskCreate(task2,"Task2",128*4,NULL,tskIDLE_PRIORITY+2,NULL);
	vTaskStartScheduler();
}

