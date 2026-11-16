#include "stm32f10x.h"    
#include "freertos.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
#include "event_groups.h"
#include "UART1.h"
#include "Delay.h"


// ---------------------take give模式: 只表示有事情发生, 通知给某个任务---------------------
// ---------------------任务1向任务2发送一个通知--------------------

//TaskHandle_t hand1, hand2;
//void task1(void *p) {
//	
//	vTaskDelay(10000);
//	
//	// 向另一个任务发送任务通知
//	// 参数:  任务的句柄
//	// 返回值: pdPASS表示发送任务成功
//	BaseType_t ret = xTaskNotifyGive(hand2);
//	BaseType_t ret2 = xTaskNotifyGive(hand2);
//	
//	// 通知是可以累积的: 本质数组值++
//	
//	while(1){
//	}
//}
//void task2(void *p) {
//	
//	vTaskDelay(11000);
//	printf1("29\r\n");
//	// 读取自己的任务有没有被通知
//	// 参数1:  要不要清除别人给我发送的通知pdTRUE(所有多次通知都清除)
//	// 参数2:  超时时间
//	// 返回值: 计数,  超时返回0
//	ulTaskNotifyTake(pdFAIL, portMAX_DELAY);
//	printf1("36\r\n");
//	ulTaskNotifyTake(pdFAIL, portMAX_DELAY);
//	printf1("38\r\n");
//	

//	while(1){
//	}
//}

//int main(void){
//	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
//	USART1_Init();
//	Delay_Init();

//	
//	xTaskCreate(task1,"Task1",128*4,NULL,tskIDLE_PRIORITY+2,&hand1);
//	xTaskCreate(task2,"Task2",128*4,NULL,tskIDLE_PRIORITY+2,&hand2);
//	vTaskStartScheduler();
//}

// ---------------------传值模式: 通知给这个任务一个具体的数值(int)---------------------


TaskHandle_t hand1, hand2;
void task1(void *p) {
	
	vTaskDelay(10000);
	
	// 向另一个任务发送任务通知: 传一个具体的值过去
	// 参数1: 传给那个任务
	// 参数2: 要传递的值是什么
	// 参数3: 如果目标任务, 本身就有一个通知存在, 怎么处理新的通知
	//           eg: eSetValueWithOverwrite -> 覆盖旧值
	// 返回值: pdPASS表示发送任务成功
	BaseType_t ret = xTaskNotify(hand2, 13, eSetValueWithOverwrite );

	
	while(1){
	}
}
void task2(void *p) {
	
	// vTaskDelay(11000);
	printf1("29\r\n");
 
	// 接收被通知的数据
  uint32_t num = 0;
	// xTaskNotifyWait( 0xffffffff,  0xffffffff, &num,  portMAX_DELAY );
	
	xTaskNotifyWait( 0xffffffff,  0xffffffff, &num,  portMAX_DELAY );
	printf1("num1: %d \r\n", num);
	
//	num = 0;
//	xTaskNotifyWait( 0xffffffff,  0xffffffff, &num,  1000 );
//	printf1("num2: %d \r\n", num);
//	
	
	
//	// 等待通知, 如果通知到来, 则获取通知值; 可在进入和退出时清除指定的位
//	BaseType_t xTaskNotifyWait(
//	uint32_t ulBitsToClearOnEntry,  // 进入函数时清除的位
//	uint32_t ulBitsToClearOnExit,   // 退出函数时清除的位
//	uint32_t *pulNotificationValue, // 存储通知值
//	TickType_t xTicksToWait         // 超时时间
//	);
//	// 返回值:pdPASS收到通知, pdFAIL表示超时
	
	printf1("38\r\n");
	

	while(1){
	}
}

int main(void){
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
	USART1_Init();
	Delay_Init();

	
	xTaskCreate(task1,"Task1",128*4,NULL,tskIDLE_PRIORITY+2,&hand1);
	xTaskCreate(task2,"Task2",128*4,NULL,tskIDLE_PRIORITY+2,&hand2);
	vTaskStartScheduler();
}




