/**
 * @file    bsp_charge.h
 * @brief   
 * @author  ptz
 * @email   ptz19861212@163.com
 * @version 0.0.1
 * @date    2014-01-23 15:25:09 星期四 
 * @history (1).2014-01-23 15:25:09 星期四 create
 */
/* Copyright (C)
 * 
 * My own license
 * All right reserved
 * 
 */

#ifndef __BSP_CHARGE_H__
#define __BSP_CHARGE_H__

#include "my_define.h"

/**
 * @brief   充电打开
 */
void ChargeOn(void);


/**
 * @brief   充电关闭
 */
void ChargeOff(void);


/**
 * @brief   充电检测
 */
E_TrueState ChargeScan(void);


/**
 * @brief   充电初始化
 */
void ChargeInit(void);



#endif
