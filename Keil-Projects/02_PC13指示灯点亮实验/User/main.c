// 只要包含了stm32f10x.h，Lib目录下所有的头文件都已包含

// 1、开始GPIOC外设时钟
// 2、初始化外设
// 3、写代码实现功能
// PC13指示灯是开漏的接法，讲PC13设置为开漏输出
#include "stm32f10x.h"                  // Device header
#include "Delay.h"
int main(void) {
    // 1、开启GPIOC外设时钟，需要使用RCC外设来完成，所以开启GPIOC外设时钟的函数，肯定在RCC模块
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE); // 开启GPIOC外设的时钟
    /*
    	如果想要同时开启多个外设的时钟，可以这样写，以同时开始B和C的时钟：
    	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOB, ENABLE);

    */
    // 2、初始化GPIOC外设，需要使用GPIO外设的功能
    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_OD; // 设置为通用开漏输出模式
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_13; // 初始化13引脚
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz; // 设置引脚的输出速度
    GPIO_Init(GPIOC, &GPIO_InitStruct); // 初始化GPIOC外设
    // 3、控制PC13引脚输出低电平，点亮PC13
    // GPIO_WriteBit(GPIOC, GPIO_Pin_13, Bit_RESET);

    // 4、控制PC13引脚输出高阻态，熄灭PC13
    // GPIO_WriteBit(GPIOC, GPIO_Pin_13, Bit_SET);

    // 5、实现闪烁
    while (1) {
        GPIO_WriteBit(GPIOC, GPIO_Pin_13, Bit_RESET); // 点亮
        // 引入延时模块，基于系统滴答计时器
        Delay_Ms(300);
        GPIO_WriteBit(GPIOC, GPIO_Pin_13, Bit_SET); // 熄灭
        Delay_Ms(300);
    }
}

// todo:
// 整理SPL模板，加上delay模块
