#include "stm32f10x.h"    
#include "freertos.h"
#include "task.h"
#include "UART1.h"

TaskHandle_t hand1, hand2;

void task1(void *p) {
	while(1){
		vTaskDelay(1000);
		printf1("task1 \r\n");
		
	}
}
void task2(void *p){
	vTaskDelay(2);
	
	int times = 0;
	while(1){
		times++;
		vTaskDelay(1000);
		printf1("task2 \r\n");
		
		if(times>10  && times < 20){
			vTaskSuspend(hand1);
		}
		if(times > 20){
			vTaskResume(hand1);
		}
	}
}
int main(void){
	USART1_Init();
	
	xTaskCreate(task1,"Task1",128*4,NULL,tskIDLE_PRIORITY+1,&hand1);
	xTaskCreate(task2,"Task2",128,NULL,tskIDLE_PRIORITY+1,&hand2);
	
	vTaskStartScheduler();

}



