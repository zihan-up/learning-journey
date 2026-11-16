#include "stm32f10x.h"
#include "freertos.h"
#include "task.h"
#include "UART1.h"

StackType_t task1StackBuf[configMINIMAL_STACK_SIZE];
StaticTask_t task1TCB ;
StackType_t task2StackBuf[configMINIMAL_STACK_SIZE];
StaticTask_t task2TCB ;

StackType_t idleStackBuf[configMINIMAL_STACK_SIZE];
StaticTask_t idleTCB ;

// 空闲任务
void vApplicationGetIdleTaskMemory( StaticTask_t ** ppxIdleTaskTCBBuffer,
																		StackType_t ** ppxIdleTaskStackBuffer,
																		configSTACK_DEPTH_TYPE * puxIdleTaskStackSize )
{

		*ppxIdleTaskTCBBuffer = &idleTCB;
		*ppxIdleTaskStackBuffer = idleStackBuf;
		*puxIdleTaskStackSize = configMINIMAL_STACK_SIZE;
}
		
void task1(void * arg) {
    // 控制PB1的Led显示
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    GPIO_InitTypeDef initType;
    initType.GPIO_Pin = GPIO_Pin_1 ;
    initType.GPIO_Mode = GPIO_Mode_Out_PP;
    initType.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &initType);

		
    while (1) {
			GPIO_SetBits(GPIOB, GPIO_Pin_1);
			vTaskDelay(1000);
			GPIO_ResetBits(GPIOB, GPIO_Pin_1);
			vTaskDelay(1000);
    }
}

void task2(void * arg) {
    // 控制PB15的蜂鸣器
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

    GPIO_InitTypeDef GPIO_InitStruct; 
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_15; 
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP; 
    GPIO_Init(GPIOB, &GPIO_InitStruct);

    while (1) {
        GPIO_ResetBits(GPIOB, GPIO_Pin_15);
        vTaskDelay(1000);
        GPIO_SetBits(GPIOB, GPIO_Pin_15);
        vTaskDelay(1000);
    }   
}


int main(void) {
    USART1_Init();

		// 静态创建任务 
    xTaskCreateStatic(task1, "Task1", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY + 1, task1StackBuf, &task1TCB);
		xTaskCreateStatic(task2, "Task2", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY + 1, task2StackBuf, &task2TCB);  
		vTaskStartScheduler();

    while (1) {
    }

}

