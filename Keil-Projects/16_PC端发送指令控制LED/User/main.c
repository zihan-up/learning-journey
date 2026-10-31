#include <stdio.h>
#include "stm32f10x.h"
#include "Delay.h"
#include "OLED.h"


// 初始化PC13状态指示灯
void PC13_Init(void);
// 初始化USART1外设
void USART1_Init(void);

// 单片机接收PC端发来的一个字节的数据
uint8_t USART1_ReceiveByte(void);

// 单片机发送一个字节的数据到PC
void USART1_SendByte(uint8_t data);
// 重写fputc函数，目的是为了修改stdout的输出位置到USART1
int fputc(int ch, FILE *f) {
    USART1_SendByte((uint8_t)ch);   // 通过 USART1 发送字符到 PC 端
    return ch;      // 返回发送的字符
}

int main(void) {
    PC13_Init();
    USART1_Init();
    GPIO_SetBits(GPIOC, GPIO_Pin_13); // PC13初始化位灭的
    OLED_Init(); // 初始化OLED显示屏

    while (1) {
        uint8_t Receive_cmd = USART1_ReceiveByte();

        switch (Receive_cmd) {
        case '0':
            GPIO_SetBits(GPIOC, GPIO_Pin_13);
            OLED_Clear();
            OLED_ShowString(1, 1, "PC13 LED OFF");
            break;

        case '1':
            GPIO_ResetBits(GPIOC, GPIO_Pin_13); 
            OLED_Clear();
            OLED_ShowString(1, 1, "PC13 LED ON");

            break;

        default:
            OLED_ShowString(1, 1, "Invalid input!");
            break;
        }
    }
}


// 初始化USART1外设
void USART1_Init() {
    //1、开启时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_USART1, ENABLE);

    //2、初始化PA9和PA10引脚
    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP; // PA9TX输出引脚，设计为复用推挽输出模式
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_9;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_Init(GPIOA, &GPIO_InitStruct);
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING; // PA10输入引脚，设计为浮空输入模式
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_10;
    GPIO_Init(GPIOA, &GPIO_InitStruct);

    //3、初始化USART1外设
    USART_InitTypeDef USART_InitStruct;
    USART_InitStruct.USART_BaudRate = 115200;
    USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStruct.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    USART_InitStruct.USART_Parity = USART_Parity_No;
    USART_InitStruct.USART_StopBits = USART_StopBits_1;
    USART_InitStruct.USART_WordLength = USART_WordLength_8b;
    USART_Init(USART1, &USART_InitStruct);
    //4、使能USART1外设
    USART_Cmd(USART1, ENABLE);
}

// 单片机接收PC端发来的一个字节的数据
uint8_t USART1_ReceiveByte(void) {
    // 接收数据前，首先要判断接收数据寄存器是否非空
    while (USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == RESET);

    // 接收数据寄存器非空，接收数据并返回
    // 记得强转格式，保持统一
    return (uint8_t)USART_ReceiveData(USART1);
}

// 初始化PC13状态指示灯
void PC13_Init(void) {
    //1、开启时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);

    //2、初始化PC13
    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_OD; // PC13指示灯本身是开漏接法，优先使用开漏输出模式
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_13;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_Init(GPIOC, &GPIO_InitStruct);
}

// 单片机发送一个字节的数据到PC
void USART1_SendByte(uint8_t data) { // uint8_t就是unsigned char

    // 1、想要发送数据，首先要确认发送数据寄存器为空
    while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);

    // 2、发送数据
    USART_SendData(USART1, data);
}


