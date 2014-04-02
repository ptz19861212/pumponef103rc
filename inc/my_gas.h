/**
 * @file    my_gas.h
 * @brief   gas
 * @author  ptz
 * @email   ptz19861212@163.com
 * @version 0.0.1
 * @date    2012-08-07 15:24:16 星期四
 * @history (2).2013-12-17 16:32:10 星期一 modify stm32 把某些数据改成了16位
 * 				(1).2012-08-07 15:24:16 星期四 create
 */
/* Copyright (C)
 * 
 * My own license
 * All right reserved
 * 
 */

#ifndef __MY_GAS_H__
#define __MY_GAS_H__

#include <stdint.h>
#include "my_define.h"
#include "my_gas_name.h"
#include "my_gas.h"
#include "my_num.h"
#include "my_calendar.h"


// 为了判断是多少位数据
#include "config_bsp.h"
#if (CONFIG_GAS_VALUE_BITS == 16)
	typedef uint16_t 						my_gas_t;
	typedef S_Value_U16					S_Value_gas;
	typedef S_Value_Array_U16			S_Value_Array_gas;
	#define GAS_VALUE_ARRAY_SIZE		7
#endif


typedef enum {GAS_DIRECT_POSITIVE = 0, \
				GAS_DIRECT_NEGATIVE,\
				GAS_DIRECT_BOTH} GasDirState;

typedef enum {GAS_ALARM_NORMAL = 0, \
				GAS_ALARM_LOWER,\
				GAS_ALARM_UPPER} GasAlarmState;

typedef enum {GAS_ERROR_NONE = 0, \
				GAS_ERROR_ZERO,\
				GAS_ERROR_GAS} GasErrorState;

typedef enum {GAS_STATE_NORMAL = 0, \
				GAS_STATE_ZERO,\
				GAS_STATE_GAS} GasStateState;

typedef enum {GAS_UNIT_NONE = 0, \
				GAS_UNIT_PPM,\
				GAS_UNIT_LEL,\
				GAS_UNIT_VOL} GasUnitState;

typedef enum {GAS_NAME_INDEX_NONE = 0x00, \
				GAS_NAME_INDEX_O2 = GAS_O2,\
				GAS_NAME_INDEX_EX = GAS_EX,\
				GAS_NAME_INDEX_CO = GAS_CO,\
				GAS_NAME_INDEX_H2S = GAS_H2S,\
				GAS_NAME_INDEX_SO2 = GAS_SO2,\
				GAS_NAME_INDEX_NO = GAS_NO,\
				GAS_NAME_INDEX_NO2 = GAS_NO2,\
				// 0x08
				GAS_NAME_INDEX_CL2 = GAS_CL2,\
				GAS_NAME_INDEX_NH3 = GAS_NH3,\
				GAS_NAME_INDEX_H2 = GAS_H2,\
				GAS_NAME_INDEX_HCN = GAS_HCN,\
				GAS_NAME_INDEX_PH3 = GAS_PH3,\
				GAS_NAME_INDEX_O3 = GAS_O3,\
				GAS_NAME_INDEX_CLO2 = GAS_CLO2,\
				GAS_NAME_INDEX_C2H4O = GAS_C2H4O,\
				// 0x10
				GAS_NAME_INDEX_CH2O = GAS_CH2O,\
				GAS_NAME_INDEX_SIH4 = GAS_SIH4,\
				GAS_NAME_INDEX_HF = GAS_HF,\
				GAS_NAME_INDEX_F2 = GAS_F2,\
				GAS_NAME_INDEX_COCL2 = GAS_COCL2,\
				GAS_NAME_INDEX_CO2 = GAS_CO2,\
				GAS_NAME_INDEX_SO2F2 = GAS_SO2F2,\
				GAS_NAME_INDEX_CH4O = GAS_CH4O,\
				GAS_NAME_INDEX_RESERVE = 0xFFFF
} GasNameIndexState;

// 气体固定属性的属性
struct S_Gas_Const_Func
{
	// 求气体浓度的虚拟函数
	MY_FUNC ValueGet;
	// 求气体报警的虚拟函数
	MY_FUNC AlarmGet;
	// 求气体一级报警的上下限的虚拟函数
	MY_FUNC AlarmLowerLimitGet;
	// 求气体二级报警的上下限的虚拟函数
	MY_FUNC AlarmUpperLimitGet;
#if ((CONFIG_GAS != GAS_O2) && (CONFIG_GAS != GAS_EX))
	// 求气体stel的上下限的虚拟函数
	MY_FUNC AlarmStelLimitGet;
	// 求气体twa报警的上下限的虚拟函数
	MY_FUNC AlarmTwaLimitGet;
#endif
	// 求气体标气的上下限的虚拟函数
	MY_FUNC GasValueLimitGet;
	// 气体标零的时候，判断标零是否成功
	MY_FUNC GasCaliZeroGet;
	// 气体标气的时候，判断标气是否成功
	MY_FUNC GasCaliCoeffGet;
};

