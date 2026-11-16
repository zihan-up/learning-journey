#include "stm32f10x.h"    
#include "freertos.h"
#include "task.h"
#include "UART1.h"


// ---------------------vTaskList: 获取所有任务信息---------------------------
//   void vTaskList( char * pcWriteBuffer );


//TaskHandle_t hand1, hand2;

//void task1(void *p) {
//	while(1){
//		vTaskDelay(1000);
//		
//		char buf[160] = {0};// eg: 3个任务,  
//		vTaskList(buf);
//		
//		printf1("buf: \r\n%s \r\n", buf);
//		
//	}
//}
//void task2(void *p){
//	vTaskDelay(2);
//	while(1){
//		vTaskDelay(10);
//	}
//}
//void task3(void *p){
//	vTaskDelay(2);
//	while(1){
//		vTaskDelay(10);
//	}
//}
//int main(void){
//	USART1_Init();
//	
//	xTaskCreate(task1,"Task1",128*4,NULL,tskIDLE_PRIORITY+1,&hand1);
//	xTaskCreate(task2,"Task2",128,NULL,tskIDLE_PRIORITY+1,&hand2);
//	xTaskCreate(task3,"Task3",128,NULL,tskIDLE_PRIORITY+1,&hand2);
//	
//	vTaskStartScheduler();

//}



// ---------------uxTaskGetSystemState:追踪当前系统所有的任务信息--------------------------
//UBaseType_t uxTaskGetSystemState(
//    TaskStatus_t * const pxTaskStatusArray,// 任务状态数组,每个下标位存储一个任务信息
//    const UBaseType_t uxArraySize,// 数组长度/大小 
//    uint32_t * const pulTotalRunTime// 系统运行总时间, NULL代表不需要
//);
//// 返回值: 标识当前任务的总数(pxTaskStatusArray数组中有效任务的数量)


//TaskHandle_t hand1, hand2;

//void task1(void *p) {
//	while(1){
//		vTaskDelay(1000);
//		
//		TaskStatus_t list[3];
//		uxTaskGetSystemState(list, 3, NULL);
//		
//		for(int i=0; i<3; i++){
//			TaskStatus_t  xTaskDetails = list[i];
//			printf1("Task Name: %s \r\n", xTaskDetails.pcTaskName);
//			printf1("Task Priority: %d \r\n", xTaskDetails.uxCurrentPriority);
//			printf1("Base Priority: %d \r\n", xTaskDetails.uxBasePriority);
//			printf1("Task State: %d  \r\n", xTaskDetails.eCurrentState);
//			printf1("Stack Base Address: %p  \r\n", xTaskDetails.pxStackBase);
//			printf1("Stack High Water Mark: %d  \r\n", xTaskDetails.usStackHighWaterMark);
//			printf1("Task Run Time: %d ticks \r\n", xTaskDetails.ulRunTimeCounter);
//		}
//	}
//}
//void task2(void *p){
//	vTaskDelay(2);
//	while(1){
//		vTaskDelay(10);
//	}
//}
//int main(void){
//	USART1_Init();
//	
//	xTaskCreate(task1,"Task1",128*4,NULL,tskIDLE_PRIORITY+1,&hand1);
//	xTaskCreate(task2,"Task2",128,NULL,tskIDLE_PRIORITY+1,&hand2);
//	
//	vTaskStartScheduler();

//}


// ------------uxTaskGetNumberOfTasks: 获取当前系统中有几个任务-------------------
// UBaseType_t uxTaskGetNumberOfTasks( void );

//TaskHandle_t hand1, hand2;

//void task1(void *p) {
//	while(1){
//		vTaskDelay(1000);
//		 
//		
//		UBaseType_t  ret = uxTaskGetNumberOfTasks();
//		printf1("num: %d \r\n", ret);

