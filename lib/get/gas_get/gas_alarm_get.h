/**
 * @file    gas_alarm_get.h
 * @brief   获得报警状态
 * @author  ptz
 * @email   ptz19861212@163.com
 * @version 0.0.1
 * @date    2013-12-25 14:09:53 星期三 
 * @history (1).2013-12-25 14:09:53 星期三 create
 */
/* Copyright (C)
 * 
 * My own license
 * All right reserved
 * 
 */

#ifndef __GAS_ALARM_GET_H__
#define __GAS_ALARM_GET_H__

#include "my_gas.h"
#include "my_input.h"

/**
 * @brief   正向负向气体浓度求报警状态
 *
 * @param   lpGas 气体结构体
 */
void GasAlarmGet(S_Gas* lpGas);


/**
 * @brief   双向气体浓度求报警状态
 *
 * @param   lpGas 气体结构体
 */
void GasAlarmBothGet(S_Gas* lpGas);


typedef void (*FUNC_GAS_ALARM_GET)(S_Gas* lpGas);


/**
 * @brief   单向气体获得一级报警的上限和下限
 *
 * @param   lpGas 气体结构体
 * @param   lpInput 输入的数值上下限
 */
void GasAlarmLowerLimitGet(S_Gas* lpGas,
								S_Value_Input_Gas* lpInput);


/**
 * @brief   单向气体获得二级报警的上限和下限
 *
 * @param   lpGas 气体结构体
 * @param   lpInput 输入的数值上下限
 */
void GasAlarmUpperLimitGet(S_Gas* lpGas,
								S_Value_Input_Gas* lpInput);


/**
 * @brief   单向气体获得stel报警的上限和下限
 *
 * @param   lpGas 气体结构体
 * @param   lpInput 输入的数值上下限
 */
void GasAlarmStelLimitGet(S_Gas* lpGas,
								S_Value_Input_Gas* lpInput);


/**
 * @brief   单向气体获得twa报警的上限和下限
 *
 * @param   lpGas 气体结构体
 * @param   lpInput 输入的数值上下限
 */
void GasAlarmTwaLimitGet(S_Gas* lpGas,
								S_Value_Input_Gas* lpInput);


/**
 * @brief   双向气体获得一级报警的上限和下限
 *
 * @param   lpGas 气体结构体
 * @param   lpInput 输入的数值上下限
 */
void GasAlarmBothLowerLimitGet(S_Gas* lpGas,
									S_Value_Input_Gas* lpInput);


/**
 * @brief   双向气体获得二级报警的上限和下限
 *
 * @param   lpGas 气体结构体
 * @param   lpInput 输入的数值上下限
 */
void GasAlarmBothUpperLimitGet(S_Gas* lpGas,
									S_Value_Input_Gas* lpInput);


typedef void (*FUNC_GAS_ALARM_LIMIT_GET)(S_Gas* lpGas, \
												S_Value_Input_Gas* lpInput);

#endif
