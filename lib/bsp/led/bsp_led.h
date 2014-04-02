/**
 * @file    bsp_led.h
 * @brief   
 * @author  ptz
 * @email   ptz19861212@163.com
 * @version 0.0.1
 * @date    2014-01-17 09:44:28 星期五 
 * @history (1).2014-01-17 09:44:28 星期五 create
 */
/* Copyright (C)
 * 
 * My own license
 * All right reserved
 * 
 */

#ifndef __BSP_LED_H__
#define __BSP_LED_H__

#include "my_bsp.h"


/**
 * @brief   灯打开
 */
void LedOn(S_Led* lpLed);


/**
 * @brief   灯关闭
 */
void LedOff(S_Led* lpLed);


/**
 * @brief   灯倒计时
 */
void LedCountdown(void);


/**
 * @brief   灯初始化
 */
void LedInit(void);


#endif
