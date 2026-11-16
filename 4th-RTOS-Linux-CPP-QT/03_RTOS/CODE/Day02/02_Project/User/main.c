#include "stm32f10x.h"      

int main(void){	
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	GPIO_InitTypeDef initType;
	initType.GPIO_Pin =  GPIO_Pin_2;
	initType.GPIO_Mode = GPIO_Mode_Out_PP;
	initType.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &initType);
	while(1){
			GPIO_SetBits(GPIOA, GPIO_Pin_2);
			
		int num=10000000;
		while(num>0){
			num--;
		}
		
			GPIO_ResetBits(GPIOA, GPIO_Pin_2);
		
					
		num=10000000;
		while(num>0){
			num--;
		}
		
	}
	
}
