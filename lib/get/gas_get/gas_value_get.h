/**
 * @file    gas_value_get.h
 * @brief   获得气体浓度
 * @author  ptz
 * @email   ptz19861212@163.com
 * @version 0.0.1
 * @date    2013-12-22 09:54:39 星期日 
 * @history (1).2013-12-22 09:54:39 星期日 create
 */
/* Copyright (C)
 * 
 * My own license
 * All right reserved
 * 
 */

#ifndef __GAS_VALUE_GET_H__
#define __GAS_VALUE_GET_H__


#include "my_gas.h"
#include "my_input.h"


/**
 * @brief   正向气体浓度求数值
 *
 * @param   lpPoint 当前的点
 * @param   lpRef1 参考点1
 * @param   lpRef3 参考点3
 * @param   lThreshold 参考点1向上的屏蔽数值
 */
void GasValueGetPositive(S_Gas* lpGas);
//void GasValueGetPositive(S_Gas_Point* lpPoint,
//							S_Gas_Point* lpRef1,
//							S_Gas_Point* lpRef3,
//							uint8_t lThreshold);


/**
 * @brief   负向气体浓度求数值
 *
 * @param   lpPoint 当前的点
 * @param   lpRef1 参考点1
 * @param   lpRef3 参考点3
 * @param   lThreshold 参考点1向上的屏蔽数值
 */
void GasValueGetNegative(S_Gas* lpGas);
//void GasValueGetNegative(S_Gas_Point* lpPoint,
//							S_Gas_Point* lpRef1,
//							S_Gas_Point* lpRef3,
//							uint8_t lThreshold);


/**
 * @brief   双向气体浓度求数值
 *
 * @param   lpPoint 当前的点
 * @param   lpRef1 参考点1
 * @param   lpRef3 参考点3
 * @param   lThreshold 参考点1向上的屏蔽数值
 */
void GasValueGetBoth(S_Gas* lpGas);
//void GasValueGetBoth(S_Gas_Point* lpPoint,
//							S_Gas_Point* lpRef1,
//							S_Gas_Point* lpRef2,
//							S_Gas_Point* lpRef3,
//							S_Gas_Point* lpRef4,
//							uint8_t lThreshold);


/**
 * @brief   气体获得标气的上限和下限
 *
 * @param   lpGas 气体结构体
 * @param   lpInput 输入的数值上下限
 */
void GasValueLimitGet(S_Gas* lpGas,
								S_Value_Input_Gas* lpInput);


typedef void (*FUNC_GAS_VALUE_GET)(S_Gas* lpGas);
//typedef void (*FUNC_GAS_VALUE_GET)(S_Gas_Point* lp, \
//										S_Gas_Point* lp1,\
//										S_Gas_Point* lp3, uint8_t lTh);

//typedef void (*FUNC_GAS_VALUE_BOTH_GET)
//									(S_Gas_Point* lp, \
//									S_Gas_Point* lp1,\
//									S_Gas_Point* lp2,\
//									S_Gas_Point* lp3,\
//									S_Gas_Point* lp4, uint8_t lTh);

typedef void (*FUNC_GAS_VALUE_LIMIT_GET)(S_Gas* lpGas, \
										S_Value_Input_Gas* lpInput);


#endif
