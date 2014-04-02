/**
 * @file    pump_in.h
 * @brief   泵
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

#ifndef __PUMP_IN_H__
#define __PUMP_IN_H__

#include "pump.h"
#include <stm32f10x_rcc.h>
#include <stm32f10x_gpio.h>

// 有没有控制泵的IO
#define CONFIG_USING_PUMP_PIN

// pump define
#ifdef CONFIG_USING_PUMP_PIN
#define PUMP_RCC						RCC_APB2Periph_GPIOB
#define PUMP_GPIO						GPIOB
#define PUMP_PIN						(GPIO_Pin_9)
#endif

#endif
