#include "stm32f10x.h"    
#include "freertos.h"
#include "task.h"
#include "queue.h"
#include "UART1.h"
#include "Delay.h"
#include "ADC.h"


int main(void){
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
	USART1_Init();
	Delay_Init();

	
	AD_Init();
	
	

	
	
	while(1){
		
			uint16_t ret = AD_GetValue(ADC_Channel_1);
			printf1("ret1: %d \r\n", ret);
	
			ret = AD_GetValue(ADC_Channel_4);
			printf1("ret4: %d \r\n", ret);
		
			Delay_ms(3000);
	}
	
	
}


