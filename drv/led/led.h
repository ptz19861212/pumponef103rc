/**
 * @file    led.h
 * @brief   灯
 * @author  ptz
 * @email   ptz19861212@163.com
 * @version 0.0.1
 * @date    2013-08-05 10:54:16 星期一
 * @history (1).2013-08-05 10:54:16 星期一 create
 */
/* Copyright (C)
 * 
 * My own license
 * All right reserved
 * 
 */

#ifndef __LED_H__
#define __LED_H__

#include "my_bsp.h"


/**
 * @brief   灯打开
 */
inline void LED_On(E_LedPin lPin);


/**
 * @brief   灯关闭
 */
inline void LED_Off(E_LedPin lPin);


/**
 * @brief   灯初始化
 */
inline void LED_Init(void);


#endif
