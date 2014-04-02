/**
 * @file    self_check_in.h
 * @brief   自检 框架内含头文件
 * @author  ptz
 * @email   ptz19861212@163.com
 * @version 0.0.1
 * @date    2013-12-01 18:53:28 星期日 
 * @history (1).2013-12-01 18:53:28 星期日 create
 */
/* Copyright (C)
 * 
 * My own license
 * All right reserved
 * 
 */

#ifndef __SELF_CHECK_IN_H__
#define __SELF_CHECK_IN_H__

#include "stm32f10x.h"
#include "self_check.h"
#include "my_define.h"
#include "my_language.h"
#include "my_display.h"
#include "string.h"
#include "self_check_root.h"
#include "self_check_tab.h"
//#include "num_to_str.h"
//#include "key.h"
//#include "gas_alarm_get.h"
#include "my_math.h"
//#include "my_menu.h"

/****************************** 自检边框 *******************************/
// 起点
#define CONFIG_SELF_CHECK_FRAME_X_START				0
#define CONFIG_SELF_CHECK_FRAME_X_END				127
#define CONFIG_SELF_CHECK_FRAME_Y_START				11
#define CONFIG_SELF_CHECK_FRAME_Y_END				49
// 框架阴影
#define CONFIG_SELF_CHECK_FRAME_EX_X					3
#define CONFIG_SELF_CHECK_FRAME_EX_Y					3


/******************************** 屏幕自检选项 **************************/
// 屏幕输入选项长度
#define CONFIG_SELF_CHECK_LEN					15
// 屏幕输入第一行位置(以半行为单位)
//#define CONFIG_SELF_CHECK_POS					1
// 屏幕输入第一行位置(以行为单位)
#define CONFIG_SELF_CHECK_POS				1



typedef struct
{
	// 当前的自检索引
	self_check_t Index;
	// 当前的根据语言决定的自检标题数组
	const char **Text;
	// 自检资源
	const struct S_SelfCheckResource* SelfCheckRsr;
}S_SelfCheckFrame;



#endif
