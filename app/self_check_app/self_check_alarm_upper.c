/**
 * @file    self_check_alarm_upper.c
 * @brief   高限报警自检
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

#include "self_check_alarm_upper_in.h"

// 高限报警自检的自检项 英文
const char *sSelfCheckAlarmUpperTxtEn[] =
{
		"Alarm Upper",
		"",
};

// 高限报警自检的自检项 中文
const char *sSelfCheckAlarmUpperTxtCn[] =
{
		"高级报警",
		"",
};

// 高限报警自检的自检项 指针数组
const char **sSelfCheckAlarmUpperTxt[] =
{
		sSelfCheckAlarmUpperTxtEn,
		sSelfCheckAlarmUpperTxtCn,
};


// 高限报警自检的下一个自检资源
const struct S_SelfCheckResource* sSelfCheckRsrAlarmUpperNext =
											&gSelfCheckRsrAlarmUpper;

// 高限报警自检 资源，包括自身字符串，自检项字符串，自检项的数目
const struct S_SelfCheckResource gSelfCheckRsrAlarmUpper =
{
		SELF_CHECK_RESOURCE(ALARM_UPPER, AlarmUpper, AlarmLower)
};


/**
 * @brief   自检初始化
 */
void SelfCheckAlarmUpperInit(void)
{
	// 高限报警自检资源初始化
	S_Gas* lpGas;
	StateGasPointGet(&lpGas);

	S_Lcd__Unit lUnit;

	lUnit.Pos = CONFIG_ALARM_UPPER_POS;
	lUnit.Char = lpGas->pConst->Unit;
	Lcd__MenuUnitDisp(&lUnit);

	S_Value_Array_gas lValue;
	char lData[GAS_VALUE_ARRAY_SIZE];

	lValue.Char = lData;
	lValue.Value.Num = lpGas->pSave->Alarm.Upper;
	lValue.Value.Point = lpGas->pConst->Point;
	DecToStrU16(&lValue);

	S_Lcd__Item_Mid lTrig;

	lTrig.Item.Pos = CONFIG_ALARM_UPPER_POS;
	lTrig.Item.Char = lValue.Char;
	lTrig.Len = CONFIG_ALARM_UPPER_LEN;

	Lcd__MenuItemMidDisp(&lTrig);
}

