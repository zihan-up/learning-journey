#include "stm32f10x.h"    
#include "freertos.h"
#include "task.h"
#include "UART1.h"
#include "Delay.h"


TaskHandle_t hand1, hand2;

void task1(void *p) {
	
	while(1){
		printf1("task1 \r\n");
		Delay_ms(1000);
	}
}
void task2(void *p){
	
	while(1){
		printf1("task2 \r\n");
		Delay_ms(1000);
	}
}

int main(void){
	USART1_Init();
	Delay_Init();
	
	Delay_ms(3000);
	printf1("main   \r\n");
	
	
	xTaskCreate(task1,"Task1",128*4,NULL,tskIDLE_PRIORITY+2,&hand1);
	xTaskCreate(task2,"Task2",128,NULL,tskIDLE_PRIORITY+1,&hand2);
	vTaskStartScheduler();
}


