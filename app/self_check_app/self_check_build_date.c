/**
 * @file    self_check_build_date.c
 * @brief   编译日期自检
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

#include "self_check_build_date_in.h"

// 编译日期自检的自检项 英文
const char *sSelfCheckBuildDateTxtEn[] =
{
		"Build Date",
		"",
};

// 编译日期自检的自检项 中文
const char *sSelfCheckBuildDateTxtCn[] =
{
		"编译日期",
		"",
};

// 编译日期自检的自检项 指针数组
const char **sSelfCheckBuildDateTxt[] =
{
		sSelfCheckBuildDateTxtEn,
		sSelfCheckBuildDateTxtCn,
};


// 编译日期自检的下一个自检资源
const struct S_SelfCheckResource* sSelfCheckRsrBuildDateNext =
											&gSelfCheckRsrBuildDate;

// 编译日期自检 资源，包括自身字符串，自检项字符串，自检项的数目
const struct S_SelfCheckResource gSelfCheckRsrBuildDate =
{
		SELF_CHECK_RESOURCE(BUILD_DATE, BuildDate, BuildTime)
};


/**
 * @brief   自检初始化
 */
void SelfCheckBuildDateInit(void)
{
	// 编译日期自检资源初始化

	S_Device* lpDev;
	StateDevicePointGet(&lpDev);

	S_Calendar_Date lDate;
	CalDateEnToNum(lpDev->pConst->Version.Date, &lDate);
	rt_kprintf("mon = %d\tday = %d\tyear = %d\n",
				lDate.Mon, lDate.Day, lDate.Year);

	char lArray[18];
	CalDateNumToCn(lArray, &lDate);
	rt_kprintf("date = %s\n", lArray);

	S_Lcd__Item_Mid lTrig;

	lTrig.Item.Pos = CONFIG_BUILD_DATE_POS;
//	lTrig.Item.Char = lpDev->pConst->Version.Date;
	lTrig.Item.Char = lArray;
	lTrig.Len = CONFIG_BUILD_DATE_LEN;
	Lcd__FrameItemMidDisp(&lTrig);
}

