#include "stm32f10x.h"
#include "freertos.h"
#include "task.h"
#include "UART1.h"


void printTaskInfo(TaskStatus_t xTaskDetails){

			// 打印任务信息
			printf1("Task Name: %s \r\n", xTaskDetails.pcTaskName);
			printf1("Task Priority: %d \r\n", xTaskDetails.uxCurrentPriority);
			printf1("Base Priority: %d \r\n", xTaskDetails.uxBasePriority);
			printf1("Task State: %d \r\n", xTaskDetails.eCurrentState);
			printf1("Stack Base Address: %p \r\n", xTaskDetails.pxStackBase);
			printf1("Stack High Water Mark: %d \r\n", xTaskDetails.usStackHighWaterMark);
			printf1("Task Run Time: %d ticks \r\n", xTaskDetails.ulRunTimeCounter);
}
void task1(void * arg) {
    while (1) {
			
			// ------方式1-----
			// TaskHandle_t hand = xTaskGetHandle("Task1");
			// TaskStatus_t xTaskDetails;
			// vTaskGetInfo(hand, &xTaskDetails, pdTRUE, eInvalid);
			// printTaskInfo(xTaskDetails);
			// ------方式2-----
			TaskStatus_t xTaskDetails;
			vTaskGetInfo(NULL, &xTaskDetails, pdTRUE, eInvalid);
			printTaskInfo(xTaskDetails);
			
			vTaskDelay(1000);
    }
}
int main(void) {
    USART1_Init();

    xTaskCreate(task1, "Task1", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY + 1, NULL);
		vTaskStartScheduler();

    while (1) {
    }

}

