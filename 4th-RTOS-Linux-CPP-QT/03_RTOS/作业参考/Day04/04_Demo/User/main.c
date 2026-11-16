#include "stm32f10x.h"
#include "FreeRTOS.h"
#include "task.h"
#include "UART1.h"


TaskHandle_t  hand1, hand2;

void getMsg(char *str, TaskHandle_t hand){
				TaskStatus_t   xTaskDetails;
        // vTaskGetInfo(hand1, &xTaskDetails,  pdTRUE, eInvalid);
        vTaskGetInfo(hand, &xTaskDetails,  pdTRUE, eInvalid); // NULL代表当前任务

        // 打印获取到的任务信息
        printf1("%s Name: %s  \r\n",str, xTaskDetails.pcTaskName);
        printf1("%s Priority: %d \r\n",str, xTaskDetails.uxCurrentPriority);
        printf1("%s Base Priority: %d \r\n",str, xTaskDetails.uxBasePriority);
        printf1("%s State: %d \r\n",str, xTaskDetails.eCurrentState);
        printf1("%s Stack Base Address: %p \r\n",str, xTaskDetails.pxStackBase);
        printf1("%s High Water Mark: %d \r\n",str, xTaskDetails.usStackHighWaterMark);
        printf1("%s Run Time: %d ticks \r\n",str, xTaskDetails.ulRunTimeCounter);

}
void task1(void  *p) {

    while (1) {

        vTaskDelay(5000);
    }
}

void task2(void *p) {

    while (1) {

        vTaskDelay(5000);
    }
}

void beginTask(void *p) {
    xTaskCreate(task1, "Task1", configMINIMAL_STACK_SIZE, NULL, 2, &hand1);
    xTaskCreate(task2, "Task2", configMINIMAL_STACK_SIZE, NULL, 2, &hand2);

    while (1) {
//        char buf[160] = {0};
//        vTaskList(buf); // 获取任务信息,  给一个任务准备40字节
//        printf1("%s\r\n", buf);
			
			getMsg("task1", hand1);
			getMsg("task2", hand2);
        vTaskDelay(5000);
    }
}

int main() {
    USART1_Init();

    xTaskCreate(beginTask, "beginTask", configMINIMAL_STACK_SIZE*2, NULL, 2, NULL);
    vTaskStartScheduler();

}


