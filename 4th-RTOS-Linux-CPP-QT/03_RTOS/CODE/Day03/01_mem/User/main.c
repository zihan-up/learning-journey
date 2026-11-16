#include "stm32f10x.h"      

#include "FreeRTOS.h"
#include "task.h"



void b(){
	int nums[20] = {0};
}
void a(){
	int nums[10] = {0};
	b();
	nums[0] = 1;
}
int main(void){	// MSP:  主栈指针
	a();
}

