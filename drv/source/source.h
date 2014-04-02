/**
 * @file    source.h
 * @brief   电源
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

#ifndef __SOURCE_H__
#define __SOURCE_H__

#include "my_bsp.h"


/**
 * @brief   电源打开
 */
inline void SOURCE_On(void);


/**
 * @brief   电源关闭
 */
inline void SOURCE_Off(void);


/**
 * @brief   电源初始化
 */
inline void SOURCE_Init(void);


#endif
