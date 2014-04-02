/**
 * @file    self_check_alarm_stel.c
 * @brief   短时报警自检
 * @author  ptz
 * @email   ptz19861212@163.com
 * @version 0.0.1
 * @date    2013-12-02 13:34:47 星期一 
 * @history (1).2013-12-02 13:34:47 星期一 create
 */
/* Copyright (C)
 * 
 * My own license
 * All right reserved
 * 
 */

#include "self_check_alarm_stel_in.h"

// 短时报警自检的自检项 英文
const char *sSelfCheckAlarmStelTxtEn[] =
{
		"Alarm Stel",
		"",
};

// 短时报警自检的自检项 中文
const char *sSelfCheckAlarmStelTxtCn[] =
{
		"短时报警",
		"",
};

// 短时报警自检的自检项 指针数组
const char **sSelfCheckAlarmStelTxt[] =
{
		sSelfCheckAlarmStelTxtEn,
		sSelfCheckAlarmStelTxtCn,
};


// 短时报警自检的下一个自检资源
const struct S_SelfCheckResource* sSelfCheckRsrAlarmStelNext =
											&gSelfCheckRsrAlarmStel;

// 短时报警自检 资源，包括自身字符串，自检项字符串，自检项的数目
const struct S_SelfCheckResource gSelfCheckRsrAlarmStel =
{
		SELF_CHECK_RESOURCE(ALARM_STEL, AlarmStel, AlarmTwa)
};


/**
 * @brief   自检初始化
 */
void SelfCheckAlarmStelInit(void)
{
	// 短时报警自检资源初始化
	S_Gas* lpGas;
	StateGasPointGet(&lpGas);

	S_Lcd__Unit lUnit;

	lUnit.Pos = CONFIG_ALARM_STEL_POS;
	lUnit.Char = lpGas->pConst->Unit;
	Lcd__MenuUnitDisp(&lUnit);

	S_Value_Array_gas lValue;
	char lData[GAS_VALUE_ARRAY_SIZE];

	lValue.Char = lData;
	lValue.Value.Num = lpGas->pSave->Alarm.Stel;
	lValue.Value.Point = lpGas->pConst->Point;
	DecToStrU16(&lValue);

	S_Lcd__Item_Mid lTrig;

	lTrig.Item.Pos = CONFIG_ALARM_STEL_POS;
	lTrig.Item.Char = lValue.Char;
	lTrig.Len = CONFIG_ALARM_STEL_LEN;

	Lcd__MenuItemMidDisp(&lTrig);
}

