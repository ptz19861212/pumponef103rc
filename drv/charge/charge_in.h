/**
 * @file    charge_in.h
 * @brief   充电
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

#ifndef __CHARGE_IN_H__
#define __CHARGE_IN_H__

#include "charge.h"
#include <stm32f10x_rcc.h>
#include <stm32f10x_gpio.h>

// 是否有控制充电电流的引脚
#define CONFIG_USING_CHARGE_PIN_500MA

// charge define
// 充电500ma
#ifdef CONFIG_USING_CHARGE_PIN_500MA
#define CHARGE_RCC						\
					(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO)
#define CHARGE_GPIO						GPIOA
#define CHARGE_PIN						(GPIO_Pin_15)
#endif

// 充电检测
#define CHARGE_IN_RCC						RCC_APB2Periph_GPIOA
#define CHARGE_IN_GPIO						GPIOA
#define CHARGE_IN_PIN						(GPIO_Pin_10)

#endif
