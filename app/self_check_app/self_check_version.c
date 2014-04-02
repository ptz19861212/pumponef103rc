/**
 * @file    self_check_version.c
 * @brief   版本号自检
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

#include "self_check_version_in.h"

// 版本号自检的自检项 英文
const char *sSelfCheckVersionTxtEn[] =
{
		"Version",
		"",
};

// 版本号自检的自检项 中文
const char *sSelfCheckVersionTxtCn[] =
{
		"版本号",
		"",
};

// 版本号自检的自检项 指针数组
const char **sSelfCheckVersionTxt[] =
{
		sSelfCheckVersionTxtEn,
		sSelfCheckVersionTxtCn,
};


// 版本号自检的下一个自检资源
const struct S_SelfCheckResource* sSelfCheckRsrVersionNext =
											&gSelfCheckRsrVersion;

// 版本号自检 资源，包括自身字符串，自检项字符串，自检项的数目
const struct S_SelfCheckResource gSelfCheckRsrVersion =
{
//		SELF_CHECK_RESOURCE(VERSION, Version, BuildDate)
		SELF_CHECK_RESOURCE(VERSION, Version, GasName)
};


/**
 * @brief   自检初始化
 */
void SelfCheckVersionInit(void)
{
	// 版本号自检资源初始化
	S_Device* lpDev;
	StateDevicePointGet(&lpDev);

	S_Lcd__Item_Mid lTrig;

	lTrig.Item.Pos = CONFIG_VERSION_POS;
	lTrig.Item.Char = lpDev->pConst->Version.Ver;
	lTrig.Len = CONFIG_VERSION_LEN;
	Lcd__FrameItemMidDisp(&lTrig);
}

