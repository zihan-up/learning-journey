#include "stm32f10x.h"    
#include "freertos.h"
#include "task.h"
#include "UART1.h"

// 静态创建任务:   内存空间需要手动提供



StaticTask_t tcb1;
StackType_t  stackBuff1[128] = {0};

StaticTask_t tcb2;
StackType_t  stackBuff2[128] = {0};

StaticTask_t tcb_idle;
StackType_t  stackBuff_idle[128] = {0};

// 给空闲任务提供内存
void vApplicationGetIdleTaskMemory( StaticTask_t ** ppxIdleTaskTCBBuffer,
																		StackType_t ** ppxIdleTaskStackBuffer,
																		configSTACK_DEPTH_TYPE * puxIdleTaskStackSize )
{

        *ppxIdleTaskTCBBuffer = &tcb_idle;
        *ppxIdleTaskStackBuffer = stackBuff_idle;
        *puxIdleTaskStackSize = configMINIMAL_STACK_SIZE;
}


void task1(void *p) {
	
	while(1){
		printf1("task1 \r\n");
		vTaskDelay(10);
		
		vTaskDelete(NULL);
	}
}

void task2(void *p){
	
	vTaskDelay(2);
	while(1){
		printf1("task2 \r\n");
		vTaskDelay(10);
	}
}

int main(void){
	USART1_Init();
	


	// xTaskCreate(task1,"Task1",128,NULL,tskIDLE_PRIORITY+1,NULL);
	// xTaskCreate(task2,"Task2",128,NULL,tskIDLE_PRIORITY+1,NULL);

	//	 StackType_t * const puxStackBuffer: 栈空间
	//   StaticTask_t * const pxTaskBuffer : TCB空间
	xTaskCreateStatic(task1,"Task1",128,NULL,tskIDLE_PRIORITY+1,stackBuff1, &tcb1);
	xTaskCreateStatic(task2,"Task2",128,NULL,tskIDLE_PRIORITY+1,stackBuff2, &tcb2);
	
	vTaskStartScheduler();

	
}
