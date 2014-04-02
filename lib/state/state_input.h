/**
 * @file    state_input.h
 * @brief   
 * @author  ptz
 * @email   ptz19861212@163.com
 * @version 0.0.1
 * @date    2014-01-07 16:42:08 星期二 
 * @history (1).2014-01-07 16:42:08 星期二 create
 */
/* Copyright (C)
 * 
 * My own license
 * All right reserved
 * 
 */

#ifndef __STATE_INPUT_H__
#define __STATE_INPUT_H__

#include "my_gas.h"

/****************************** 数值输入 *********************************************/
typedef void (*FUNC_STATE_INPUT_VALUE_GET)(S_Value_U16* lpValue);
typedef void (*FUNC_STATE_INPUT_VALUE_CONFIRM)
												(E_TrueState lTrue);
typedef struct
{
	// 获得数值输入的上下限的函数，准备进入闪烁状态
	MY_FUNC LimitGet;
	// 设置数值的输入结束，退出闪烁函数
	MY_FUNC Set;
	// 获得保存的数值函数，刚刚进入时候，反显状态显示的数值
	FUNC_STATE_INPUT_VALUE_GET ValueGet;
	// 保存数值函数，当按下确认的时候把输入的数值进行保存
	MY_FUNC Save;
	// 确认函数，当按下按键的时候进行系统状态转换使用的函数
	FUNC_STATE_INPUT_VALUE_CONFIRM Confirm;
}S_InputValueFunction;

typedef struct
{
	// 输入的数值
//	S_Value_U16 Value;
	// 输入数值函数
	S_InputValueFunction Func;
}S_InputValue;


/**
 * @brief   菜单项最终处理显示，差不多全部显示，输入数值这个不显示
 */
void StateInputValueInit(S_InputValue* lValue);


/**
 * @brief   按键 调用函数
 */
void StateInputKey(uint8_t lKey);






/************************************** 开关输入 ***************************************/
typedef void (*FUNC_STATE_INPUT_BINARY_GET)(E_TurnState* lpState);
typedef void (*FUNC_STATE_INPUT_BINARY_SAVE)
												(E_TurnState lTurn);
typedef void (*FUNC_STATE_INPUT_BINARY_CONFIRM)
												(E_TurnState lTurn);

typedef struct
{
	// 获得数值函数
//	MY_FUNC Get;
	// 设置数值函数
//	MY_FUNC Set;
	// 获得保存的数值函数
	FUNC_STATE_INPUT_BINARY_GET BinaryGet;
	// 保存数值函数
	FUNC_STATE_INPUT_BINARY_SAVE Save;
	// 确认函数
	FUNC_STATE_INPUT_BINARY_CONFIRM Confirm;
}S_InputBinaryFunction;

typedef struct
{
	// 输入的数值
//	S_Value_U16 Value;
//	E_TurnState Binary;
	// 哪种二值，on/off, yes/no
	E_BinaryState State;
	// 是否能够进入相应的调用状态，主要用于调用标零和标气倒计时
//	E_TrueState Call;
	// 输入数值函数
	S_InputBinaryFunction Func;
}S_InputBinary;





// 使能字符串 指针数组
//extern const char **gInputOnOff[];
// 二值字符串 指针数组
extern const char ***gInputBinary[];


#define STATE_INPUT_VALUE_INDEX			0
#define STATE_INPUT_BINARY_INDEX			1


#endif
