#include "stm32f10x.h"
#include "freertos.h"
#include "task.h"
#include "semphr.h"
#include "event_groups.h"
#include "UART1.h"

EventGroupHandle_t  events;

void task1(void * arg) {
    // 控制PB0的Led显示
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    GPIO_InitTypeDef initType;
    initType.GPIO_Pin = GPIO_Pin_0 ;
    initType.GPIO_Mode = GPIO_Mode_Out_PP;
    initType.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &initType);

    while (1) {
			GPIO_SetBits(GPIOB, GPIO_Pin_0);
			xEventGroupSetBits(events, 1<<0);
			vTaskDelay(500);
			xEventGroupSetBits(events, 1<<0);
			
			GPIO_ResetBits(GPIOB, GPIO_Pin_0);
			vTaskDelay(5000);
    }
}
void task2(void * arg) {
    // 控制PB1的Led显示
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    GPIO_InitTypeDef initType;
    initType.GPIO_Pin = GPIO_Pin_1 ;
    initType.GPIO_Mode = GPIO_Mode_Out_PP;
    initType.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &initType);

    while (1) {
			GPIO_SetBits(GPIOB, GPIO_Pin_1);
			xEventGroupSetBits(events, 1<<1);
			vTaskDelay(2000);	
			xEventGroupSetBits(events, 1<<1);
			
			GPIO_ResetBits(GPIOB, GPIO_Pin_1);
			vTaskDelay(2000);
    }
}

void task3(void * arg) {
    // 控制PB15的蜂鸣器
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

    GPIO_InitTypeDef GPIO_InitStruct; 
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_15; 
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP; 
    GPIO_Init(GPIOB, &GPIO_InitStruct);

		int flag1 = 0;
	  int flag2 = 0;
    while (1) {
			  EventBits_t uxBits = xEventGroupWaitBits(events,(1<<0)|(1<<1),pdTRUE,pdFALSE,portMAX_DELAY);

				if (uxBits & 1<<0){
					flag1 = flag1==0?1:0;
				}
				if (uxBits & 1<<1){
					flag2 = flag2==0?1:0;
				}
			  
				if(flag1 == 1 && flag2 == 1){
					GPIO_ResetBits(GPIOB, GPIO_Pin_15);// 响
				}else{
					GPIO_SetBits(GPIOB, GPIO_Pin_15); // 不响
				}
    }   
}


int main(void) {
    USART1_Init();

		events = xEventGroupCreate();
	
    xTaskCreate(task1, "Task1", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY + 1, NULL);
		xTaskCreate(task2, "Task2", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY + 1, NULL);  
	  xTaskCreate(task3, "Task3", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY + 1, NULL);
		vTaskStartScheduler();

}

