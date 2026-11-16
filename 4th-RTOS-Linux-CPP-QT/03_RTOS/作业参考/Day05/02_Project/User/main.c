#include "stm32f10x.h"
#include "freertos.h"
#include "task.h"
#include "UART1.h"


TaskHandle_t hand1, hand2, hand3;


void printTaskInfo(TaskHandle_t taskHandle){
			TaskStatus_t xTaskDetails;
			// 获取任务信息
			vTaskGetInfo(taskHandle, &xTaskDetails, pdTRUE, eInvalid);

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
			vTaskDelay(1000);
    }
}
void task2(void * arg) {
    while (1) {
			vTaskDelay(1000);
    }
}
void task3(void * arg) {
    while (1) {
			// ------------方式1----------------------
			// printTaskInfo(hand1);
			// printTaskInfo(hand2);
			// printTaskInfo(hand3);
			// ------------方式二----------------------
			// char buf[160] = {0};
			// vTaskList(buf);
			// printf1("%s \r\n", buf);
			// ------------方式三----------------------
			TaskStatus_t pxTaskStatusArray[4];
			UBaseType_t  uxTaskCount = uxTaskGetSystemState(pxTaskStatusArray, 4, NULL);
			for (UBaseType_t i = 0; i < uxTaskCount; i++)
			{
				printf1("Task: %s, State: %d, Priority: %lu, Stack High Water Mark: %u \r\n",
							 pxTaskStatusArray[i].pcTaskName,
							 pxTaskStatusArray[i].eCurrentState,
							 (unsigned long)pxTaskStatusArray[i].uxCurrentPriority,
							 pxTaskStatusArray[i].usStackHighWaterMark);
			}
			
			vTaskDelay(1000);
    }
}
int main(void) {
    USART1_Init();

    xTaskCreate(task1, "Task1", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY + 1, &hand1);
	  xTaskCreate(task2, "Task2", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY + 1, &hand2);
	  xTaskCreate(task3, "Task3", configMINIMAL_STACK_SIZE*2, NULL, tskIDLE_PRIORITY + 1, &hand3);
		vTaskStartScheduler();

    while (1) {
    }

}

