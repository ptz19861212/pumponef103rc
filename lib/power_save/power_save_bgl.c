/**
 * @file    power_save_bgl.c
 * @brief   
 * @author  ptz
 * @email   ptz19861212@163.com
 * @version 0.0.1
 * @date    2014-01-24 13:02:35 星期五 
 * @history (1).2014-01-24 13:02:35 星期五 create
 */
/* Copyright (C)
 * 
 * My own license
 * All right reserved
 * 
 */

#include "power_save_bgl_in.h"


static uint8_t sPwrSvBglCount;
static my_second_t sPwrSvBglSecond;



/**
 * @brief   省电的背光倒计时
 */
void PowerSaveBglCountdown(void)
{
	S_Device* lpDev;
	StateDevicePointGet(&lpDev);

	// 为了整秒
	if (lpDev->pTemp->Time.Count != sPwrSvBglCount)
	{
		return;
	}

	if (lpDev->pTemp->Time.Sec > (sPwrSvBglSecond +
							CONFIG_POWER_SAVE_BGL_SECOND))
	{
		DisBgOff();
	}
}


/**
 * @brief   省电的背光刷新
 */
void PowerSaveBglFresh(void)
{
	S_Device* lpDev;
	StateDevicePointGet(&lpDev);

	sPwrSvBglCount = lpDev->pTemp->Time.Count;
	sPwrSvBglSecond = lpDev->pTemp->Time.Sec;

	DisBgOn();

//	rt_kprintf("-----\n");
}
