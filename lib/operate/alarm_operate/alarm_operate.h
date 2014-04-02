/**
 * @file    alarm_operate.h
 * @brief   
 * @author  ptz
 * @email   ptz19861212@163.com
 * @version 0.0.1
 * @date    2014-01-23 14:46:39 星期四 
 * @history (1).2014-01-23 14:46:39 星期四 create
 */
/* Copyright (C)
 * 
 * My own license
 * All right reserved
 * 
 */

#ifndef __ALARM_OPERATE_H__
#define __ALARM_OPERATE_H__

#include "my_gas.h"
#include "my_device.h"


/**
 * @brief   获得报警状态
 *
 * @param   lpGas 气体结构体
 * @param   lpDev 设备结构体
 */
void AlarmOperate(S_Gas* lpGas, S_Device* lpDev);


#endif
