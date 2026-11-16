#include "stm32f10x.h"
#include "freertos.h"
#include "task.h"
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

    char buf[50] = {0};

    while (1) {
        char ch = 0;
        BaseType_t ret = xQueueReceive(queue, &ch, 1000);
				
        if (ret == pdFAIL) {
            // 没收到数据
        } else {
            // 收到数据
            buf[strlen(buf)] = ch;
        }

        if (strcmp(buf, "OK") == 0) {
            printf1("light on \r\n");
            GPIO_SetBits(GPIOB, GPIO_Pin_1);
						
            memset(buf, 0, sizeof(buf));
        } else if (strcmp(buf, "ERROR") == 0) {
						printf1("light off \r\n");
						GPIO_ResetBits(GPIOB, GPIO_Pin_1);
						
            memset(buf, 0, sizeof(buf));
        }

    }
}

int main(void) {
		NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
    USART1_Init();
	

    queue = xQueueCreate(100, 1);

    xTaskCreate(task1, "Task1", configMINIMAL_STACK_SIZE*2, NULL, tskIDLE_PRIORITY + 1, NULL);
    vTaskStartScheduler();

    while (1) {
    }

}

