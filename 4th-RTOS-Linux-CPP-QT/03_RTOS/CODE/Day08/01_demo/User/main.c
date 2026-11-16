#include "stm32f10x.h"
#include "freertos.h"
#include "task.h"
#include "queue.h"
#include "UART1.h"

QueueHandle_t queue;

void task1(void * arg) {
    // 控制PB1的Led显示
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    GPIO_InitTypeDef initType;
    initType.GPIO_Pin = GPIO_Pin_1 ;
    initType.GPIO_Mode = GPIO_Mode_Out_PP;
    initType.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &initType);

	
		char buf[10] = {0};
		while(1){
				char ch = 0;
				BaseType_t ret = xQueueReceive(queue, &ch, 1000);
				if(ret == pdPASS){
					buf[strlen(buf)] = ch;
				}else{
				}
	
				//printf1("main.c:task1:27:--%s--\r\n", buf);
				if (strcmp(buf, "OK") == 0) {
						printf1("light on \r\n");
						GPIO_SetBits(GPIOB, GPIO_Pin_1);
						vTaskDelay(1000);
						memset(buf, 0, sizeof(buf));
				} else if (strcmp(buf, "ERROR") == 0) {
						printf1("light off \r\n");
						GPIO_ResetBits(GPIOB, GPIO_Pin_1);
						vTaskDelay(1000);
						memset(buf, 0, sizeof(buf));
				}
		
		}
	
}

int main(void) {
    USART1_Init();

	
		queue = xQueueCreate( 10, 1);
	
	
    xTaskCreate(task1, "Task1", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY + 1, NULL);
    vTaskStartScheduler();

    while (1) {
    }

}

