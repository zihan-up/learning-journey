// UART1.h
#ifndef __UART1_H__
#define __UART1_H__

#include "stm32f10x.h" 
#include <stdio.h>
#include <stdarg.h>
#include <string.h>

// extern char buf[100] ;

void USART1_Init(void);
void USART1_SendByte(uint8_t Byte);
void printf1(char *format, ...);

#endif
