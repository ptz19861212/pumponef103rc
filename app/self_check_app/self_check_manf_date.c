/**
 * @file    self_check_manf_date.c
 * @brief   生产日期自检
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

#include "self_check_manf_date_in.h"

// 生产日期自检的自检项 英文
const char *sSelfCheckManfDateTxtEn[] =
{
		"Manf Date",
		"",
};

// 生产日期自检的自检项 中文
const char *sSelfCheckManfDateTxtCn[] =
{
		"生产日期",
		"",
};

// 生产日期自检的自检项 指针数组
const char **sSelfCheckManfDateTxt[] =
{
		sSelfCheckManfDateTxtEn,
		sSelfCheckManfDateTxtCn,
};


// 生产日期自检的下一个自检资源
const struct S_SelfCheckResource* sSelfCheckRsrManfDateNext =
											&gSelfCheckRsrManfDate;

// 生产日期自检 资源，包括自身字符串，自检项字符串，自检项的数目
const struct S_SelfCheckResource gSelfCheckRsrManfDate =
{
		SELF_CHECK_RESOURCE(MANF_DATE, ManfDate, WarrantyDate)
};


/**
 * @brief   自检初始化
 */
void SelfCheckManfDateInit(void)
{
	// 生产日期自检资源初始化

	S_Device* lpDev;
	StateDevicePointGet(&lpDev);

	S_Lcd__Item_Mid lTrig;

	lTrig.Item.Pos = CONFIG_MANF_DATE_POS;
	lTrig.Item.Char = lpDev->pConst->Version.Date;
	lTrig.Len = CONFIG_MANF_DATE_LEN;
	Lcd__FrameItemMidDisp(&lTrig);
}

