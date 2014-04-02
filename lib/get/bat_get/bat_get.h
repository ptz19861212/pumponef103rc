/**
 * @file    bat_get.h
 * @brief   获得电池状态
 * @author  ptz
 * @email   ptz19861212@163.com
 * @version 0.0.1
 * @date    2013-12-26 09:41:18 星期四 
 * @history (1).2013-12-26 09:41:18 星期四 create
 */
/* Copyright (C)
 * 
 * My own license
 * All right reserved
 * 
 */

#ifndef __BAT_GET_H__
#define __BAT_GET_H__

#include "my_device.h"

/**
 * @brief   求电池容量
 *
 * @param   lpDev 设备结构体地址
 */
void BatValueGet(S_Device* lpDev);


/**
 * @brief   求电池容量等级，这个函数是和显示相关的，显示电池容量的等级
 *
 * @param   lpDev 设备结构体地址
 */
void BatLevelGet(S_Device* lpDev);

#endif
