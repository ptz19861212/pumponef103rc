/**
 * @file    source_in.h
 * @brief   电源
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

#ifndef __SOURCE_IN_H__
#define __SOURCE_IN_H__

#include "source.h"
#include <stm32f10x_rcc.h>
#include <stm32f10x_gpio.h>

// source define
#define SOURCE_RCC						RCC_APB2Periph_GPIOC
#define SOURCE_GPIO						GPIOC
#define SOURCE_PIN						(GPIO_Pin_3)

#endif
