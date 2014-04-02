/**
 * @file    state_shutdown.h
 * @brief   关机
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

#ifndef __STATE_SHUTDOWN_H__
#define __STATE_SHUTDOWN_H__

/****************************** 数值输入 *********************************************/
//typedef void (*FUNC_STATE_SHUTDOWN_GET)
//								(S_Value_U16* lpValue);
//
//typedef void (*FUNC_STATE_SHUTDOWN_SET)
//								(S_Value_U16* lpValue);

typedef struct
{
	// 获得数值函数
//	MY_FUNC Get;
	// 设置数值函数
//	MY_FUNC Set;
	// 获得ADC的数值函数
//	FUNC_STATE_SHUTDOWN_GET ValueGet;
	// 传递ADC进行求和的数值函数
//	FUNC_STATE_SHUTDOWN_SET ValueSet;
	// 数值计算的函数
//	MY_FUNC ValueCalcu;
	MY_FUNC Shutdown;
	// 保存数值函数
//	MY_FUNC Save;
}S_ShutdownFunction;

typedef struct
{
	// 是否显示气体的AD数值
//	E_TrueState AD;
	// 标题栏，用于不显示AD数值的时候，显示标题
//	const char* Label;
	// 电量是否低
	E_TrueState BatLow;
	// 关机秒
	uint8_t Time;
	// 输入数值函数
	S_ShutdownFunction Func;
}S_Shutdown;


/**
 * @brief   获得关机外部输入结构体指针
 *
 * @return
 */
S_Shutdown* StateShutdownPointGet(void);


/**
 * @brief   菜单项关机的初始显示，包括数值本身的显示
 *
 * @param   lpInput
 */
void StateShutdownInit(void);


/**
 * @brief   按键 调用函数
 */
void StateShutdownKey(uint8_t lKey);

//
//#define STATE_SHUTDOWN_INDEX				0
//#define STATE_SHUTDOWN_ZERO_INDEX				0
//#define STATE_SHUTDOWN_COEFF_INDEX			1

#endif
