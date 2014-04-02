/**
 * @file    bat_get.c
 * @brief   获得电池状态
 * @author  ptz
 * @email   ptz19861212@163.com
 * @version 0.0.1
 * @date    2013-12-26 09:40:45 星期四 
 * @history (1).2013-12-26 09:40:45 星期四 create
 */
/* Copyright (C)
 * 
 * My own license
 * All right reserved
 * 
 */

#include "bat_get_in.h"


/**
 * @brief   求电池容量，这个函数和显示无关的，直接求电池容量的确切的百分比。
 *
 * @param   lpDev 设备结构体地址
 */
void BatValueGet(S_Device* lpDev)
{
	uint16_t lAdc;
	uint32_t lProduct;

	lAdc = lpDev->pTemp->Bat.Point.Adc;

	if (lAdc < lpDev->pConst->Bat.Lv0.Adc)
	{
		lpDev->pTemp->Bat.Point.Value =
					lpDev->pConst->Bat.Lv0.Value;
	}
	else if (lAdc < lpDev->pConst->Bat.Lv20.Adc)
	{
		lProduct = lpDev->pConst->Bat.Lv20.Value -
						lpDev->pConst->Bat.Lv0.Value;
		lProduct *= lAdc - lpDev->pConst->Bat.Lv0.Adc;
		lpDev->pTemp->Bat.Point.Value =
			(lProduct /
				(lpDev->pConst->Bat.Lv20.Adc -
						lpDev->pConst->Bat.Lv0.Adc)) +
			lpDev->pConst->Bat.Lv0.Value;
	}
	else if (lAdc < lpDev->pConst->Bat.Lv40.Adc)
	{
		lProduct = lpDev->pConst->Bat.Lv40.Value -
						lpDev->pConst->Bat.Lv20.Value;
		lProduct *= lAdc - lpDev->pConst->Bat.Lv20.Adc;
		lpDev->pTemp->Bat.Point.Value =
			(lProduct /
				(lpDev->pConst->Bat.Lv40.Adc - lpDev->pConst->Bat.Lv20.Adc)) +
			lpDev->pConst->Bat.Lv20.Value;
	}
	else if (lAdc < lpDev->pConst->Bat.Lv60.Adc)
	{
		lProduct = lpDev->pConst->Bat.Lv60.Value -
						lpDev->pConst->Bat.Lv40.Value;
		lProduct *= lAdc - lpDev->pConst->Bat.Lv40.Adc;
		lpDev->pTemp->Bat.Point.Value =
			(lProduct /
				(lpDev->pConst->Bat.Lv60.Adc - lpDev->pConst->Bat.Lv40.Adc)) +
			lpDev->pConst->Bat.Lv40.Value;
	}
	else if (lAdc < lpDev->pConst->Bat.Lv80.Adc)
	{
		lProduct = lpDev->pConst->Bat.Lv80.Value -
						lpDev->pConst->Bat.Lv60.Value;
		lProduct *= lAdc - lpDev->pConst->Bat.Lv60.Adc;
		lpDev->pTemp->Bat.Point.Value =
			(lProduct /
				(lpDev->pConst->Bat.Lv80.Adc - lpDev->pConst->Bat.Lv60.Adc)) +
			lpDev->pConst->Bat.Lv60.Value;
	}
	else if (lAdc < lpDev->pConst->Bat.Lv100.Adc)
	{
		lProduct = lpDev->pConst->Bat.Lv100.Value -
						lpDev->pConst->Bat.Lv80.Value;
		lProduct *= lAdc - lpDev->pConst->Bat.Lv80.Adc;
		lpDev->pTemp->Bat.Point.Value =
			(lProduct /
				(lpDev->pConst->Bat.Lv100.Adc - lpDev->pConst->Bat.Lv80.Adc)) +
			lpDev->pConst->Bat.Lv80.Value;
	}
	else
	{
		lpDev->pTemp->Bat.Point.Value = lpDev->pConst->Bat.Lv100.Value;
	}
}


/**
 * @brief   求电池容量等级，这个函数是和显示相关的，显示电池容量的等级
 *
 * @param   lpDev 设备结构体地址
 */
//void BatLevelGet(struct S_Device* lpDev)
//{
//	uint8_t lValue;
//
//	lValue = lpDev->pTemp->Bat.Point.Value;
//
//	if (lValue >= DIS_SYM_BAT_100)
//	{
//		lpDev->pTemp->Bat.Lv = DIS_SYM_BAT_100;
//	}
//	else if (lValue >= DIS_SYM_BAT_80)
//	{
//		lpDev->pTemp->Bat.Lv = DIS_SYM_BAT_80;
//	}
//	else if (lValue >= DIS_SYM_BAT_60)
//	{
//		lpDev->pTemp->Bat.Lv = DIS_SYM_BAT_60;
//	}
//	else if (lValue >= DIS_SYM_BAT_40)
//	{
//		lpDev->pTemp->Bat.Lv = DIS_SYM_BAT_40;
//	}
//	else if (lValue >= DIS_SYM_BAT_20)
//	{
//		lpDev->pTemp->Bat.Lv = DIS_SYM_BAT_20;
//	}
//	else
//	{
//		lpDev->pTemp->Bat.Lv = DIS_SYM_BAT_NONE;
//	}
//}