//	}
//}
//void task2(void *p){
//	vTaskDelay(2);
//	while(1){
//		vTaskDelay(10);
//	}
//}
//int main(void){
//	USART1_Init();
//	
//	xTaskCreate(task1,"Task1",128*4,NULL,tskIDLE_PRIORITY+1,&hand1);
//	xTaskCreate(task2,"Task2",128,NULL,tskIDLE_PRIORITY+1,&hand2);
//	
//	vTaskStartScheduler();

//}



// ---------pcTaskGetName:通过任务句柄获取任务名----------------------
//char * pcTaskGetName(
//		TaskHandle_t xTaskToQuery // 任务句柄, NULL表示获取当前任务
//)

//TaskHandle_t hand1, hand2;

//void task1(void *p) {
//	while(1){
//		vTaskDelay(1000);
//		
//		char * name = pcTaskGetName(hand1);
//		printf1("name: %s \r\n", name);

//	}
//}
//void task2(void *p){
//	vTaskDelay(2);
//	while(1){
//		vTaskDelay(10);
//	}
//}
//int main(void){
//	USART1_Init();
//	
//	xTaskCreate(task1,"zs",128*4,NULL,tskIDLE_PRIORITY+1,&hand1);
//	xTaskCreate(task2,"Task2",128,NULL,tskIDLE_PRIORITY+1,&hand2);
//	
//	vTaskStartScheduler();

//}


// ------------uxTaskPriorityGet: 获取任务的优先级--------
//UBaseType_t uxTaskPriorityGet(
//		TaskHandle_t xTask // 任务句柄, NULL表示当前任务
//);
//TaskHandle_t hand1, hand2;

//void task1(void *p) {
//	while(1){
//		vTaskDelay(1000);
//		
//		UBaseType_t  ret = uxTaskPriorityGet(hand1);
//		printf1("ret: %d \r\n", ret);

//	}
//}
//void task2(void *p){
//	vTaskDelay(2);
//	while(1){
//		vTaskDelay(10);
//	}
//}
//int main(void){
//	USART1_Init();
//	
//	xTaskCreate(task1,"zs",128*4,NULL,tskIDLE_PRIORITY+1,&hand1);
//	xTaskCreate(task2,"Task2",128,NULL,tskIDLE_PRIORITY+1,&hand2);
//	
//	vTaskStartScheduler();

//}


// ----------xTaskGetHandle: 根据任务名获取任务句柄----------------
//TaskHandle_t xTaskGetHandle(
//		const char *pcName // 任务名
//);


//TaskHandle_t hand1, hand2;

//void task1(void *p) {
//	while(1){
//		vTaskDelay(1000);
//		
//		TaskHandle_t hand = xTaskGetHandle("Task2");
//		UBaseType_t  ret = uxTaskPriorityGet(hand);
//		printf1("ret: --%d-- \r\n", ret);
//		
//	}
//}
//void task2(void *p){
//	vTaskDelay(2);
//	while(1){
//		vTaskDelay(10);
//	}
//}
//int main(void){
//	USART1_Init();
//	
//	xTaskCreate(task1,"Task1",128*4,NULL,tskIDLE_PRIORITY+1,&hand1);
//	xTaskCreate(task2,"Task2",128,NULL,tskIDLE_PRIORITY+1,&hand2);
//	
//	vTaskStartScheduler();

//}


// --------------eTaskGetState:根据任务句柄获取任务状态----------------
//eTaskState eTaskGetState( 
//		TaskHandle_t xTask // 任务句柄
//)

TaskHandle_t hand1, hand2;

void task1(void *p) {
	while(1){
		vTaskDelay(1000);
		
		eTaskState  ret = eTaskGetState(hand2);
		printf1("ret: --%d-- \r\n", ret);
		
	}
}
void task2(void *p){
	vTaskDelay(2);
	while(1){
		vTaskDelay(10);
	}
}
int main(void){
	USART1_Init();
	
	xTaskCreate(task1,"Task1",128*4,NULL,tskIDLE_PRIORITY+1,&hand1);
	xTaskCreate(task2,"Task2",128,NULL,tskIDLE_PRIORITY+1,&hand2);
	
	vTaskStartScheduler();

}



