/**
 * @file    state_info_in.h
 * @brief   提示内部头文件
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

#ifndef __STATE_INFO_IN_H__
#define __STATE_INFO_IN_H__


#include "display.h"
#include "my_math.h"
#include "key.h"
#include "state_info.h"
#include "my_gas.h"
#include "my_device.h"
#include "my_bsp.h"


/******************************** 屏幕输入选项 **************************/
// 屏幕输入选项长度
#define CONFIG_INFO_LEN					15
// 屏幕输入第一行位置(以半行为单位)
#define CONFIG_INFO_POS					3


/*************************** 输入数值的框架 *****************************/
// 起点
#define CONFIG_INFO_FRAME_X_START				0
#define CONFIG_INFO_FRAME_X_END				127
#define CONFIG_INFO_FRAME_Y_START				19
#define CONFIG_INFO_FRAME_Y_END				41
// 框架阴影
#define CONFIG_INFO_FRAME_EX_X					3
#define CONFIG_INFO_FRAME_EX_Y					3

typedef struct
{
	// 行下标
	my_lcd_t Index;
	// 行数目
	my_lcd_t Num;
}S_InfoLine;

typedef struct
{
	// 行相关
	S_InfoLine Line;
	// 给外部使用的部分结构体
	S_Info Out;
	// 显示倒计时结束
//	E_TrueState DispEnd;
}S_StateInfo;



// 用于菜单根据按键调用相应的菜单函数
typedef struct
{
	my_lcd_t Index;
//	MY_FUNC Init;
	MY_FUNC Confirm;
}S_Info_Tab;



// 生成按键函数表 StateInputValueInit
#define STATE_INFO_KEY_TAB(TXT, Txt)		\
								{\
									STATE_INFO_##TXT##_INDEX,\
									StateInfo##Txt##Confirm,\
								}



// 菜单对应的按键函数
static const S_Info_Tab sInfoTab[];


#endif
