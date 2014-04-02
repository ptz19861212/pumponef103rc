/**
 * @file    gas_alarm_get.c
 * @brief   报警状态计算
 * @author  ptz
 * @email   ptz19861212@163.com
 * @version 0.0.1
 * @date    2013-12-25 14:09:19 星期三 
 * @history (1).2013-12-25 14:09:19 星期三 create
 */
/* Copyright (C)
 * 
 * My own license
 * All right reserved
 * 
 */

#include "gas_alarm_get_in.h"

/**
 * @brief   正向负向气体浓度求报警状态
 *
 * @param   lpGas 气体结构体
 */
void GasAlarmGet(S_Gas* lpGas)
{
	my_gas_t lValue;

	lValue = lpGas->pTemp->Point.Value;

	if (lValue < lpGas->pSave->Alarm.Lower)
	{
		lpGas->pTemp->Alarm = GAS_ALARM_NORMAL;
	}
	else if (lValue < lpGas->pSave->Alarm.Upper)
	{
		lpGas->pTemp->Alarm = GAS_ALARM_LOWER;
	}
	else
	{
		lpGas->pTemp->Alarm = GAS_ALARM_UPPER;
	}
}


/**
 * @brief   双向气体浓度求报警状态
 *
 * @param   lpGas 气体结构体
 */
void GasAlarmBothGet(S_Gas* lpGas)
{
	my_gas_t lValue;

	lValue = lpGas->pTemp->Point.Value;

	if (lValue > lpGas->pSave->Alarm.Lower)
	{
		lpGas->pTemp->Alarm = GAS_ALARM_LOWER;
	}
	else if (lValue < lpGas->pSave->Alarm.Upper)
	{
		lpGas->pTemp->Alarm = GAS_ALARM_UPPER;
	}
	else
	{
		lpGas->pTemp->Alarm = GAS_ALARM_NORMAL;
	}
}


/**
 * @brief   单向气体获得一级报警的上限和下限
 *
 * @param   lpGas 气体结构体
 * @param   lpInput 输入的数值上下限
 */
void GasAlarmLowerLimitGet(S_Gas* lpGas,
								S_Value_Input_Gas* lpInput)
{
//	lpInput->Up = lpGas->pSave->Alarm.Upper;
	lpInput->Up = lpGas->pSave->Alarm.Upper - 1;

//	lpInput->Up = lpGas->pTemp->AlarmSave.Upper;

//	lpInput->Low = 0;
	lpInput->Low = 0 + 1;

	lpInput->Init = lpGas->pSave->Alarm.Lower;

//	lpInput->Init = lpGas->pTemp->AlarmSave.Lower;
}


/**
 * @brief   单向气体获得二级报警的上限和下限
 *
 * @param   lpGas 气体结构体
 * @param   lpInput 输入的数值上下限
 */
void GasAlarmUpperLimitGet(S_Gas* lpGas,
								S_Value_Input_Gas* lpInput)
{
//	lpInput->Up = lpGas->pConst->Range;
	lpInput->Up = lpGas->pConst->Range - 1;
//	lpInput->Low = lpGas->pSave->Alarm.Lower;
	lpInput->Low = lpGas->pSave->Alarm.Lower + 1;
//	lpInput->Low = lpGas->pTemp->AlarmSave.Lower;
	lpInput->Init = lpGas->pSave->Alarm.Upper;
//	lpInput->Init = lpGas->pTemp->AlarmSave.Upper;
}


#if ((CONFIG_GAS != GAS_O2) && (CONFIG_GAS != GAS_EX))
/**
 * @brief   单向气体获得stel报警的上限和下限
 *
 * @param   lpGas 气体结构体
 * @param   lpInput 输入的数值上下限
 */
void GasAlarmStelLimitGet(S_Gas* lpGas,
								S_Value_Input_Gas* lpInput)
{
//	lpInput->Up = lpGas->pConst->Range;
	lpInput->Up = lpGas->pConst->Range - 1;
//	lpInput->Low = 0;
	lpInput->Low = 0 + 1;
	lpInput->Init = lpGas->pSave->Alarm.Stel;
//	lpInput->Init = lpGas->pTemp->AlarmSave.Stel;
}


/**
 * @brief   单向气体获得twa报警的上限和下限
 *
 * @param   lpGas 气体结构体
 * @param   lpInput 输入的数值上下限
 */
void GasAlarmTwaLimitGet(S_Gas* lpGas,
								S_Value_Input_Gas* lpInput)
{
//	lpInput->Up = lpGas->pConst->Range;
	lpInput->Up = lpGas->pConst->Range - 1;
//	lpInput->Low = 0;
	lpInput->Low = 0 + 1;
	lpInput->Init = lpGas->pSave->Alarm.Twa;
//	lpInput->Init = lpGas->pTemp->AlarmSave.Twa;
}
#endif


/**
 * @brief   双向气体获得一级报警的上限和下限
 *
 * @param   lpGas 气体结构体
 * @param   lpInput 输入的数值上下限
 */
void GasAlarmBothLowerLimitGet(S_Gas* lpGas,
									S_Value_Input_Gas* lpInput)
{
//	lpInput->Up = lpGas->pConst->Range;
	lpInput->Up = lpGas->pConst->Range - 1;
//	lpInput->Low = lpGas->pSave->Ref3.Value;
//	lpInput->Low = lpGas->pSave->Alarm.Upper;
	lpInput->Low = lpGas->pSave->Alarm.Upper + 1;
//	lpInput->Low = lpGas->pTemp->AlarmSave.Upper;
	lpInput->Init = lpGas->pSave->Alarm.Lower;
//	lpInput->Init = lpGas->pTemp->AlarmSave.Lower;
}


/**
 * @brief   双向气体获得二级报警的上限和下限
 *
 * @param   lpGas 气体结构体
 * @param   lpInput 输入的数值上下限
 */
void GasAlarmBothUpperLimitGet(S_Gas* lpGas,
									S_Value_Input_Gas* lpInput)
{
//	lpInput->Up = lpGas->pSave->Ref3.Value;
//	lpInput->Up = lpGas->pSave->Alarm.Lower;
	lpInput->Up = lpGas->pSave->Alarm.Lower - 1;
//	lpInput->Up = lpGas->pTemp->AlarmSave.Lower;
//	lpInput->Low = 0;
	lpInput->Low = 0 + 1;
	lpInput->Init = lpGas->pSave->Alarm.Upper;
//	lpInput->Init = lpGas->pTemp->AlarmSave.Upper;
}

