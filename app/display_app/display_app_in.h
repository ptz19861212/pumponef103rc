/**
 * @file    display_app_in.h
 * @brief   
 * @author  ptz
 * @email   ptz19861212@163.com
 * @version 0.0.1
 * @date    2014-01-06 17:08:57 星期一 
 * @history (1).2014-01-06 17:08:57 星期一 create
 */
/* Copyright (C)
 * 
 * My own license
 * All right reserved
 * 
 */


#ifndef __DISPLAY_APP_IN_H__
#define __DISPLAY_APP_IN_H__

#include "my_display.h"
#include "font_symbol.h"
#include "display_app.h"
#include "my_device.h"

/************************************ 风扇图标 ************************************/
// 风扇位置
#define CONFIG_FAN_X							86
#define CONFIG_FAN_Y							0

/************************************ 充电图标 ************************************/
// 风扇位置
#define CONFIG_CHARGE_X							124
#define CONFIG_CHARGE_Y							0

/********************************** 大号关机充电图标 **********************************/
// 风扇位置
#define CONFIG_CHARGE_LARGE_X					47
#define CONFIG_CHARGE_LARGE_Y					24

/********************************** 大号关机充满图标 **********************************/
// 风扇位置
#define CONFIG_CHARGE_FULL_LARGE_X					55
#define CONFIG_CHARGE_FULL_LARGE_Y					20

/************************************ 电池图标 ************************************/
// 风扇位置
#define CONFIG_BAT_X							107
#define CONFIG_BAT_Y							0



// 显示左上角电池状态
#define DIS_SYM_BAT_NONE				0
#define DIS_SYM_BAT_5					5
#define DIS_SYM_BAT_20					20
#define DIS_SYM_BAT_40					40
#define DIS_SYM_BAT_60					60
#define DIS_SYM_BAT_80					80
#define DIS_SYM_BAT_100					100
#define DIS_SYM_BAT_FULL				0xFF

typedef enum {
					BAT_NONE = 0,
					BAT_20 = 1,
					BAT_40 = 2,
					BAT_60 = 3,
					BAT_80 = 4,
					BAT_100 = 5,
					BAT_FULL = 6,
}E_BatState;

#endif
