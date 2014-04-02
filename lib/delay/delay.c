/**
 * @file    delay.c
 * @brief   软件延时
 * @author  ptz
 * @email   ptz19861212@163.com
 * @version 0.0.1
 * @date    2013-12-03 14:23:39 星期二 
 * @history (1).2013-12-03 14:23:39 星期二 create
 */
/* Copyright (C)
 * 
 * My own license
 * All right reserved
 * 
 */

#include "delay_in.h"


/**
 * @brief   微妙延时
 */
void DelayUs(uint16_t time)
{
	uint16_t i=0;
	while(time--)
	{
		i=10;  //尹工用的17
		while(i--);
	}
}


/**
 * @brief   毫秒延时
 */
void DelayMs(uint16_t time)
{
	uint16_t i=0;
	while(time--)
	{
		i=12000;  //尹工用的18000
		while(i--);
	}
}
