/**
 * @file    charge.h
 * @brief   充电
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

#ifndef __CHARGE_H__
#define __CHARGE_H__

#include "my_bsp.h"
#include "my_define.h"


/**
 * @brief   充电打开
 */
inline void CHARGE_On(void);


/**
 * @brief   充电关闭
 */
inline void CHARGE_Off(void);


/**
 * @brief   充电检测
 */
E_TrueState CHARGE_Scan(void);


/**
 * @brief   充电初始化
 */
inline void CHARGE_Init(void);


#endif
