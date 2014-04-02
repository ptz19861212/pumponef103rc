/**
 * @file    state_input_in.h
 * @brief   
 * @author  ptz
 * @email   ptz19861212@163.com
 * @version 0.0.1
 * @date    2014-01-07 16:42:36 星期二 
 * @history (1).2014-01-07 16:42:36 星期二 create
 */
/* Copyright (C)
 * 
 * My own license
 * All right reserved
 * 
 */

#ifndef __STATE_INPUT_IN_H__
#define __STATE_INPUT_IN_H__

#include "state_input.h"
#include "display.h"
#include "my_math.h"
#include "key.h"

/************************************ 屏幕输入选项 *******************************/
// 屏幕输入选项长度
#define CONFIG_INPUT_LEN							15
// 屏幕输入第一行位置(以半行为单位)
#define CONFIG_INPUT_VALUE_POS					1
// 屏幕输入开关量第一行位置(以整行为单位)
#define CONFIG_INPUT_ONOFF_POS					1


/******************************** 输入数值的框架 *********************************/
// 起点
#define CONFIG_VALUE_FRAME_X_START				0
#define CONFIG_VALUE_FRAME_X_END				127
#define CONFIG_VALUE_FRAME_Y_START				3
#define CONFIG_VALUE_FRAME_Y_END				57
// 框架阴影
#define CONFIG_VALUE_FRAME_EX_X					3
#define CONFIG_VALUE_FRAME_EX_Y					3

typedef struct
{
	// 行下标
	my_lcd_t Index;
	// 行数目
	my_lcd_t Num;
	// 锁定行状态
	E_LockState Lock;
}S_StateLine;


typedef struct
{
	// 行相关
	S_StateLine Line;
	// 函数
	S_InputValueFunction Func;
}S_StateInputValue;





/******************************** 输入选择的框架 *********************************/
// 起点
#define CONFIG_BINARY_FRAME_X_START				0
#define CONFIG_BINARY_FRAME_X_END				127
#define CONFIG_BINARY_FRAME_Y_START				11
#define CONFIG_BINARY_FRAME_Y_END				49
// 框架阴影
#define CONFIG_BINARY_FRAME_EX_X					3
#define CONFIG_BINARY_FRAME_EX_Y					3


typedef struct
{
	// 行下标
	my_lcd_t Index;
	// 行数目
	my_lcd_t Num;
	// 调用函数行状态
	E_TrueState Call;
}S_InputBinaryLine;


typedef struct
{
	// 行相关
	S_InputBinaryLine Line;
	// 函数
	S_InputBinaryFunction Func;
}S_StateInputBinary;


// 输入框架 包括输入索引和输入资源
//struct S_MenuFrame
//{
//	// 当前的菜单状态机的状态数值，也就是在菜单数组中的索引下标
//	my_lcd_t InputIndex;
//	// 菜单项资源指针
//	const struct S_MenuResource *MenuRsr;
//};




// 用于菜单根据按键调用相应的菜单函数
typedef struct
{
	my_lcd_t InputIndex;
//	MY_FUNC Init;
	MY_FUNC Confirm;
	MY_FUNC Exit;
	MY_FUNC Down;
	MY_FUNC Up;
}S_State_Input_Tab;

// 生成按键函数表 StateInputValueInit
#define STATE_INPUT_KEY_TAB(TXT, Txt)		\
								{\
									STATE_INPUT_##TXT##_INDEX,\
									StateInput##Txt##Confirm,\
									StateInput##Txt##Exit,\
									StateInput##Txt##Down,\
									StateInput##Txt##Up,\
								}
//{\
//	STATE_INPUT_##TXT##_INDEX,\
//	StateInput##Txt##Init,\
//	StateInput##Txt##Confirm,\
//	StateInput##Txt##Cancel,\
//	StateInput##Txt##Next,\
//	StateInput##Txt##Prev,\
//}

// 菜单对应的按键函数
static const S_State_Input_Tab sStateInputTab[];

#endif
