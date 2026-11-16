#include "stm32f10x.h"    
#include "freertos.h"
#include "task.h"
#include "UART1.h"

//TaskHandle_t hand1, hand2;

//void task1(void *p) {
//	while(1){
//		vTaskDelay(1000);
//		printf1("task1 \r\n");
//		
//	}
//}
//void task2(void *p){
//	vTaskDelay(2);
//	
//	int times = 0;
//	while(1){
//		times++;
//		vTaskDelay(1000);
//		printf1("task2 \r\n");
//		
//		if(times>10  && times < 20){
//			vTaskSuspendAll();
//		}
//		if(times > 20){
//			xTaskResumeAll();
//		}
//	}
//}
//int main(void){
//	USART1_Init();
//	
//	xTaskCreate(task1,"Task1",128*4,NULL,tskIDLE_PRIORITY+1,&hand1);
//	xTaskCreate(task2,"Task2",128,NULL,tskIDLE_PRIORITY+1,&hand2);
//	
//	vTaskStartScheduler();

//}


// ---------------挂起调度器的使用----------------------
//TaskHandle_t hand1, hand2;

//void task1(void *p) {
//	while(1){
//		//vTaskDelay(1000);
//		printf1("task1 \r\n");
//	}
//}
//void task2(void *p){
//	vTaskDelay(2);

//	while(1){
//		//vTaskDelay(1000);
//		printf1("task2 \r\n");
//	}
//}

//void beginTask(void *p){
//	
//	vTaskSuspendAll();// 不要任务切换
//	xTaskCreate(task1,"Task1",128*4,NULL,tskIDLE_PRIORITY+2,&hand1);
//	xTaskCreate(task2,"Task2",128,NULL,tskIDLE_PRIORITY+2,&hand2);
//	xTaskResumeAll();// 才允许任务切换
//	
//	while(1){
//		printf1("beginTask \r\n");
//	}
//}
//int main(void){
//	USART1_Init();
//	
//	xTaskCreate(beginTask,"beginTask",128,NULL,tskIDLE_PRIORITY+1,&hand2);
//	vTaskStartScheduler();

//}


// ----------------挂起调度器的中间, 不要使用vTaskDelay----------------------------
//TaskHandle_t hand1, hand2;

//void task1(void *p) {
//	while(1){
//		//vTaskDelay(1000);
//		//printf1("task1 \r\n");
//	}
//}
//void task2(void *p){
//	vTaskDelay(2);

//	while(1){
//		//vTaskDelay(1000);
//		//printf1("task2 \r\n");
//	}
//}

//void beginTask(void *p){
//	
//	vTaskSuspendAll();// 不要任务切换
//	xTaskCreate(task1,"Task1",128*4,NULL,tskIDLE_PRIORITY+2,&hand1);
//	xTaskCreate(task2,"Task2",128,NULL,tskIDLE_PRIORITY+2,&hand2);
//	// vTaskDelay(30000);
//	
//	printf1("tag \r\n");
//	xTaskResumeAll();// 才允许任务切换

//	while(1){
//		printf1("beginTask \r\n");
//	}
//}
//int main(void){
//	USART1_Init();
//	
//	xTaskCreate(beginTask,"beginTask",128,NULL,tskIDLE_PRIORITY+1,&hand2);
//	vTaskStartScheduler();
//}






TaskHandle_t hand1, hand2;

void task1(void *p) {
	while(1){
		printf1("task1 \r\n");
	}
}
void task2(void *p){
	vTaskDelay(2);
	while(1){
		printf1("task2 \r\n");
	}
}
int main(void){
	USART1_Init();
	
	xTaskCreate(task1,"Task1",128*4,NULL,tskIDLE_PRIORITY+2,&hand1);
	xTaskCreate(task2,"Task2",128,NULL,tskIDLE_PRIORITY+2,&hand2);
	vTaskStartScheduler();
}


