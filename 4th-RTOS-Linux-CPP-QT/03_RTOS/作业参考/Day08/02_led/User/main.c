#include "stm32f10x.h"
#include "freertos.h"
#include "task.h"
#include "semphr.h"
#include "UART1.h"


//// ---------------------二值信号量实现----------------------------
//SemaphoreHandle_t semph;

//void task1(void * arg) {
//    // 控制PB1的Led显示
//    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
//    GPIO_InitTypeDef initType;
//    initType.GPIO_Pin = GPIO_Pin_1 ;
//    initType.GPIO_Mode = GPIO_Mode_Out_PP;
//    initType.GPIO_Speed = GPIO_Speed_50MHz;
//    GPIO_Init(GPIOB, &initType);

//		
//    while (1) {
//			xSemaphoreGive(semph);
//			GPIO_SetBits(GPIOB, GPIO_Pin_1);
//			vTaskDelay(1000);
//			
//			xSemaphoreGive(semph);
//			GPIO_ResetBits(GPIOB, GPIO_Pin_1);
//			vTaskDelay(1000);
//    }
//}

//void task2(void * arg) {
//    // 控制PB15的蜂鸣器
//    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

//    GPIO_InitTypeDef GPIO_InitStruct; 
//    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_15; 
//    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
//    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP; 
//    GPIO_Init(GPIOB, &GPIO_InitStruct);

//		int flag = 0;
//    while (1) {
//			  
//				BaseType_t  ret = xSemaphoreTake(semph, 0);
//			  if(ret == pdPASS){
//					flag = flag==0?1:0;
//				}
//			
//				if(flag == 0){
//					GPIO_ResetBits(GPIOB, GPIO_Pin_15);// 响
//				}else{
//					GPIO_SetBits(GPIOB, GPIO_Pin_15); // 不响
//				}
//    }   
//}


//int main(void) {
//    USART1_Init();

//	  semph =  xSemaphoreCreateBinary();
//	
//    xTaskCreate(task1, "Task1", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY + 1, NULL);
//		xTaskCreate(task2, "Task2", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY + 1, NULL);  
//		vTaskStartScheduler();
//}




// ---------------------互斥信号量实现----------------------------
SemaphoreHandle_t semph;

void task1(void * arg) {
    // 控制PB1的Led显示
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    GPIO_InitTypeDef initType;
    initType.GPIO_Pin = GPIO_Pin_1 ;
    initType.GPIO_Mode = GPIO_Mode_Out_PP;
    initType.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &initType);

		
    while (1) {
			xSemaphoreTake(semph, portMAX_DELAY);
			GPIO_SetBits(GPIOB, GPIO_Pin_1);
			vTaskDelay(1000);
			GPIO_ResetBits(GPIOB, GPIO_Pin_1);
			xSemaphoreGive(semph);
			portYIELD();
			
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
			  
				xSemaphoreTake(semph, portMAX_DELAY);
				GPIO_ResetBits(GPIOB, GPIO_Pin_15);// 响
			  vTaskDelay(1000);
			  GPIO_SetBits(GPIOB, GPIO_Pin_15); // 不响	
				xSemaphoreGive(semph);
				portYIELD();
			  
    }   
}


int main(void) {
    USART1_Init();

	  semph = xSemaphoreCreateMutex();
	  xSemaphoreGive(semph);
	
    xTaskCreate(task1, "Task1", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY + 1, NULL);
		xTaskCreate(task2, "Task2", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY + 1, NULL);  
		vTaskStartScheduler();
}


