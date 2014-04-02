/**
 * @file    bsp_vibration.h
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

#ifndef __BSP_VIBRATION_H__
#define __BSP_VIBRATION_H__

#include "my_bsp.h"


/**
 * @brief   振动泵打开
 */
void VibrationOn(S_Vibration* lpVbr);


/**
 * @brief   振动泵关闭
 */
void VibrationOff(S_Vibration* lpVbr);


/**
 * @brief   振动泵倒计时
 */
void VibrationCountdown(void);


/**
 * @brief   振动泵初始化
 */
void VibrationInit(void);


#endif
