#include "stm32f10x.h"
#include "freertos.h"
#include "task.h"
#include "semphr.h"
#include "UART1.h"

SemaphoreHandle_t semaph ;

void task1(void * arg) {

    while (1) {
			printf1("task1 \r\n");
    }
}

void task2(void * arg) {
    
    while (1) {
			printf1("task2 \r\n");
    }   
}


int main(void) {
    USART1_Init();
	
	  semaph = xSemaphoreCreateMutex();
		xSemaphoreGive(semaph);

    xTaskCreate(task1, "Task1", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY + 1, NULL);
		xTaskCreate(task2, "Task2", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY + 1, NULL);  
		vTaskStartScheduler();

    while (1) {
    }

}

