/**
 * @file    buzzer_in.h
 * @brief   蜂鸣器
 * @author  ptz
 * @email   ptz19861212@163.com
 * @version 0.0.1
 * @date    2013-08-05 10:33:32 星期一 
 * @history (1).2013-08-05 10:33:32 星期一 create
 */
/* Copyright (C)
 * 
 * My own license
 * All right reserved
 * 
 */

#ifndef __BUZZER_IN_H__
#define __BUZZER_IN_H__

#include "buzzer.h"
#include <stm32f10x_rcc.h>
#include <stm32f10x_gpio.h>

// buzzer define
#define BUZZER_RCC				\
					(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO)
#define BUZZER_GPIO                   GPIOB
#define BUZZER_PIN                    (GPIO_Pin_4)

#endif
