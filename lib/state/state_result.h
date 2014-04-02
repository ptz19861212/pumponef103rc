/**
 * @file    state_result.h
 * @brief   
 * @author  ptz
 * @email   ptz19861212@163.com
 * @version 0.0.1
 * @date    2014-01-16 07:29:03 星期四 
 * @history (1).2014-01-16 07:29:03 星期四 create
 */
/* Copyright (C)
 * 
 * My own license
 * All right reserved
 * 
 */

#ifndef __STATE_RESULT_H__
#define __STATE_RESULT_H__

#include "my_error.h"
#include "my_num.h"
#include "my_define.h"

/****************************** 数值输入 *********************************************/
//typedef void (*FUNC_STATE_RESULT_GET)
//								(S_Value_U16* lpValue);

//typedef void (*FUNC_STATE_RESULT_SET)
//								(S_Value_U16* lpValue);

typedef struct
{
	// 获得数值函数
//	MY_FUNC Get;
	// 设置数值函数
//	MY_FUNC Set;
	// 获得ADC的数值函数
	// 获得出错的时候具体数据是多少
//	FUNC_STATE_RESULT_GET ValueGet;
	// 传递ADC进行求和的数值函数
//	FUNC_STATE_RESULT_SET ValueSet;
	// 数值计算的函数
//	MY_FUNC ValueCalcu;
	// 保存数值函数
//	MY_FUNC Save;
}S_ResultFunction;

typedef struct
{
	// 是否显示气体的AD数值
	E_TrueState AD;
	// 标题栏，用于不显示AD数值的时候，显示标题
//	const char* Label;
	// 倒计时秒
//	uint8_t Time;
	// 标零或者标气的实际数值，不用函数，因为函数都是实时的数值，这边
	// 显示的是刚才计算完成的数值
	S_Value_U16 Value;
	// 出错号
	E_ErrorState ErrNum;
	// 输入数值函数
	S_ResultFunction Func;
}S_ResultError;


typedef struct
{
	// 是否显示气体的AD数值
	E_TrueState AD;
	// 标零或者标气的实际数值，不用函数，因为函数都是实时的数值，这边
	// 显示的是刚才计算完成的数值
	S_Value_U16 Value;
	// 输入数值函数
	S_ResultFunction Func;
}S_ResultSuccess;


/**
 * @brief   获得出错外部输入结构体指针
 *
 * @return
 */
S_ResultError* StateResultErrorPointGet(void);


/**
 * @brief   菜单项倒计时的初始显示，包括数值本身的显示
 *
 * @param   lpResult
 */
void StateResultErrorInit(void);


/**
 * @brief   获得成功外部输入结构体指针
 *
 * @return
 */
S_ResultSuccess* StateResultSuccessPointGet(void);


/**
 * @brief   菜单项倒计时的初始显示，包括数值本身的显示
 *
 * @param   lpResult
 */
void StateResultSuccessInit(void);


/**
 * @brief   按键 调用函数
 */
void StateResultKey(uint8_t lKey);


#define STATE_RESULT_ERROR_INDEX				0
#define STATE_RESULT_SUCCESS_INDEX				1
//#define STATE_RESULT_ZERO_INDEX				0
//#define STATE_RESULT_COEFF_INDEX			1

#endif
