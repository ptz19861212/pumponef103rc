/**
 * @file    vibration_in.h
 * @brief   振动泵
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

#ifndef __VIBRATION_IN_H__
#define __VIBRATION_IN_H__

#include "vibration.h"
#include <stm32f10x_rcc.h>
#include <stm32f10x_gpio.h>

// vibration define
#define VIBRATION_RCC						RCC_APB2Periph_GPIOA
#define VIBRATION_GPIO						GPIOA
#define VIBRATION_PIN						(GPIO_Pin_8)

#endif
