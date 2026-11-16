#include "stm32f10x.h"    
#include "freertos.h"
#include "task.h"
#include "UART1.h"

// 动态创建任务


//// void *p用来接收传参(  别人传给task1 )
//void task1(void *p) {
//	
////	int *num = (int *)p;
////	printf1("num: %d \r\n",  *num);
//	
//	while(1){
//		printf1("task1 \r\n");
//		// vTaskDelay()
//		
//		vTaskDelay(10);
//	}
//	// 任务的入口函数, 不允许走到结束, 也不允许在入口函数中return
//}

//void task2(void *p){
//	vTaskDelay(2);
//	while(1){
//		printf1("task2 \r\n");
//		vTaskDelay(10);// 除了延时以外, 让任务陷入阻塞
//	}
//}

//int num = 10;
//int main(void){
//	USART1_Init();
//	
//	//                          128
//	BaseType_t  ret = xTaskCreate(task1,"Task1",128,(void *)&num,tskIDLE_PRIORITY+1,NULL);
//	if(ret == pdPASS){
//		// 成功
//	}else{
//		// 失败
//	}
//	
//	
//	xTaskCreate(task2,"Task2",128,(void *)&num,tskIDLE_PRIORITY+2,NULL);
//	// 
//	// xTaskCreate(task1,"Task1",configMINIMAL_STACK_SIZE,NULL,tskIDLE_PRIORITY+1,NULL);
//	
//	vTaskStartScheduler();// 调度器

//	
//}



// -------------------------------------------------------------

TaskHandle_t hand1, hand2;

void task1(void *p) {
	
	while(1){
		//printf1("task1 \r\n");
		vTaskDelay(10);
	}
}

void task2(void *p){
	
	vTaskDelay(2);
	while(1){
		//printf1("task2 \r\n");
		vTaskDelay(10);
	}
}

int main(void){
	USART1_Init();

	xTaskCreate(task1,"Task1",128,NULL,tskIDLE_PRIORITY+1,&hand1);
	xTaskCreate(task2,"Task2",128,NULL,tskIDLE_PRIORITY+1,&hand2);

	// 回调机制: (给"回调函数")
	//      一个函数在某些情况下已经被注册, 但是在注册之后不会立即执行
	//      而是在未来某个事件, 满足了执行条件, 回来调用这个函数
	//      这种机制我们称之为回调机制
	
	vTaskStartScheduler();// 调度器函数, FreeRTOS中调度器函数, 是开启任务调度的开关
	                      //     在调度器函数执行的时候, 会自动创建一个空闲任务
	
	// 注意: 开启了调度器之后, 在主栈中的调度器函数之后的代码不会执行了
	//        下面不用再写代码了

	
	int num = 10;
	printf1("num: %d \r\n", num);
	
	
	while(1){
	}
}
