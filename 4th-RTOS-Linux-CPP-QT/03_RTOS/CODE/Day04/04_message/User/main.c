#include "stm32f10x.h"    
#include "freertos.h"
#include "task.h"
#include "UART1.h"

// 通过vTaskGetInfo: 在程序运行过程中, 获取某个任务的信息

TaskHandle_t hand1, hand2;

void task1(void *p) {
	
	while(1){
		
		// A  // 100字节 
		// B  // 200字节
		printf1("task1 \r\n");
		
		vTaskDelay(1000);
	}
}

void task2(void *p){
	

	while(1){
		
		// 获取任务1的信息
		TaskStatus_t  xTaskDetails;
		// 第一个参数: 要获取信息的对应任务的句柄
		vTaskGetInfo(hand2, &xTaskDetails, pdTRUE, eInvalid ); // 250
		
		printf1("Task Name: %s \r\n", xTaskDetails.pcTaskName);
		printf1("Task Priority: %d \r\n", xTaskDetails.uxCurrentPriority);
		printf1("Base Priority: %d  \r\n", xTaskDetails.uxBasePriority);
		printf1("Task State: %d  \r\n", xTaskDetails.eCurrentState);
		printf1("Stack Base Address: %p   \r\n", xTaskDetails.pxStackBase);
		printf1("Stack High Water Mark: %d  \r\n", xTaskDetails.usStackHighWaterMark);
		printf1("Task Run Time: %d ticks  \r\n", xTaskDetails.ulRunTimeCounter);
		
		
		vTaskDelay(2000);
	}
}

int main(void){
	USART1_Init();

	xTaskCreate(task1,"Task1",128,NULL,tskIDLE_PRIORITY+1,&hand1);
	xTaskCreate(task2,"Task2",128,NULL,tskIDLE_PRIORITY+1,&hand2);
	
	vTaskStartScheduler();
}





