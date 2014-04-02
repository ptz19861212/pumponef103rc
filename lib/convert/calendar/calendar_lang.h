/**
 * @file    calendar_lang.h
 * @brief   
 * @author  ptz
 * @email   ptz19861212@163.com
 * @version 0.0.1
 * @date    2014-01-22 15:37:07 星期三 
 * @history (1).2014-01-22 15:37:07 星期三 create
 */
/* Copyright (C)
 * 
 * My own license
 * All right reserved
 * 
 */

#ifndef __CALENDAR_LANG_H__
#define __CALENDAR_LANG_H__

#include "my_calendar.h"

/**
 * @brief   把英文的日期转换为数字
 */
void CalDateEnToNum(const char* lpEn, S_Calendar_Date* lpDate);


/**
 * @brief   把日期转换为中文
 *
 * @param   lpCn 中文的日历地址
 * @param   lpDate 数字的日历地址
 */
void CalDateNumToCn(char* lpCn, S_Calendar_Date* lpDate);


#endif
