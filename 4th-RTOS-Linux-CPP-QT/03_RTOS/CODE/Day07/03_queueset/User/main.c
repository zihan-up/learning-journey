#include "stm32f10x.h"    
#include "freertos.h"
#include "task.h"
#include "queue.h"
#include "UART1.h"
#include "Delay.h"


// -------  任务和任务间:消息队列----------------------
//TaskHandle_t hand1, hand2;
//QueueHandle_t queue1, queue2 ;

//void task1(void *p) {
//	
//	while(1){
//		
//		// 读取引脚(偷懒, 中断/外部中断不准备用), 高电平/低电平 ->按钮
//		// 任务1: 读取按键1  -> 亮灯
//		
//		int num = 10;
//		xQueueSend(queue1, &num, 1000 );
//		vTaskDelay(1000);
//	}
//}
//void task2(void *p) {
//	
//	while(1){
//		// 读取引脚(偷懒, 中断/外部中断不准备用), 高电平/低电平 ->按钮
//		// 任务2: 读取按键2  -> 向串口打印
//			
//			int num = 10;
//		xQueueSend(queue2, &num, 1000 );
//		vTaskDelay(1000);
//	}
//}
//void task3(void *p) {
//	
//	while(1){
//		
//		// "监控" -> queue1有数据,  queue2有数据了   -> 队列集: 队列的集合
//		
//			//  亮灯, 串口打印
//			int num = 0;
//			xQueueReceive(queue1, &num, portMAX_DELAY);
//			if(num == 10){
//				// 亮灯
//			}
//			xQueueReceive(queue2, &num, portMAX_DELAY);
//			if(num == 10){
//				// 串口打印
//			}
//		
//	}
//}


//int main(void){
//	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
//	USART1_Init();
//	Delay_Init();
//	
//	//Delay_ms(3000);

//	queue1 = xQueueCreate( 10, 4);
//	queue2 = xQueueCreate( 10, 4);
//		
//	xTaskCreate(task1,"Task1",128*4,NULL,tskIDLE_PRIORITY+2,&hand1);
//	xTaskCreate(task2,"Task2",128*4,NULL,tskIDLE_PRIORITY+2,&hand2);
//	xTaskCreate(task3,"Task3",128*4,NULL,tskIDLE_PRIORITY+2,NULL);
//	vTaskStartScheduler();
//}


// -----------------------------
//TaskHandle_t hand1, hand2;
//QueueHandle_t queue ;

//void task1(void *p) {
//	
//	while(1){
//		
//		// 读取引脚(偷懒, 中断/外部中断不准备用), 高电平/低电平 ->按钮
//		// 任务1: 读取按键1  -> 亮灯
//		
//		int num = 10;
//		xQueueSend(queue, &num, 1000 );
//		vTaskDelay(1000);
//	}
//}
//void task2(void *p) {
//	
//	while(1){
//		// 读取引脚(偷懒, 中断/外部中断不准备用), 高电平/低电平 ->按钮
//		// 任务2: 读取按键2  -> 向串口打印
//			
//			int num = 20;
//		xQueueSend(queue, &num, 1000 );
//		vTaskDelay(1000);
//	}
//}
//void task3(void *p) {
//	
//	while(1){
//			//  亮灯, 串口打印
//			int num = 0;
//			xQueueReceive(queue, &num, portMAX_DELAY);
//			if(num == 10){
//				// 亮灯
//			}else if(num == 20){
//				// 串口打印
//			}

//			vTaskDelay(5000);
//	}
//}


//int main(void){
//	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
//	USART1_Init();
//	Delay_Init();
//	
//	//Delay_ms(3000);

//	queue = xQueueCreate( 10, 4);
//		
//	xTaskCreate(task1,"Task1",128*4,NULL,tskIDLE_PRIORITY+2,&hand1);
//	xTaskCreate(task2,"Task2",128*4,NULL,tskIDLE_PRIORITY+2,&hand2);
//	xTaskCreate(task3,"Task3",128*4,NULL,tskIDLE_PRIORITY+2,NULL);
//	vTaskStartScheduler();
//}


// ---------------------------------队列集-------------------------------------

TaskHandle_t hand1, hand2;
QueueHandle_t queue1, queue2 ;
QueueSetHandle_t queueset;

void task1(void *p) {
	
	while(1){
		
		// 读取引脚(偷懒, 中断/外部中断不准备用), 高电平/低电平 ->按钮
		// 任务1: 读取按键1  -> 亮灯
		
		int num = 10;
		xQueueSend(queue1, &num, 1000 );
		vTaskDelay(2000);
	}
}
void task2(void *p) {
	
	while(1){
		// 读取引脚(偷懒, 中断/外部中断不准备用), 高电平/低电平 ->按钮
		// 任务2: 读取按键2  -> 向串口打印
			
		int num = 10;
		xQueueSend(queue2, &num, 1000 );
		vTaskDelay(10000);
	}
}
void task3(void *p) {
	
	while(1){
		
		// "监控" -> queue1有数据,  queue2有数据了   -> 队列集: 队列的集合
		
		// xQueueSelectFromSet: 监控队列集中, 那个消息队列存储的有数据,
		//                      返回那个有数据的队列的句柄
		// 第一个参数: 要监控的队列集
		// 第二个参数: 超时时间
		// 返回值: 队列中那个队列有数据了
		QueueSetMemberHandle_t  queue = xQueueSelectFromSet(queueset, portMAX_DELAY);
		
		int num = 0;
		if(queue == queue1){
				xQueueReceive(queue1, &num, portMAX_DELAY);
				printf1("queue1 recv \r\n");
		}
		if(queue == queue2){
				xQueueReceive(queue2, &num, portMAX_DELAY);
				printf1("queue2 recv \r\n");
		}
		
	}
}


int main(void){
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
	USART1_Init();
	Delay_Init();
	
	//Delay_ms(3000);

	queue1 = xQueueCreate( 10, 4);
	queue2 = xQueueCreate( 15, 4);
	
	// 创建队列集
	// 参数: 队列集中所有消息队列的消息总个数
	// 返回值: 返回队列集的句柄
	queueset =  xQueueCreateSet(25);
		
	// 把消息队列放入队列集中
	// 第一个参数: 队列
	// 第二个参数: 队列集
	// 返回值: pdPASS代表成功, 否则失败
	xQueueAddToSet(queue1, queueset);
	xQueueAddToSet(queue2, queueset);

	
	xTaskCreate(task1,"Task1",128*4,NULL,tskIDLE_PRIORITY+2,&hand1);
	xTaskCreate(task2,"Task2",128*4,NULL,tskIDLE_PRIORITY+2,&hand2);
	xTaskCreate(task3,"Task3",128*4,NULL,tskIDLE_PRIORITY+2,NULL);
	vTaskStartScheduler();
}







