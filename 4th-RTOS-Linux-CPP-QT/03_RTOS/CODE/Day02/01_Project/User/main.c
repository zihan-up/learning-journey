#include "stm32f10x.h"      

int main(void){	
	
	// 控制PA1和PA2灯亮
	RCC->APB2ENR = 0x00000004; // 开启时钟 GPIOA
	GPIOA->CRL = 0x00000330; //
	
	// PA0
	//GPIOA->CRL = 0x00000003;
	GPIOA->ODR = 0x00000007;
	
	while(1){
	}
}
