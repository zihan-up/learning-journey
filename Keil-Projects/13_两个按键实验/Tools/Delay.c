#include "Delay.h"

/**
  * @brief  提供微秒级延时
  * @param  us 延时时长（单位：微秒）
  *         当系统时钟为 72 MHz 且 CLKSOURCE = 1（SysTick 时钟 = HCLK）时
  *         建议取值范围：0 ~ 233016 us
  * @retval 无
  * @note   最大值为什么是 233016？
  *         1) SysTick 是 24 位递减计数器
  *            LOAD 寄存器只有 24 位有效位
  *            所以最大可装载值为：
  *            LOAD_max = 0xFFFFFF = 16777215
  *
  *         2) 本函数设置 CLKSOURCE = 1
  *            SysTick 时钟频率 = HCLK = 72000000 Hz
  *            也就是每秒递减 72000000 次
  *
  *         3) 计数器从 LOAD 递减到 0 一共经历 (LOAD + 1) 次时钟
  *            最大一次能经历的计数次数：
  *            N_max = LOAD_max + 1 = 16777216 次
  *
  *         4) 最大延时时间：
  *            T_max = N_max / 72,000,000
  *                 = 16777216 / 72000000 秒
  *                 ≈ 0.233016888... 秒
  *                 ≈ 233016.888... 微秒
  *
  *         5) 为了不超出 24 位装载能力，us 取整后可取：
  *            us_max = 233016
  */
void Delay_Us(uint32_t us) {
    if (us == 0) {
        return;
    }

    if (us > 233016) {
        return;     // 超出 24 位计数器计数能力
    }

    /* 重装值 LOAD = N - 1 */
    SysTick->LOAD = 72U * us - 1U;

    /* 清空当前计数值，同时清除 COUNTFLAG */
    SysTick->VAL = 0U;

    /*
    	CTRL寄存器：
        bit0 ENABLE = 1 (开启计时)
        bit1 TICKINT = 0 (禁用中断)
        bit2 CLKSOURCE = 1 (选中HCLK)
    */
    SysTick->CTRL = (1U << 0) | (1U << 2);


    /* 等待 COUNTFLAG 置位（bit16） */
    while ((SysTick->CTRL & (1U << 16)) == 0);

    /* 单次延时完成，关闭 SysTick bit0 ENABLE = 0 */
    SysTick->CTRL &= ~(1U << 0);
}

/**
  * @brief  提供毫秒级延时
  * @param  ms 延时时长（单位：毫秒）
  *         取值范围受 uint32_t 类型限制：
  *         0 ~ 4294967295
  *
  *         理论最大延时 ≈ 49.7 天
  * @retval 无
  */
void Delay_Ms(uint32_t ms) {
    while (ms--) {
        Delay_Us(1000);
    }
}

/**
  * @brief  提供秒级延时
  * @param  s 延时时长，范围：0~4294967295
  * @retval 无
  */
void Delay_S(uint32_t s) {
    while (s--) {
        Delay_Ms(1000);
    }
}
