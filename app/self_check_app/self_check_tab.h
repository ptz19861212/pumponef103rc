/**
 * @file    self_check_tab.h
 * @brief   自检 头文件
 * @author  ptz
 * @email   ptz19861212@163.com
 * @version 0.0.1
 * @date    2013-12-02 13:35:28 星期一 
 * @history (1).2013-12-02 13:35:28 星期一 create
 */
/* Copyright (C)
 * 
 * My own license
 * All right reserved
 * 
 */

#ifndef __SELF_CHECK_TAB_H__
#define __SELF_CHECK_TAB_H__

#include "self_check.h"

// 自检对应的按键函数
extern const S_SelfCheckTab gSelfCheckTab[];


/******************* 自检索引配置 ****************************/
// 根自检的索引
#define SELF_CHECK_ROOT_INDEX					0
#define SELF_CHECK_SAMPLE_INDEX					1
#define SELF_CHECK_VERSION_INDEX					2
#define SELF_CHECK_BUILD_DATE_INDEX					3
#define SELF_CHECK_BUILD_TIME_INDEX					4
#define SELF_CHECK_MANF_DATE_INDEX					5
#define SELF_CHECK_WARRANTY_DATE_INDEX					6
#define SELF_CHECK_GAS_NAME_INDEX					7
#define SELF_CHECK_CALI_DATE_INDEX					8
#define SELF_CHECK_CALI_TIME_INDEX					9
#define SELF_CHECK_ALARM_UPPER_INDEX					10
#define SELF_CHECK_ALARM_LOWER_INDEX					11
#define SELF_CHECK_ALARM_STEL_INDEX					12
#define SELF_CHECK_ALARM_TWA_INDEX					13
#define SELF_CHECK_ALARM_SOUND_INDEX					14
#define SELF_CHECK_ALARM_VIBRATION_INDEX					15
#define SELF_CHECK_USR_GROUP_INDEX					16
#define SELF_CHECK_END_INDEX					17
#define SELF_CHECK_GAS_RANGE_INDEX					18



#endif
