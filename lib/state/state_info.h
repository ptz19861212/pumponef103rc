/**
 * @file    state_info.h
 * @brief   提示
 * @author  ptz
 * @email   ptz19861212@163.com
 * @version 0.0.1
 * @date    2014-01-14 16:43:40 星期二 
 * @history (1).2014-01-14 16:43:40 星期二 create
 */
/* Copyright (C)
 * 
 * My own license
 * All right reserved
 * 
 */

#ifndef __STATE_INFO_H__
#define __STATE_INFO_H__

/****************************** 数值输入 *********************************************/
//typedef void (*FUNC_STATE_INFO_GET)
//								(S_Value_U16* lpValue);
//
//typedef void (*FUNC_STATE_INFO_SET)
//								(S_Value_U16* lpValue);

typedef struct
{
	// 获得数值函数
//	MY_FUNC Get;
	// 设置数值函数
//	MY_FUNC Set;
	// 获得ADC的数值函数
//	FUNC_STATE_INFO_GET ValueGet;
	// 传递ADC进行求和的数值函数
//	FUNC_STATE_INFO_SET ValueSet;
	// 数值计算的函数
//	MY_FUNC ValueCalcu;
//	MY_FUNC Info;
	// 保存数值函数
//	MY_FUNC Save;
}S_InfoFunction;

typedef struct
{
	// 提示的信息
	const char* Info;
	// 提示秒
	uint8_t Time;
	// 输入数值函数
//	S_InfoFunction Func;
}S_Info;


/**
 * @brief   获得提示外部输入结构体指针
 *
 * @return
 */
S_Info* StateInfoPointGet(void);


/**
 * @brief   菜单项提示的初始显示，包括数值本身的显示
 *
 * @param   lpInput
 */
void StateInfoInit(void);


/**
 * @brief   按键 调用函数
 */
void StateInfoKey(uint8_t lKey);

//
//#define STATE_INFO_INDEX				0
//#define STATE_INFO_ZERO_INDEX				0
//#define STATE_INFO_COEFF_INDEX			1

#endif
