/**
 * @file    led_in.h
 * @brief   灯
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

#ifndef __LED_IN_H__
#define __LED_IN_H__

#include "led.h"
#include <stm32f10x_rcc.h>
#include <stm32f10x_gpio.h>

// led define
#define LED_RCC						RCC_APB2Periph_GPIOA
#define LED_GPIO						GPIOA
#define LED_PIN						(GPIO_Pin_1)

#endif
