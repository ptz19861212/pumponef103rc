/**
 * @file    self_check_gas_name.c
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

#include "self_check_gas_name_in.h"

// 气体名称自检的自检项 英文
const char *sSelfCheckGasNameTxtEn[] =
{
		"Gas Name",
		"",
};

// 气体名称自检的自检项 中文
const char *sSelfCheckGasNameTxtCn[] =
{
		"气体名称",
		"",
};

// 气体名称自检的自检项 指针数组
const char **sSelfCheckGasNameTxt[] =
{
		sSelfCheckGasNameTxtEn,
		sSelfCheckGasNameTxtCn,
};


// 气体名称自检的下一个自检资源
const struct S_SelfCheckResource* sSelfCheckRsrGasNameNext =
											&gSelfCheckRsrGasName;

// 气体名称自检 资源，包括自身字符串，自检项字符串，自检项的数目
const struct S_SelfCheckResource gSelfCheckRsrGasName =
{
//		SELF_CHECK_RESOURCE(GAS_NAME, GasName, CaliDate)
		SELF_CHECK_RESOURCE(GAS_NAME, GasName, GasRange)
};


/**
 * @brief   自检初始化
 */
void SelfCheckGasNameInit(void)
{
	// 气体名称自检资源初始化

//	S_Device* lpDev;
//	StateDevicePointGet(&lpDev);

	S_Gas* lpGas;
	StateGasPointGet(&lpGas);

	E_Language lLang;
	lLang = Lcd__LangGet();

	S_Lcd__Item_Mid lTrig;

	lTrig.Item.Pos = CONFIG_GAS_NAME_POS;
//	lTrig.Item.Char = lpDev->pConst->Version.Date;
	lTrig.Item.Char = lpGas->pConst->Name[lLang];
	lTrig.Len = CONFIG_GAS_NAME_LEN;
	Lcd__FrameItemMidDisp(&lTrig);
}