// 气体固定属性的属性
struct S_Gas_Const
{
	//gas name
	GasNameIndexState NameIndex;
	// 气体名称的字符串数组
	const char** Name;
	//range of gas value
	my_gas_t Range;
	//the direct of gas sensor, 0 positive, 1 negative, 2 both
	GasDirState Direct;
	//the point of gas value
	PointState Point;
	// unit
	GasUnitState UnitIndex;
	const char* Unit;
	// ref1 threshold
	uint8_t ZeroThrs;
	// zero adc
	uint16_t ZeroAdc;
	// zero value
	uint16_t ZeroValue;
	// 标零范围
	uint16_t ZeroAdcRange;
	// 标气的时候屏蔽的数值
	uint16_t CaliCoeffThrs;
	// 调用的函数
	struct S_Gas_Const_Func vFunc;

//	// 求气体浓度的虚拟函数
//	MY_FUNC vFuncValueGet;
//	// 求气体报警的虚拟函数
//	MY_FUNC vFuncAlarmGet;
//	// 求气体一级报警的上下限的虚拟函数
//	MY_FUNC vFuncAlarmLowerLimitGet;
//	// 求气体二级报警的上下限的虚拟函数
//	MY_FUNC vFuncAlarmUpperLimitGet;
//#if ((CONFIG_GAS != GAS_O2) && (CONFIG_GAS != GAS_EX))
//	// 求气体stel的上下限的虚拟函数
//	MY_FUNC vFuncAlarmStelLimitGet;
//	// 求气体twa报警的上下限的虚拟函数
//	MY_FUNC vFuncAlarmTwaLimitGet;
//#endif
//	// 求气体标气的上下限的虚拟函数
//	MY_FUNC vFuncGasValueLimitGet;
//	// 气体标零的时候，判断标零是否成功
//	MY_FUNC vFuncGasCaliZeroGet;
//	// 气体标气的时候，判断标气是否成功
//	MY_FUNC vFuncGasCaliCoeffGet;

};

// 气体保存参考点的内容
typedef struct
{
	// 气体数值
	my_gas_t Value;
	// adc 数值
	uint16_t Adc;
}S_Gas_Point;

// 气体报警的数值
struct S_Gas_Alarm
{
	// 一级报警的数值
	my_gas_t Lower;
	// 二级报警的数值
	my_gas_t Upper;
	// 15分钟 短时加权报警，多次取值求平均，间隔不能小于5分钟
	my_gas_t Stel;
	// 8小时 长时加权报警，多次取值求平均，间隔不能小于15分钟
	my_gas_t Twa;
};

// 气体保存下来可以改变的属性
struct S_Gas_Save
{
	// 拟合的斜线的ADC最低端，普通气体方面可以使用
	S_Gas_Point Ref1;
	// 拟合的斜线的ADC中间端，一般只用于氧气方面，适合于氧气 0-20.9 中间的一个点
	S_Gas_Point Ref2;
	// 拟合的斜线的ADC高端，普通气体方面可以使用
	S_Gas_Point Ref3;
	// 拟合的斜线的ADC高端向上的点，用于氧气方面在20.9-30之间的点
	S_Gas_Point Ref4;
	// 拟合斜线上面可能以后用到的最高点，可能是氧气的30的点，暂时不用
	S_Gas_Point Ref5;
	// 报警
	struct S_Gas_Alarm Alarm;
	// 校准日期
	S_Calendar_Date CaliDate;
	// 校准时间
	S_Calendar_Time CaliTime;
	//is this struct member saved?
	union
	{
		uint16_t Save;
		struct
		{
			uint8_t Ref1			:	1;
			uint8_t Ref2			:	1;
			uint8_t Ref3			:	1;
			uint8_t Ref4			:	1;
			uint8_t Ref5			:	1;
			uint8_t Lower			:	1;		//low
			uint8_t Upper			:	1;
			uint8_t Stel			:	1;
			uint8_t Twa			:	1;
			uint8_t Date			:	1;
			uint8_t Time			:	1;
			uint8_t RESERVE		:	5;
		}Save_Bits;
	};
};

