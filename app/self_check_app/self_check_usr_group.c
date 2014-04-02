/**
 * @file    self_check_usr_group.c
 * @brief   用户组自检
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

#include "self_check_usr_group_in.h"

// 用户组自检的自检项 英文
const char *sSelfCheckUsrGroupTxtEn[] =
{
		"UsrGroup",
		"",
};

// 用户组自检的自检项 中文
const char *sSelfCheckUsrGroupTxtCn[] =
{
		"用户组",
		"",
};

// 用户组自检的自检项 指针数组
const char **sSelfCheckUsrGroupTxt[] =
{
		sSelfCheckUsrGroupTxtEn,
		sSelfCheckUsrGroupTxtCn,
};


// 用户组自检的下一个自检资源
const struct S_SelfCheckResource* sSelfCheckRsrUsrGroupNext =
											&gSelfCheckRsrUsrGroup;

// 用户组自检 资源，包括自身字符串，自检项字符串，自检项的数目
const struct S_SelfCheckResource gSelfCheckRsrUsrGroup =
{
		SELF_CHECK_RESOURCE(USR_GROUP, UsrGroup, UsrGroup)
};


/**
 * @brief   自检初始化
 */
void SelfCheckUsrGroupInit(void)
{
	// 用户组自检资源初始化

	S_Device* lpDev;
	StateDevicePointGet(&lpDev);

	S_Lcd__Item_Mid lTrig;

	lTrig.Item.Pos = CONFIG_USR_GROUP_POS;
	lTrig.Item.Char = lpDev->pConst->Version.Date;
	lTrig.Len = CONFIG_USR_GROUP_LEN;
	Lcd__FrameItemMidDisp(&lTrig);
}

