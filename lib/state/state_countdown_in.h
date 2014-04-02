/**
 * @file    state_countdown_in.h
 * @brief   倒计时内部头文件
 * @author  ptz
 * @email   ptz19861212@163.com
 * @version 0.0.1
 * @date    2014-01-14 16:44:15 星期二 
 * @history (1).2014-01-14 16:44:15 星期二 create
 */
/* Copyright (C)
 * 
 * My own license
 * All right reserved
 * 
 */

#ifndef __STATE_COUNTDOWN_IN_H__
#define __STATE_COUNTDOWN_IN_H__


#include "display.h"
#include "my_math.h"
#include "key.h"
#include "state_countdown.h"
#include "my_gas.h"
#include "my_device.h"


/******************************** 屏幕输入选项 **************************/
// 屏幕输入选项长度
#define CONFIG_COUNTDOWN_LEN					15
// 屏幕输入第一行位置(以半行为单位)
#define CONFIG_COUNTDOWN_POS					1


/*************************** 输入数值的框架 *****************************/
// 起点
#define CONFIG_COUNTDOWN_FRAME_X_START				0
#define CONFIG_COUNTDOWN_FRAME_X_END				127
#define CONFIG_COUNTDOWN_FRAME_Y_START				3
#define CONFIG_COUNTDOWN_FRAME_Y_END				57
// 框架阴影
#define CONFIG_COUNTDOWN_FRAME_EX_X					3
#define CONFIG_COUNTDOWN_FRAME_EX_Y					3

typedef struct
{
	// 行下标
	my_lcd_t Index;
	// 行数目
	my_lcd_t Num;
}S_CountdownLine;

typedef struct
{
	// 行相关
	S_CountdownLine Line;
	// 给外部使用的部分结构体
	S_Countdown Out;
}S_StateCountdown;



// 用于菜单根据按键调用相应的菜单函数
typedef struct
{
	my_lcd_t Index;
//	MY_FUNC Init;
	MY_FUNC Confirm;
}S_Countdown_Tab;



// 生成按键函数表 StateInputValueInit
#define STATE_COUNTDOWN_KEY_TAB(TXT, Txt)		\
								{\
									STATE_COUNTDOWN_##TXT##_INDEX,\
									StateCountdown##Txt##Confirm,\
								}



// 菜单对应的按键函数
static const S_Countdown_Tab sCountdownTab[];


#endif
