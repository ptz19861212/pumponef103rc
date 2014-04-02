/**
 * @file    state_detect_in.h
 * @brief   检测状态内部头文件
 * @author  ptz
 * @email   ptz19861212@163.com
 * @version 0.0.1
 * @date    2013-12-22 07:50:05 星期日 
 * @history (1).2013-12-22 07:50:05 星期日 create
 */
/* Copyright (C)
 * 
 * My own license
 * All right reserved
 * 
 */

#ifndef __STATE_DETECT_IN_H__
#define __STATE_DETECT_IN_H__

#include "display_uc1701.h"
#include "state.h"
#include "key.h"
#include "state_detect.h"
#include "gas_value_get.h"
#include "gas_alarm_get.h"
#include "bsp_buzzer.h"
#include "bsp_vibration.h"
#include "bsp_source.h"
#include "state_shutdown.h"
#include "my_language.h"
#include "state_info.h"

// 显示气体浓度的位置
#define CONFIG_DETECT_VALUE_DISP_X					0
#define CONFIG_DETECT_VALUE_DISP_Y					16
#define CONFIG_DETECT_VALUE_DISP_LEN				6
#define CONFIG_DETECT_VALUE_DISP_END_X				\
											(0 + 16 * CONFIG_DETECT_VALUE_DISP_LEN)
#define CONFIG_DETECT_VALUE_DISP_END_Y				(16 + 32)
// 显示报警状态的位置
#define CONFIG_DETECT_ALARM_DISP_X					52
#define CONFIG_DETECT_ALARM_DISP_Y					0
// 显示单位的位置
#define CONFIG_DETECT_UNIT_DISP_X					95
#define CONFIG_DETECT_UNIT_DISP_Y					32
// 显示名称的位置
#define CONFIG_DETECT_NAME_DISP_X					0
#define CONFIG_DETECT_NAME_DISP_Y					48
// 显示状态的位置
//#define CONFIG_DETECT_STATE_DISP_X					80
#define CONFIG_DETECT_STATE_DISP_X					64
#define CONFIG_DETECT_STATE_DISP_Y					48
// 显示错误的位置
#define CONFIG_DETECT_ERROR_DISP_X					0
#define CONFIG_DETECT_ERROR_DISP_Y					0
#define CONFIG_DETECT_ERROR_DISP_END_X				12
#define CONFIG_DETECT_ERROR_DISP_END_Y				9
// 显示风扇的位置
#define CONFIG_DETECT_FAN_DISP_X					86
#define CONFIG_DETECT_FAN_DISP_Y					0
// 显示充电的位置
#define CONFIG_DETECT_CHARGE_DISP_X				124
#define CONFIG_DETECT_CHARGE_DISP_Y				0
// 显示电池的位置
#define CONFIG_DETECT_BAT_DISP_X					107
#define CONFIG_DETECT_BAT_DISP_Y					0

#endif
