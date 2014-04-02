/**
 * @file    pump.h
 * @brief   泵
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

#ifndef __PUMP_H__
#define __PUMP_H__

#include "my_bsp.h"


/**
 * @brief   泵打开
 */
inline void PUMP_On(void);


/**
 * @brief   泵关闭
 */
inline void PUMP_Off(void);


/**
 * @brief   泵初始化
 */
inline void PUMP_Init(void);


#endif
