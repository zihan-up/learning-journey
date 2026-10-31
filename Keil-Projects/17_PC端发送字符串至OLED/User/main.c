#include <stdio.h>
#include "stm32f10x.h"
#include "Delay.h"
#include "OLED.h"
/**
	1、PC端使用串口发送字符串，以'\n'结尾表示发送完毕。
	2、STM32通过串口接收这个字符串，并将这个字符串显示在OLED显示屏上。
**/
#define BUFFER_SIZE 10
// 此枚举类型表示下面函数构建字符串是否完成
typedef enum {
    FINISHED, // 字符串构建完成
    UNFINISHED
} BuildStrStatus;


// 初始化USART1外设
void USART1_Init(void);

// 单片机接收PC端发来的一个字节的数据
uint8_t USART1_ReceiveByte(void);

void OLED_UpdateDisplay(char *Str);

// 将USART1外设接收到的字符，转换成字符串
BuildStrStatus USART1_ReceiveChar2Str(char *Buffer);

int main(void) {
    USART1_Init(); // 初始化USART1外设
    OLED_Init(); // 初始化OLED显示屏
    OLED_Clear();

    // 首先在OLED屏幕上展示一个标题:
    // OLED_ShowString(1, 1, "Waiting String:");

    char Buffer[BUFFER_SIZE];

    while (1) {
        // 轮询单片机是否完成字符串的构建，如果完成构建，就再OLED上显示此字符串
        if (USART1_ReceiveChar2Str(Buffer) == FINISHED){

            // 这里写在OLED上显示字符串的逻辑
            // OLED_UpdateDisplay(Buffer);
			 OLED_Clear();
			 OLED_ShowString(1, 1, Buffer);
			
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
    return (uint8_t)USART_ReceiveData(USART1);
}

// 将USART1外设接收到的字符，转换成字符串
BuildStrStatus USART1_ReceiveChar2Str(char *Buffer) {
    // 接收PC端发送的一个字符
    char ReceiveChar = (char)USART1_ReceiveByte();

    // 设置一个静态局部变量下标，用于表示下一个接收到的字符应该存储的位置
    static uint8_t Index = 0;

    // 如果已经存满了(必须留一个位置给字符串的空字符)
    if (Index == BUFFER_SIZE - 1) {
        // 把最后一个位置给空字符
        Buffer[Index] = 0;
        // main函数会一直执行此函数，此时字符串已经构建完成，所以需要把index归零
        Index = 0;
        return FINISHED;
    } else { // 如果此时还没满
        // 如果是换行符\n，表示字符串结束
        if (ReceiveChar == '\n') {
            Buffer[Index] = 0;
            Index = 0;
            return FINISHED;
        } else { // 如果接收到的是正常字符
            Buffer[Index] = ReceiveChar;
            Index++;
            return UNFINISHED;
        }
    }



}


void OLED_UpdateDisplay(char *Str) {
    // 当前显示数据的行，从第 2 行开始（第 1 行是标题）
    static uint8_t CurrentLine = 2;

    // 如果到达 OLED 第 5 行（超出 4 行），重新回到第 2 行
    if (CurrentLine > 4) {
        // 先清屏再打印标题
        OLED_Clear();
        OLED_ShowString(1, 1, "Waiting String:");
        CurrentLine = 2;
    }

    OLED_ShowString(CurrentLine, 1, Str);
    // 切换到下一行
    CurrentLine++;
}
