#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
/*
	基于已实现的OLED模块，测试OLED的使用
*/

int main(void) {
	// 初始化
	OLED_Init();
	OLED_ShowChar(1,1,'A');
	OLED_ShowString(2,1,"Hello World!");
	OLED_ShowString(3,1,"666666");
	while(1){
	
	}
}

