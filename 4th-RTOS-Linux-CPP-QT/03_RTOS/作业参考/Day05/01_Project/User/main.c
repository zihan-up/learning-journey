#include "stm32f10x.h"
#include "freertos.h"
#include "task.h"
#include "UART1.h"


TaskHandle_t hand1;

void task1(void * arg) {

		int times = 0;
    while (1) {
			times++;
			
			if(times>10){
				vTaskPrioritySet(hand1,3);
			}
			UBaseType_t ret = uxTaskPriorityGet(hand1);
			printf1("Priority:%d \r\n", ret);
		
			vTaskDelay(1000);
    }
}

int main(void) {
    USART1_Init();

    xTaskCreate(task1, "Task1", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY + 1, &hand1);
		vTaskStartScheduler();

    while (1) {
    }

}

