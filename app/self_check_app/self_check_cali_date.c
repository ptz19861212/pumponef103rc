/**
 * @file    self_check_cali_date.c
 * @brief   校准日期自检
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

#include "self_check_cali_date_in.h"

// 校准日期自检的自检项 英文
const char *sSelfCheckCaliDateTxtEn[] =
{
		"Cali Date",
		"",
};

// 校准日期自检的自检项 中文
const char *sSelfCheckCaliDateTxtCn[] =
{
		"校准日期",
		"",
};

// 校准日期自检的自检项 指针数组
const char **sSelfCheckCaliDateTxt[] =
{
		sSelfCheckCaliDateTxtEn,
		sSelfCheckCaliDateTxtCn,
};


// 校准日期自检的下一个自检资源
const struct S_SelfCheckResource* sSelfCheckRsrCaliDateNext =
											&gSelfCheckRsrCaliDate;

// 校准日期自检 资源，包括自身字符串，自检项字符串，自检项的数目
const struct S_SelfCheckResource gSelfCheckRsrCaliDate =
{
		SELF_CHECK_RESOURCE(CALI_DATE, CaliDate, CaliTime)
};


/**
 * @brief   自检初始化
 */
void SelfCheckCaliDateInit(void)
{
	// 校准日期自检资源初始化

	S_Device* lpDev;
	StateDevicePointGet(&lpDev);

	S_Lcd__Item_Mid lTrig;

	lTrig.Item.Pos = CONFIG_CALI_DATE_POS;
	lTrig.Item.Char = lpDev->pConst->Version.Date;
	lTrig.Len = CONFIG_CALI_DATE_LEN;
	Lcd__FrameItemMidDisp(&lTrig);
}

