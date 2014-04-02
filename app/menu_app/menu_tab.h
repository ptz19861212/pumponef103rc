/**
 * @file    menu_tab.h
 * @brief   菜单 头文件
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

#ifndef __MENU_TAB_H__
#define __MENU_TAB_H__

#include "menu_frame.h"

// 菜单对应的按键函数
extern const S_MenuTab gMenuTab[];


/******************* 菜单索引配置 ****************************/
// 根菜单的索引
#define MENU_ROOT_INDEX					0
#define MENU_PARAM_INDEX					1
#define MENU_CALI_INDEX					2
#define MENU_TIME_INDEX					3
#define MENU_RESTORE_INDEX				4
#define MENU_MANUF_INDEX					5
#define MENU_DEBUG_INDEX					6
#define MENU_USER_INDEX					7
#define MENU_PARAM_ALARM_INDEX			8
#define MENU_PARAM_UPPER_INDEX			9
#define MENU_PARAM_LOWER_INDEX			10
#define MENU_PARAM_STEL_INDEX			11
#define MENU_PARAM_TWA_INDEX			12
#define MENU_PARAM_PUMP_INDEX			13
#define MENU_PARAM_BAK_INDEX			14
#define MENU_CALI_ZERO_INDEX			15
#define MENU_CALI_COEFF_INDEX				16
#define MENU_RST_PARAM_INDEX			17
#define MENU_RST_CALI_INDEX				18
#define MENU_DEBUG_ZERO_INDEX			19
#define MENU_DEBUG_COEFF_INDEX			20
#define MENU_DEBUG_REF1_INDEX			21
#define MENU_DEBUG_REF2_INDEX			22
#define MENU_DEBUG_BUILD_INDEX			23
#define MENU_USER_GROUP_INDEX			24
#define MENU_USER_UPGRADE_INDEX			25
#define MENU_USER_DEGRADE_INDEX			26
#define MENU_PARAM_ALARM_SOUND_INDEX				27
#define MENU_PARAM_ALARM_VIBRATION_INDEX			28
#define MENU_PARAM_LANGUAGE_INDEX		29


#endif
