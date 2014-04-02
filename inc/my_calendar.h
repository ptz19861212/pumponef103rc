/**
 * @file    my_calendar.h
 * @brief   
 * @author  ptz
 * @email   ptz19861212@163.com
 * @version 0.0.1
 * @date    2014-01-22 15:39:30 星期三 
 * @history (1).2014-01-22 15:39:30 星期三 create
 */
/* Copyright (C)
 * 
 * My own license
 * All right reserved
 * 
 */

#ifndef __MY_CALENDAR_H__
#define __MY_CALENDAR_H__

#include <stdint.h>

typedef struct
{
	// 月
	uint8_t Mon;
	// 日
	uint8_t Day;
	// 年
	uint16_t Year;
}S_Calendar_Date;


typedef struct
{
	// 时
	uint8_t Hour;
	// 分
	uint8_t Min;
	// 秒
	uint8_t Sec;
}S_Calendar_Time;


#endif
