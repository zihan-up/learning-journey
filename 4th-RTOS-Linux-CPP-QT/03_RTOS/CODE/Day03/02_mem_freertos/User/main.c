#include "stm32f10x.h"    
#include "freertos.h"
#include "task.h"
#include "UART1.h"


void task1 ( void * arg ){	
	int arr1[10] = {0};
	while(1){
		vTaskDelay(1);
	}
}
void task2 ( void * arg ){
	int arr2[20] = {0};
	while(1){
		vTaskDelay(1);
	}
}
void task3 ( void * arg ){
	int arr3[30] = {0};
	while(1){
		vTaskDelay(1);
	}
}
int main(void){
	USART1_Init();
	
	

	// printf("123 %s  %s", str, str2);

	printf1("nihao  %s  \r\n",   "123");
	
	
	while(1){
	}
	
	
//	int arr[10];
//	xTaskCreate(task1,"Task1",configMINIMAL_STACK_SIZE,NULL,tskIDLE_PRIORITY+1,NULL);
//	xTaskCreate(task2,"Task2",configMINIMAL_STACK_SIZE,NULL,tskIDLE_PRIORITY+1, NULL);
//	xTaskCreate(task3,"Task3",configMINIMAL_STACK_SIZE,NULL,tskIDLE_PRIORITY+1, NULL);
//	vTaskStartScheduler();
//	while(1){
//	}
}
