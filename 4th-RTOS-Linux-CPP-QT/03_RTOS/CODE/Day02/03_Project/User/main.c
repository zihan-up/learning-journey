#include "stm32f10x.h"      

#include "FreeRTOS.h"
#include "task.h"

// 任务1
void task1(void *p){
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	GPIO_InitTypeDef initType;
	initType.GPIO_Pin =  GPIO_Pin_2;
	initType.GPIO_Mode = GPIO_Mode_Out_PP;
	initType.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &initType);
	while(1){
		GPIO_SetBits(GPIOA, GPIO_Pin_2);
		vTaskDelay(1000);
		GPIO_ResetBits(GPIOA, GPIO_Pin_2);
		vTaskDelay(1000);
	}
	
	// 不允许return, 也不允许走到函数结束 -> while(1){}
}


// 任务2
void task2(void *p){
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	GPIO_InitTypeDef initType;
	initType.GPIO_Pin =  GPIO_Pin_1;
	initType.GPIO_Mode = GPIO_Mode_Out_PP;
	initType.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &initType);
	while(1){
		GPIO_SetBits(GPIOA, GPIO_Pin_1);
		vTaskDelay(1000);
		GPIO_ResetBits(GPIOA, GPIO_Pin_1);
		vTaskDelay(1000);
	}
}



int main(void){	
	
	
	xTaskCreate(task1,"Task2",configMINIMAL_STACK_SIZE,NULL,tskIDLE_PRIORITY+1, NULL);
	xTaskCreate(task2,"Task2",configMINIMAL_STACK_SIZE,NULL,tskIDLE_PRIORITY+1, NULL);
	vTaskStartScheduler();
	
}
