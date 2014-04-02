/**
 * @file    state_detect.h
 * @brief   检测状态
 * @author  ptz
 * @email   ptz19861212@163.com
 * @version 0.0.1
 * @date    2013-12-22 07:49:21 星期日 
 * @history (1).2013-12-22 07:49:21 星期日 create
 */
/* Copyright (C)
 * 
 * My own license
 * All right reserved
 * 
 */

#ifndef __STATE_DETECT_H__
#define __STATE_DETECT_H__

#include "my_gas.h"
#include "my_device.h"


/**
 * @brief   气体浓度求数值
 *
 * @param   lpGas 气体结构体
 */
void StateDetectValueGet(S_Gas* lpGas);


/**
 * @brief   正常状态初次显示
 *
 * @param   lpGas 气体结构体
 * @param   lpDev 设备结构体
 */
void StateDetectDispInit(S_Gas* lpGas, S_Device* lpDev);


/**
 * @brief   关机
 */
void StateDetectShutdown(void);


/**
 * @brief   充电的提示
 */
void StateDetectChargeInfo(S_Device* lpDev);


/**
 * @brief   充电状态的改变
 */
void StateDetectChargeInfoChange(S_Device* lpDev);

#endif
