#include "stm32f10x.h"    
#include "freertos.h"
#include "task.h"
#include "UART1.h"

// ----------------------------------------------------------
int num = 0;

//TaskHandle_t hand1, hand2;

//void task1(void *p) {
//	
//	for(int i=0; i<100000; i++){
//		 // vTaskSuspendAll();
//		//taskENTER_CRITICAL();
//		 portDISABLE_INTERRUPTS();
//	  num++;
//		 portENABLE_INTERRUPTS();
//		//taskEXIT_CRITICAL();
//		 // xTaskResumeAll();
//	}
//	
//	printf1("num: %d \r\n", num);
//	
//	while(1){
//	}
//}
//void task2(void *p){
//	for(int i=0; i<100000; i++){
//		// vTaskSuspendAll();
//		//taskENTER_CRITICAL();
//		 portDISABLE_INTERRUPTS();
//	  num++;
//		 portENABLE_INTERRUPTS();
//		//taskEXIT_CRITICAL();
//		// xTaskResumeAll();
//	}

//	printf1("num: %d \r\n", num);
//	
//	while(1){
//	}
//}

//int main(void){
//	USART1_Init();
//	
//	xTaskCreate(task1,"Task1",128*4,NULL,tskIDLE_PRIORITY+2,&hand1);
//	xTaskCreate(task2,"Task2",128,NULL,tskIDLE_PRIORITY+2,&hand2);
//	vTaskStartScheduler();
//}


// ---------------------------------------------------------

TaskHandle_t hand1, hand2;

void task1(void *p) {
	while(1){
		printf1("task1 \r\n");
	}
}
void task2(void *p){
	while(1){
		printf1("task2 \r\n");
	}
}

void begTask(void *p){
	
	taskENTER_CRITICAL(); // 计数机制
	//portDISABLE_INTERRUPTS();  // 没有计数机制
	xTaskCreate(task1,"Task1",128*4,NULL,tskIDLE_PRIORITY+2,&hand1);
	xTaskCreate(task2,"Task2",128,NULL,tskIDLE_PRIORITY+2,&hand2);
	//portENABLE_INTERRUPTS();
	taskEXIT_CRITICAL();
	
	while(1){
	}
}
int main(void){
	USART1_Init();
	
	xTaskCreate(begTask,"begTask",128,NULL,tskIDLE_PRIORITY+1,NULL);
	vTaskStartScheduler();
}


