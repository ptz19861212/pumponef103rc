/**
 * @file    bsp_pump.c
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

#include "bsp_pump_in.h"

/**
 * @brief   泵打开
 */
void PumpOn(void)
{
	PUMP_On();
}


/**
 * @brief   泵关闭
 */
void PumpOff(void)
{
	PUMP_Off();
}


/**
 * @brief   泵初始化
 */
void PumpInit(void)
{
	PUMP_Init();
}

