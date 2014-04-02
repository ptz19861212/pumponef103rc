/**
 * @file    tim_general_in.h
 * @brief   
 * @author  ptz
 * @email   ptz19861212@163.com
 * @version 0.0.1
 * @date    2013-11-28 10:36:35 星期四 
 * @history (1).2013-11-28 10:36:35 星期四 create
 */
/* Copyright (C)
 * 
 * My own license
 * All right reserved
 * 
 */

#ifndef __TIM_GENERAL_IN_H__
#define __TIM_GENERAL_IN_H__

#include "stm32f10x_rcc.h"
#include "config_bsp.h"
#include "tim_general.h"
#include "state.h"

// time2 clk div   tim2 = x * APB1
#define CONFIG_TIM2_CLK					TIM_CKD_DIV1

// time2 prescale  tim2 = pre + 1, so pre = tim2 - 1
#define CONFIG_TIM2_PRESCALE			35

// time2 period  2000000/128 = 15625
#define CONFIG_TIM2_PERIOD				15625

// time2 pwm pluse pulse = period / 2
#define CONFIG_TIM2_PULSE				7812

// time3 clk div   tim3 = x * APB1
#define CONFIG_TIM3_CLK					TIM_CKD_DIV1

// time3 prescale  tim3 = pre + 1, so pre = tim3 - 1
#define CONFIG_TIM3_PRESCALE			7199

// time3 period  10000/50 = 200
#define CONFIG_TIM3_PERIOD				200

// time3 pwm pluse pulse = period / 2
//#define CONFIG_TIM3_PULSE				7812

#endif
