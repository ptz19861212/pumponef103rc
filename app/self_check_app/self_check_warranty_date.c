/**
 * @file    self_check_warranty_date.c
 * @brief   质保日期自检
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

#include "self_check_warranty_date_in.h"

// 质保日期自检的自检项 英文
const char *sSelfCheckWarrantyDateTxtEn[] =
{
		"Warranty Date",
		"",
};

// 质保日期自检的自检项 中文
const char *sSelfCheckWarrantyDateTxtCn[] =
{
		"质保日期",
		"",
};

// 质保日期自检的自检项 指针数组
const char **sSelfCheckWarrantyDateTxt[] =
{
		sSelfCheckWarrantyDateTxtEn,
		sSelfCheckWarrantyDateTxtCn,
};


// 质保日期自检的下一个自检资源
const struct S_SelfCheckResource* sSelfCheckRsrWarrantyDateNext =
											&gSelfCheckRsrWarrantyDate;

// 质保日期自检 资源，包括自身字符串，自检项字符串，自检项的数目
const struct S_SelfCheckResource gSelfCheckRsrWarrantyDate =
{
		SELF_CHECK_RESOURCE(WARRANTY_DATE, WarrantyDate, GasName)
};


/**
 * @brief   自检初始化
 */
void SelfCheckWarrantyDateInit(void)
{
	// 质保日期自检资源初始化

	S_Device* lpDev;
	StateDevicePointGet(&lpDev);

	S_Lcd__Item_Mid lTrig;

	lTrig.Item.Pos = CONFIG_WARRANTY_DATE_POS;
	lTrig.Item.Char = lpDev->pConst->Version.Date;
	lTrig.Len = CONFIG_WARRANTY_DATE_LEN;
	Lcd__FrameItemMidDisp(&lTrig);
}

