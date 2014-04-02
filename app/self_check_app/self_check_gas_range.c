/**
 * @file    self_check_gas_range.c
 * @brief   气体名称自检
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

#include "self_check_gas_range_in.h"

// 气体名称自检的自检项 英文
const char *sSelfCheckGasRangeTxtEn[] =
{
		"Gas Range",
		"",
};

// 气体名称自检的自检项 中文
const char *sSelfCheckGasRangeTxtCn[] =
{
		"气体量程",
		"",
};

// 气体名称自检的自检项 指针数组
const char **sSelfCheckGasRangeTxt[] =
{
		sSelfCheckGasRangeTxtEn,
		sSelfCheckGasRangeTxtCn,
};


// 气体名称自检的下一个自检资源
const struct S_SelfCheckResource* sSelfCheckRsrGasRangeNext =
											&gSelfCheckRsrGasRange;

// 气体名称自检 资源，包括自身字符串，自检项字符串，自检项的数目
const struct S_SelfCheckResource gSelfCheckRsrGasRange =
{
//		SELF_CHECK_RESOURCE(GAS_RANGE, GasRange, CaliDate)
		SELF_CHECK_RESOURCE(GAS_RANGE, GasRange, AlarmUpper)
};


/**
 * @brief   自检初始化
 */
void SelfCheckGasRangeInit(void)
{
	// 气体量程自检资源初始化
	S_Gas* lpGas;
	StateGasPointGet(&lpGas);

	S_Lcd__Unit lUnit;

	lUnit.Pos = CONFIG_GAS_RANGE_POS;
	lUnit.Char = lpGas->pConst->Unit;
	Lcd__MenuUnitDisp(&lUnit);

	S_Value_Array_gas lValue;
	char lData[GAS_VALUE_ARRAY_SIZE];

	lValue.Char = lData;
	lValue.Value.Num = lpGas->pConst->Range;
	lValue.Value.Point = lpGas->pConst->Point;
	DecToStrU16(&lValue);

	S_Lcd__Item_Mid lTrig;

	lTrig.Item.Pos = CONFIG_GAS_RANGE_POS;
	lTrig.Item.Char = lValue.Char;
	lTrig.Len = CONFIG_GAS_RANGE_LEN;

	Lcd__MenuItemMidDisp(&lTrig);
}

