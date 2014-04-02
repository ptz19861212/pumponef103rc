/**
 * @file    self_check_cali_time.c
 * @brief   校准时间自检
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

#include "self_check_cali_time_in.h"

// 校准时间自检的自检项 英文
const char *sSelfCheckCaliTimeTxtEn[] =
{
		"Cali Time",
		"",
};

// 校准时间自检的自检项 中文
const char *sSelfCheckCaliTimeTxtCn[] =
{
		"校准时间",
		"",
};

// 校准时间自检的自检项 指针数组
const char **sSelfCheckCaliTimeTxt[] =
{
		sSelfCheckCaliTimeTxtEn,
		sSelfCheckCaliTimeTxtCn,
};


// 校准时间自检的下一个自检资源
const struct S_SelfCheckResource* sSelfCheckRsrCaliTimeNext =
											&gSelfCheckRsrCaliTime;

// 校准时间自检 资源，包括自身字符串，自检项字符串，自检项的数目
const struct S_SelfCheckResource gSelfCheckRsrCaliTime =
{
		SELF_CHECK_RESOURCE(CALI_TIME, CaliTime, AlarmUpper)
};


/**
 * @brief   自检初始化
 */
void SelfCheckCaliTimeInit(void)
{
	// 校准时间自检资源初始化

	S_Device* lpDev;
	StateDevicePointGet(&lpDev);

	S_Lcd__Item_Mid lTrig;

	lTrig.Item.Pos = CONFIG_CALI_TIME_POS;
	lTrig.Item.Char = lpDev->pConst->Version.Date;
	lTrig.Len = CONFIG_CALI_TIME_LEN;
	Lcd__FrameItemMidDisp(&lTrig);
}

