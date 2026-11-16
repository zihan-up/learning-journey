#include "stm32f10x.h"
#include "freertos.h"
#include "task.h"
#include "queue.h"
#include "UART1.h"
#include "Delay.h"
#include "ADC.h"
#include <string.h>


// addr: 页首地址
void erasePage(uint32_t addr) {
    FLASH_Unlock();					//解锁
    FLASH_ErasePage(addr);			//页擦除
    FLASH_Lock();					//加锁
}

// addr: 页首地址
// data: 存放在首地址的32位数据
void changeFlashFor32(uint32_t addr, uint32_t data) {
    FLASH_Unlock();							// 解锁
    FLASH_ProgramWord(addr, data);			// 32bits
    FLASH_Lock();							// 加锁
}

// addr: 页首地址
// data: 存放在首地址的16位数据
void changeFlashFor16(uint32_t addr, uint16_t data) {
    FLASH_Unlock();							// 解锁
    FLASH_ProgramHalfWord(addr, data);		// 16bits
    FLASH_Lock();							// 加锁
}

// 读取数据
void readFlash(uint32_t addr, char *buffer, int len) {
    for (int i = 0; i < len; i++) {
        buffer[i] = *(__IO uint8_t *)(addr + i);
    }
}

int main(void) {
    USART1_Init();

	
    int address = 0x0800F000; // 定义一个地址
    
		// 通过地址读取flash的值
		int status = *((__IO uint32_t *)(address));

	
		// 判断这个也的首地址, 读取的前4个字节 是不是   0xFFFFFFFF
	  // 是 -> 这个位置从来没有存储过内容
	  // 不是  -> 这个也存储的有内容 
    if (status != 0xFFFFFFFF) {
				char buffer[40] = {0};
        // 有内容
        int len = *((__IO uint32_t *)address );
        readFlash(address + 4, buffer, len);

        printf1("read: %d, %d, %s \r\n", status, len, buffer);
    } else {
				// Flash的这个第61个也无内容, 存入数据
			
				char buffer[40] = {0};
        char *str = "!snow=12345678!";
        strncpy(buffer, str, strlen(str));
				
				// 擦除页
        erasePage(address);
       
				// 写入长度:  
        changeFlashFor32(address, strlen(buffer));

        for (int i = 0; i < sizeof(buffer); i += 4) {
            changeFlashFor32(address + 4 + i, *(int *)(buffer + i));
        }

        printf1("write \r\n");
    }

    while (1);
}


