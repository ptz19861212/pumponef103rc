/**
 * @file    bsp_charge.c
 * @brief   
 * @author  ptz
 * @email   ptz19861212@163.com
 * @version 0.0.1
 * @date    2014-01-23 15:24:29 星期四 
 * @history (1).2014-01-23 15:24:29 星期四 create
 */
/* Copyright (C)
 * 
 * My own license
 * All right reserved
 * 
 */

#include "bsp_charge_in.h"

/**
 * @brief   充电打开
 */
void ChargeOn(void)
{
	CHARGE_On();
}


/**
 * @brief   充电关闭
 */
void ChargeOff(void)
{
	CHARGE_Off();
}


/**
 * @brief   充电检测
 */
E_TrueState ChargeScan(void)
{
	return CHARGE_Scan();
}


/**
 * @brief   充电初始化
 */
void ChargeInit(void)
{
	CHARGE_Init();
}

