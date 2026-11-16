#include "stm32f10x.h"    
#include "freertos.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
#include "event_groups.h"
#include "UART1.h"
#include "Delay.h"


void a(){
    printf1("i am a \r\n");
	
}
void b(){
    printf1("i am a \r\n");
}

void task1(void *p) {
	
	vTaskDelay(5000);
	printf1("i am task1 \r\n");
	// TODO: 定时, 10s之后执行 a函数
	
	while(1){
	}
}
void task2(void *p) {
	
	vTaskDelay(3000);
	printf1("i am task2 \r\n");
	// TODO: 定时, 5s之后执行 b函数

	while(1){
	}
}

int main(void){
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
	USART1_Init();
	Delay_Init();

	
	xTaskCreate(task1,"Task1",128*4,NULL,tskIDLE_PRIORITY+2,NULL);
	xTaskCreate(task2,"Task2",128*4,NULL,tskIDLE_PRIORITY+2,NULL);
	vTaskStartScheduler();
}




