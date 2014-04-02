/**
 * @file    gas_cali_coeff.h
 * @brief   系数校准
 * @author  ptz
 * @email   ptz19861212@163.com
 * @version 0.0.1
 * @date    2014-01-14 16:17:45 星期二 
 * @history (1).2014-01-14 16:17:45 星期二 create
 */
/* Copyright (C)
 * 
 * My own license
 * All right reserved
 * 
 */

#ifndef __GAS_CALI_COEFF_H__
#define __GAS_CALI_COEFF_H__

#include <stdint.h>
#include "my_define.h"
#include "my_gas.h"
#include "my_error.h"

typedef struct
{
	// 数值
	my_gas_t Value;
	// adc 数值
	uint16_t AdcNow;
	// adc 零点
	uint16_t AdcZero;
	// adc 标气的时候屏蔽范围
	uint16_t Threshold;
	// 标气成功还是失败
	E_TrueState CaliSuc;
	// 如果出错，错误号
	E_ErrorState ErrNum;
}S_Gas_Cali_Coeff;


/**
 * @brief   气体浓度标气
 *
 * @param   lpCali
 * @param   lpPoint 正向气体使用REF1，负向和双向气体使用REF3
 */
void GasCaliCoeffGetPositive(S_Gas_Cali_Coeff* lpCali,
//										S_Gas_Point* lpPoint);
										S_Gas* lpGas);


/**
 * @brief   气体浓度标气
 *
 * @param   lpCali
 * @param   lpPoint 正向气体使用REF1，负向和双向气体使用REF3
 */
void GasCaliCoeffGetNegative(S_Gas_Cali_Coeff* lpCali,
//										S_Gas_Point* lpPoint);
									S_Gas* lpGas);


/**
 * @brief   气体浓度标气
 *
 * @param   lpCali
 * @param   lpPoint 正向气体使用REF1，负向和双向气体使用REF3
 */
void GasCaliCoeffGetBoth(S_Gas_Cali_Coeff* lpCali,
//										S_Gas_Point* lpPoint);
									S_Gas* lpGas);

typedef void (*FUNC_GAS_CALI_COEFF_GET)
					(S_Gas_Cali_Coeff* lpCali, \
//						S_Gas_Point* lpPoint);
						S_Gas* lpGas);

#endif
