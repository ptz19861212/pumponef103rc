/**
 * @file    config_gas_o2.h
 * @brief   O2相关设置
 * @author  ptz
 * @email   ptz19861212@163.com
 * @version 0.0.1
 * @date    2013-12-19 23:51:16 星期四 
 * @history (1).2013-12-19 23:51:16 星期四 create
 */
/* Copyright (C)
 * 
 * My own license
 * All right reserved
 * 
 */

#ifndef __CONFIG_O2_H__
#define __CONFIG_O2_H__

#include "my_compile.h"
// 不需要包换那些 my_gas.h ，因为宏也只是替换，所以不需要包含气体名称的头文件


// 这个是为了O2和EX气体不能设置STEL和TWA进行的，
#include "my_gas_name.h"
// 这个是为了O2和EX气体不能设置STEL和TWA进行的，注意
// 预编译的判断不能有枚举和sizeof

// 气体
#define CONFIG_GAS						GAS_O2

// 气体单位
#define CONFIG_GAS_UNIT_INDEX			GAS_UNIT_VOL
#define CONFIG_GAS_UNIT					"%VOL"

// 气体名称
#define CONFIG_GAS_NAME_INDEX			GAS_NAME_INDEX_O2
#define CONFIG_GAS_NAME_EN				"O2"
#define CONFIG_GAS_NAME_CN				"氧气"

// 气体方向
#define CONFIG_GAS_DIRECT				GAS_DIRECT_BOTH
//// 气体数值计算
//#define CONFIG_GAS_FUNC_VALUE_GET		GasValueGetBoth
//// 气体报警获得
//#define CONFIG_GAS_FUNC_ALARM_GET		GasAlarmBothGet
//// 气体低报限获得
//#define CONFIG_GAS_FUNC_ALARM_LOWER_LIMIT_GET		\
//			GasAlarmBothLowerLimitGet
//
//// 气体高报限获得
//#define CONFIG_GAS_FUNC_ALARM_UPPER_LIMIT_GET		\
//			GasAlarmBothUpperLimitGet
//
//// 气体STEL
//#define CONFIG_GAS_FUNC_ALARM_STEL_LIMIT_GET		\
//			GasAlarmStelLimitGet
//
//// 气体TWA
//#define CONFIG_GAS_FUNC_ALARM_TWA_LIMIT_GET		\
//			GasAlarmTwaLimitGet
//
//// 气体数值限制获得
//#define CONFIG_GAS_FUNC_GAS_VALUE_LIMIT_GET	\
//			GasValueLimitGet
//
//// 气体标零
//#define CONFIG_GAS_FUNC_GAS_CALI_ZERO_GET	\
//			GasCaliZeroGetBoth
//
//// 气体标气
//#define CONFIG_GAS_FUNC_GAS_CALI_COEFF_GET	\
//			GasCaliCoeffGetBoth

// 校准日期
#define CONFIG_GAS_CALI_DATE_MON				1
#define CONFIG_GAS_CALI_DATE_DAY				22
#define CONFIG_GAS_CALI_DATE_YEAR				2014
// 校准时间
#define CONFIG_GAS_CALI_TIME_HOUR				9
#define CONFIG_GAS_CALI_TIME_MIN				10
#define CONFIG_GAS_CALI_TIME_SEC				11

#if (CONFIG_O2__30_0 == PRE_COMP_ENABLE)
	// 小数点
	#define CONFIG_GAS_POINT					POINT_HHHHXH
	// 量程
	#define CONFIG_GAS_RANGE					300
	// 低报
	#define CONFIG_GAS_ALARM_LOWER			235
	// 高报
	#define CONFIG_GAS_ALARM_UPPER			185
	// STEL
	#define CONFIG_GAS_ALARM_STEL			50
	// TWA
	#define CONFIG_GAS_ALARM_TWA			50
	// ref1 数值
	#define CONFIG_GAS_REF1_VALUE			0
	// ref1 ADC
	#define CONFIG_GAS_REF1_ADC				220

	// ref2 数值
	#define CONFIG_GAS_REF2_VALUE			0
	// ref2 ADC
	#define CONFIG_GAS_REF2_ADC				0

	// ref3 数值
	#define CONFIG_GAS_REF3_VALUE			209
	// ref3 ADC
	#define CONFIG_GAS_REF3_ADC				2570

	// ref4 数值
	#define CONFIG_GAS_REF4_VALUE			0
	// ref4 ADC
	#define CONFIG_GAS_REF4_ADC				0

	// ref5 数值
	#define CONFIG_GAS_REF5_VALUE			0
	// ref5 ADC
	#define CONFIG_GAS_REF5_ADC				0

	// 在最低点的屏蔽数值
	#define CONFIG_GAS_REF1_THRESHOLD		2
	// 标气和正常检测气体的时候的屏蔽数值
	#define CONFIG_GAS_VALUE_THRESHOLD		1
	// 标零时候的ADC范围
	#define CONFIG_GAS_REF1_RANGE			200

#elif (CONFIG_O2__100 == PRE_COMP_ENABLE)

#endif

// 零点ADC
#define CONFIG_GAS_ZERO_ADC			CONFIG_GAS_REF3_ADC
// 零点数值
#define CONFIG_GAS_ZERO_VALUE		CONFIG_GAS_REF3_VALUE
// 零点范围
#define CONFIG_GAS_ZERO_RANGE		CONFIG_GAS_REF1_RANGE


#endif
