#include <stdio.h>
#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"

// 复习：sizeof(arr)这里是求整个数组的大小，sizeof((arr)[0])是求一个数组元素的大小，单位是字节Byte；
// 所以相除之后就可以得到这个数组的元素数量
#define ARRAY_LEN(arr) (sizeof(arr) / sizeof((arr)[0]))

// 初始化USART1外设
void USART1_Init(void);

// 单片机发送一个字节的数据到PC
void USART1_SendByte(uint8_t data);

// 单片机发送字节数组到PC
void USART1_SendBytes(const uint8_t *Bytes, uint16_t Length);

// 单片机发送字符串到PC
void USART1_SendString(const char *Str);

// 单片机发送无符号整数到PC,方法1将数字转换成字符串，调用发送字符串的函数
void USART1_SendUIntStr(uint32_t Num);

// 通过 USART1 发送 32 位无符号整数二进制位（以小端序发送）到PC
void USART1_SendUInt(uint32_t Num);


// 写了printf函数后，会将数据先存到stdout标准输出缓冲区，stdout输出到屏幕上，靠的是fputc函数（逐字符发送）；
// 重写fputc函数，目的是为了修改stdout的输出位置到USART1
int fputc(int ch, FILE *f) {
    USART1_SendByte((uint8_t)ch);   // 通过 USART1 发送字符到 PC 端
    return ch;      // 返回发送的字符
}

int main(void) {
	USART1_Init();
	
//	uint8_t Bytes[] = {1,2,3,4,5}; // 声明一个数组
//	uint16_t BytesLength = ARRAY_LEN(Bytes);
    while (1) {
//		// 复习：这里传入数组，传入的数组会退化成指针，等价于&Bytes[0]；但是这样就丢失了长度信息，所以需要补充一个长度的参数
//		USART1_SendBytes(Bytes, BytesLength);
//		Delay_S(2);
		
//		USART1_SendString("Hello STM32!\n");
//		Delay_S(2);
		
//		uint32_t Num = 114514;
//		USART1_SendUIntStr(Num);
//		Delay_S(2);
		
//		uint32_t Num = 114514;
//		USART1_SendUInt(Num);
//        Delay_S(2);  // 延时 2 秒，避免发送过快
		
		printf("Hello STM32!\n");
		
        Delay_S(2);  // 延时 2 秒，避免发送过快
    }
}


// 初始化USART1外设
void USART1_Init(){
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


// 单片机发送一个字节的数据到PC
void USART1_SendByte(uint8_t data){ // uint8_t就是unsigned char
	
	// 1、想要发送数据，首先要确认发送数据寄存器为空
	while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
	// 2、发送数据
	USART_SendData(USART1, data);
}


// 单片机发送字节数组到PC
void USART1_SendBytes(const uint8_t *Bytes, uint16_t Length){
	for(uint16_t i = 0;i < Length; i++){
		USART1_SendByte(Bytes[i]); // Bytes[i] 等价于 *(Bytes + i)，先算地址，再解引用
	}
	// 等待数据全部发送完毕
	while(USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);
}

// 单片机发送字符串到PC
void USART1_SendString(const char *Str){
	
	while(*Str){
		USART1_SendByte((uint8_t)*Str);
		Str++;
	}
	// 等待全部数据发送完毕
	while(USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);
}

// 单片机发送无符号整数到PC,方法1将数字转换成字符串，调用发送字符串的函数
void USART1_SendUIntStr(uint32_t Num){
	char Buffer[11]; // 足够容纳 10 位数字 + 终止符
	sprintf(Buffer, "%u", Num);
	USART1_SendString(Buffer);
}
// 通过 USART1 发送 32 位无符号整数二进制位（以小端序发送）到PC
void USART1_SendUInt(uint32_t Num) {
    uint8_t Buffer[4];  // 用于存储 32 位整数拆分后的 4 个字节

    // 逐字节提取 32 位整数的各个字节（按照小端序存储）
    Buffer[0] = (uint8_t)(Num & 0xFF);         // 提取num最后一个字节数据作为最先发送的字节
    Buffer[1] = (uint8_t)((Num >> 8) & 0xFF);  // 提取num倒数第二个字节数据作为其次发送的字节
    Buffer[2] = (uint8_t)((Num >> 16) & 0xFF); // 提取num倒数第三个字节数据作为第三次发送的字节
    Buffer[3] = (uint8_t)((Num >> 24) & 0xFF); // 提取num第一个字节数据作为最后发送的字节

    // 通过串口发送这 4 个字节
    USART1_SendBytes(Buffer, 4);
}

