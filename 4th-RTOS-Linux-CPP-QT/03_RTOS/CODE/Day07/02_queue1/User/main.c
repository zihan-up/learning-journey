#include "stm32f10x.h"    
#include "freertos.h"
#include "task.h"
#include "queue.h"
#include "UART1.h"
#include "Delay.h"


// -------  任务和任务间:消息队列----------------------
TaskHandle_t hand1, hand2;
QueueHandle_t queue ;

void task1(void *p) {
	
	while(1){
		
		int num = 10;

		// 第一个参数: 消息队列句柄
		// 第二个参数: 要发送消息的首地址
		// 第三个参数: 阻塞时间 (portMAX_DELAY: 一直等待, 直到可以添加数据)
		// 返回值: 发送数据是否成功
		//BaseType_t ret = xQueueSend(queue, &num, portMAX_DELAY );
		
		BaseType_t ret = xQueueSend(queue, &num, 1000 );
		if(ret == pdPASS){
			printf1("send ok\r\n");
		}else{
			printf1("send error\r\n");
		}
		
		//vTaskDelay(1000);
	}
}
void task2(void *p) {
	
	while(1){
			
			int num = 0;
			
			// 参数一: 从那个消息队列取数数据
			// 参数二: 读取到的消息存在哪里
			// 参数三: 等待时间()
			// 返回值:pdPASS代表收到数据, 否则失败
			BaseType_t ret = xQueueReceive(queue, &num, 1000);
			if(ret == pdPASS){
				printf1("recvdata: %d \r\n", num);
			}else{
				printf1("recv error \r\n");
			}
			
			
			vTaskDelay(5000);
	}
}


int main(void){
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
	USART1_Init();
	Delay_Init();
	
	//Delay_ms(3000);
	
	// 创建消息队列: 动态创建
	
	// 第一个参数: 创建的消息队列, 最终可以存储多少个消息
	// 第二个参数:  单个消息的大小 (单个消息占用的内存) (注意: 要和具体传递的消息一样大)
	// 返回值:消息队列的句柄
	queue = xQueueCreate( 10, 4);
		
	xTaskCreate(task1,"Task1",128*4,NULL,tskIDLE_PRIORITY+2,&hand1);
	xTaskCreate(task2,"Task2",128*4,NULL,tskIDLE_PRIORITY+2,&hand2);
	vTaskStartScheduler();
}


