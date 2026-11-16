#include "stm32f10x.h"
#include "FreeRTOS.h"
#include "task.h"
#include "UART1.h"
#include "Delay.h"


void task1(void *p){
	
	while(1){
		printf1("task1 \r\n");
		Delay_ms(1000);
		vTaskDelay(1000);
	}
}
void task2(void *p){
	
	
	while(1){
		printf1("task2 \r\n");
		vTaskDelay(1000);
	}
}

int main(){
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
	USART1_Init();
	Delay_Init();
	
	xTaskCreate(task1,"Task1",configMINIMAL_STACK_SIZE,NULL,3,NULL);
	xTaskCreate(task2,"Task2",configMINIMAL_STACK_SIZE,NULL,2,NULL);
	vTaskStartScheduler();
}




