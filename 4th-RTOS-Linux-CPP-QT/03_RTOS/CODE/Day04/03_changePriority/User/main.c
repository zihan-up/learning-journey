#include "stm32f10x.h"    
#include "freertos.h"
#include "task.h"
#include "UART1.h"

// 改变优先级(程序运行过程中)

TaskHandle_t hand1, hand2;

void task1(void *p) {
	
	while(1){
		printf1("task1 \r\n");
		
		vTaskDelay(1000);  // x+1000
		
		
//		int num=10000000;
//		while(num >0){
//			num--;
//		}
	}
}

void task2(void *p){
	
	// vTaskDelay(2);
	
	int times = 0;
	while(1){
		printf1("task2 \r\n");
		vTaskDelay(2000); // y+2000
		times++;
		
		if(times > 5){
			vTaskPrioritySet(hand1, 2);
		}
		
		int num=10000000;
		while(num >0){
			num--;
		}
	}
}

int main(void){
	USART1_Init();

	xTaskCreate(task1,"Task1",128,NULL,tskIDLE_PRIORITY+1,&hand1);
	xTaskCreate(task2,"Task2",128,NULL,tskIDLE_PRIORITY+1,&hand2);
	
	vTaskStartScheduler();
}





