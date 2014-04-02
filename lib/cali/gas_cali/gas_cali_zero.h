/**
 * @file    gas_cali_zero.h
 * @brief   零点校准
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

#ifndef __GAS_CALI_ZERO_H__
#define __GAS_CALI_ZERO_H__

#include <stdint.h>
#include "my_define.h"
#include "my_gas.h"
#include "my_error.h"

typedef struct
{
	// adc 数值
	uint16_t AdcNow;
	// adc 零点
	uint16_t AdcZero;
	// adc 范围
	uint16_t ZeroRange;
	// 标零成功还是失败
	E_TrueState CaliSuc;
	// 如果出错，错误号
	E_ErrorState ErrNum;
}S_Gas_Cali_Zero;


/**
 * @brief   气体浓度标零
 *
 * @param   lpCali
 * @param   lpPoint 正向气体使用REF1，负向和双向气体使用REF3
 */
void GasCaliZeroGetPositive(S_Gas_Cali_Zero* lpCali,
//								S_Gas_Point* lpPoint);
								S_Gas* lpGas);


/**
 * @brief   负向气体浓度标零
 *
 * @param   lpCali
 * @param   lpGas
 */
void GasCaliZeroGetNegative(S_Gas_Cali_Zero* lpCali,
								S_Gas* lpGas);


/**
 * @brief   双向气体浓度标零
 *
 * @param   lpCali
 * @param   lpGas
 */
void GasCaliZeroGetBoth(S_Gas_Cali_Zero* lpCali,
								S_Gas* lpGas);


typedef void (*FUNC_GAS_CALI_ZERO_GET)
					(S_Gas_Cali_Zero* lpCali, \
//						S_Gas_Point* lpPoint);
						S_Gas* lpGas);

#endif
