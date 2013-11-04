/**
 * @file    buzzer.c
 * @brief   蜂鸣器
 * @author  ptz
 * @email   ptz19861212@163.com
 * @version 0.0.1
 * @date    2013-08-05 10:27:56 星期一 
 * @history (1).2013-08-05 10:27:56 星期一 create
 */
/* Copyright (C)
 * 
 * My own license
 * All right reserved
 * 
 */

#include "buzzer_in.h"

void BUZZER_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    RCC_APB2PeriphClockCmd(buzzer_rcc, ENABLE);

    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

    GPIO_InitStructure.GPIO_Pin   = buzzer_pin;
    GPIO_Init(buzzer_gpio, &GPIO_InitStructure);
}

inline void BUZZER_On(void)
{
    GPIO_SetBits(buzzer_gpio, buzzer_pin);
}

inline void BUZZER_Off(void)
{
    GPIO_ResetBits(buzzer_gpio, buzzer_pin);
}