// 开机以后计算的临时数值
struct S_Gas_Temp
{
	// 当前的ADC在斜线上面所在的点
	S_Gas_Point Point;
	// 当前是正常还是低报或者高报？
	GasAlarmState Alarm;
	// 当前状态是正常还是标零，标气?
	GasStateState State;
	// 当前的数值是否达到了量程.
	E_TurnState FullBlink;
	// 产生了错误，这个错误是产生在标零还是标气？
	GasErrorState Error;
	// 报警
	struct S_Gas_Alarm AlarmSave;
};

// 气体相关属性
typedef struct
{
	const struct S_Gas_Const* pConst;
	struct S_Gas_Save* pSave;
	struct S_Gas_Temp* pTemp;
}S_Gas;




#define GAS_DIRECT_POSITIVE				0
#define GAS_DIRECT_NEGATIVE				1
#define GAS_DIRECT_BOTH					2


// 正向气体调用的函数
#if (CONFIG_GAS_DIRECT == GAS_DIRECT_POSITIVE)
// 气体数值计算
#define CONFIG_GAS_FUNC_VALUE_GET		GasValueGetPositive
// 气体报警获得
#define CONFIG_GAS_FUNC_ALARM_GET		GasAlarmGet
// 气体低报限获得
#define CONFIG_GAS_FUNC_ALARM_LOWER_LIMIT_GET		\
			GasAlarmLowerLimitGet

// 气体高报限获得
#define CONFIG_GAS_FUNC_ALARM_UPPER_LIMIT_GET		\
			GasAlarmUpperLimitGet

// 气体STEL
#define CONFIG_GAS_FUNC_ALARM_STEL_LIMIT_GET		\
			GasAlarmStelLimitGet

// 气体TWA
#define CONFIG_GAS_FUNC_ALARM_TWA_LIMIT_GET		\
			GasAlarmTwaLimitGet

// 气体数值限制获得
#define CONFIG_GAS_FUNC_GAS_VALUE_LIMIT_GET	\
			GasValueLimitGet

// 气体标零
#define CONFIG_GAS_FUNC_GAS_CALI_ZERO_GET	\
			GasCaliZeroGetPositive

// 气体标气
#define CONFIG_GAS_FUNC_GAS_CALI_COEFF_GET	\
			GasCaliCoeffGetPositive

// 负向气体调用的函数
#elif (CONFIG_GAS_DIRECT == GAS_DIRECT_NEGATIVE)

// 双向气体调用的函数
#elif (CONFIG_GAS_DIRECT == GAS_DIRECT_BOTH)
// 气体数值计算
#define CONFIG_GAS_FUNC_VALUE_GET		GasValueGetBoth
// 气体报警获得
#define CONFIG_GAS_FUNC_ALARM_GET		GasAlarmBothGet
// 气体低报限获得
#define CONFIG_GAS_FUNC_ALARM_LOWER_LIMIT_GET		\
			GasAlarmBothLowerLimitGet

// 气体高报限获得
#define CONFIG_GAS_FUNC_ALARM_UPPER_LIMIT_GET		\
			GasAlarmBothUpperLimitGet

// 气体STEL
#define CONFIG_GAS_FUNC_ALARM_STEL_LIMIT_GET		\
			GasAlarmStelLimitGet

// 气体TWA
#define CONFIG_GAS_FUNC_ALARM_TWA_LIMIT_GET		\
			GasAlarmTwaLimitGet

// 气体数值限制获得
#define CONFIG_GAS_FUNC_GAS_VALUE_LIMIT_GET	\
			GasValueLimitGet

// 气体标零
#define CONFIG_GAS_FUNC_GAS_CALI_ZERO_GET	\
			GasCaliZeroGetBoth

// 气体标气
#define CONFIG_GAS_FUNC_GAS_CALI_COEFF_GET	\
			GasCaliCoeffGetBoth

#endif

//#define GAS_ALARM_NORMAL					0
//#define GAS_ALARM_LOW					1
//#define GAS_ALARM_HIGH					2

//#define GAS_ERROR_NONE					0
//#define GAS_ERROR_ZERO					1
//#define GAS_ERROR_GAS					2

//#define GAS_STATUS_NORMAL				0
//#define GAS_STATUS_ZERO					1
//#define GAS_STATUS_GAS					2

//#define GAS_UNIT_NONE						0
//#define GAS_UNIT_PPM						1
//#define GAS_UNIT_LEL						2
//#define GAS_UNIT_VOL						3



//#define GAS_NAME_O2											0x01
//#define GAS_NAME_EX											0x02
//#define GAS_NAME_CO											0x03
//#define GAS_NAME_H2S											0x04
//#define GAS_NAME_CL2											0x08
//#define GAS_NAME_PH3											0x09
//
//#define GAS_NAME_HF											0x12
//#define GAS_NAME_SO2F2										0x16


#endif
