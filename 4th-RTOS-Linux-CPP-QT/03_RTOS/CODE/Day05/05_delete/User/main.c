#include "stm32f10x.h"    
#include "freertos.h"
#include "task.h"
#include "UART1.h"



TaskHandle_t hand1, hand2;

void task1(void *p) {
	
	int times = 0;
	while(1){
		
		times++;
//		if(times> 10  && hand2 != NULL){
//			vTaskDelete(hand2);
//			hand2 = NULL;
//		}
		
		if(times> 10  && hand1 != NULL){
			//vTaskDelete(hand1);
			vTaskDelete(NULL);
			hand1 = NULL;
		}
		
		printf1("task1 \r\n");
		vTaskDelay(1000);
	}
}
void task2(void *p){
	while(1){
		printf1("task2 \r\n");
		vTaskDelay(1000);
	}
}

int main(void){
	USART1_Init();
	
	
	// int num
	
	
	// vTaskDelay: 不可以main
	
	// x + 1000
	// y + 2000
	
	xTaskCreate(task1,"Task1",128*4,NULL,tskIDLE_PRIORITY+2,&hand1);
	xTaskCreate(task2,"Task2",128,NULL,tskIDLE_PRIORITY+2,&hand2);
	vTaskStartScheduler();
}


