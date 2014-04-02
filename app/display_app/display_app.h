/**
 * @file    display_app.h
 * @brief   
 * @author  ptz
 * @email   ptz19861212@163.com
 * @version 0.0.1
 * @date    2014-01-06 17:08:33 星期一 
 * @history (1).2014-01-06 17:08:33 星期一 create
 */
/* Copyright (C)
 * 
 * My own license
 * All right reserved
 * 
 */


#ifndef __DISPLAY_APP_H__
#define __DISPLAY_APP_H__

#include <stdint.h>

/**
 * @brief   显示风扇
 *
 * @param   lpPoint
 */
void Lcd__FanDisp(void);


/**
 * @brief   清除风扇
 */
void Lcd__FanClr(void);


/**
 * @brief   显示充电状态
 */
void Lcd__ChargeDisp(void);


/**
 * @brief   清除充电状态
 */
void Lcd__ChargeClr(void);


/**
 * @brief   显示大号充电状态
 */
void Lcd__ChargeLargeDisp(void);


/**
 * @brief   显示大号充满状态
 */
void Lcd__ChargeFullLargeDisp(void);


/**
 * @brief   显示电池状态
 *
 * @param   lValue
 */
void Lcd__BatDisp(uint8_t lValue);



#endif
