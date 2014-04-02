/**
 * @file    state_result_in.h
 * @brief   
 * @author  ptz
 * @email   ptz19861212@163.com
 * @version 0.0.1
 * @date    2014-01-16 07:29:35 星期四 
 * @history (1).2014-01-16 07:29:35 星期四 create
 */
/* Copyright (C)
 * 
 * My own license
 * All right reserved
 * 
 */

#ifndef __STATE_RESULT_IN_H__
#define __STATE_RESULT_IN_H__


#include "state_result.h"
#include "display.h"
#include "my_math.h"
#include "key.h"
#include "my_gas.h"
#include "my_device.h"


/******************************** 屏幕输入选项 **************************/
// 屏幕输入选项长度
#define CONFIG_RESULT_LEN					15
// 屏幕输入第一行位置(以半行为单位)
#define CONFIG_RESULT_ERROR_POS					1
// 屏幕输入第一行位置(以行为单位)
#define CONFIG_RESULT_SUCCESS_POS				1


/*************************** 输入数值的框架 *****************************/
// 起点
#define CONFIG_RESULT_ERROR_FRAME_X_START				0
#define CONFIG_RESULT_ERROR_FRAME_X_END				127
#define CONFIG_RESULT_ERROR_FRAME_Y_START				3
#define CONFIG_RESULT_ERROR_FRAME_Y_END				57
// 框架阴影
#define CONFIG_RESULT_ERROR_FRAME_EX_X					3
#define CONFIG_RESULT_ERROR_FRAME_EX_Y					3

// 起点
#define CONFIG_RESULT_SUCCESS_FRAME_X_START				0
#define CONFIG_RESULT_SUCCESS_FRAME_X_END				127
#define CONFIG_RESULT_SUCCESS_FRAME_Y_START				11
#define CONFIG_RESULT_SUCCESS_FRAME_Y_END				49
// 框架阴影
#define CONFIG_RESULT_SUCCESS_FRAME_EX_X					3
#define CONFIG_RESULT_SUCCESS_FRAME_EX_Y					3

typedef struct
{
	// 行下标
	my_lcd_t Index;
	// 行数目
	my_lcd_t Num;
}S_ResultLine;

typedef struct
{
	// 行相关
	S_ResultLine Line;
	// 给外部使用的部分结构体
	S_ResultError Out;
}S_StateResultError;


typedef struct
{
	// 行相关
	S_ResultLine Line;
	// 给外部使用的部分结构体
	S_ResultSuccess Out;
}S_StateResultSuccess;



// 用于菜单根据按键调用相应的菜单函数
typedef struct
{
	my_lcd_t Index;
//	MY_FUNC Init;
	MY_FUNC Confirm;
}S_Result_Tab;



// 生成按键函数表 StateInputValueInit
#define STATE_RESULT_KEY_TAB(TXT, Txt)		\
								{\
									STATE_RESULT_##TXT##_INDEX,\
									StateResult##Txt##Confirm,\
								}



// 菜单对应的按键函数
static const S_Result_Tab sResultTab[];


#endif
