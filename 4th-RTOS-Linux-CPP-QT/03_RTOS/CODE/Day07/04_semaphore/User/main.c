#include "stm32f10x.h"    
#include "freertos.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
#include "UART1.h"
#include "Delay.h"


// -------------------------------二值信号量-------------------------------------
SemaphoreHandle_t semaph ;

void task1(void *p) {
	while(1){

		vTaskDelay(5000);
		
		// 释放信号量: 底层向消息队列添加数据
		// 参数: 向哪一个信号量句柄 释放信号量
		// 返回值: pdPASS释放获取信号量成功, 否则失败(重复释放信号量会返回失败)
		xSemaphoreGive(semaph);
		
		
		
	}
}
void task2(void *p) {
	while(1){
		
		
		// 获取信号量
		// 参数1: 去那个信号量的句柄中获取信号量
		// 参数2: 如果没有信号量可以获取, 等待多少时间
		// 返回值: pdPASS成功获取信号量, 否则失败
		// BaseType_t ret = xSemaphoreTake(semaph, portMAX_DELAY);
		BaseType_t ret = xSemaphoreTake(semaph, 1000);

		if(ret == pdPASS){
				printf1("task2 \r\n");
		}else{
				printf1("no \r\n");
		}
		
		
	}
}
int main(void){
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
	USART1_Init();
	Delay_Init();
	
	//Delay_ms(3000);

	// 创建一个二值信号量:     
	//              信号量是一种任务间通信的机制
	//              二值: 二值信号量的两种表现:  有信号, 没有信号
	// 返回值：成功则返回信号量句柄
	semaph =  xSemaphoreCreateBinary();

	
	xTaskCreate(task1,"Task1",128*4,NULL,tskIDLE_PRIORITY+2,NULL);
	xTaskCreate(task2,"Task2",128*4,NULL,tskIDLE_PRIORITY+2,NULL);
	vTaskStartScheduler();
}




