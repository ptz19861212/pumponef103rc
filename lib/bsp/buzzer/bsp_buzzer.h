/**
 * @file    bsp_buzzer.h
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

#ifndef __BSP_BUZZER_H__
#define __BSP_BUZZER_H__

#include "my_bsp.h"


/**
 * @brief   蜂鸣器打开
 */
void BuzzerOn(S_Buzzer* lpBz);


/**
 * @brief   蜂鸣器关闭
 */
void BuzzerOff(S_Buzzer* lpBz);


/**
 * @brief   蜂鸣器倒计时
 */
void BuzzerCountdown(void);


/**
 * @brief   蜂鸣器初始化
 */
void BuzzerInit(void);


#endif
