/**
 * @file    menu_param_alarm_vibration.h
 * @brief   菜单 头文件
 * @author  ptz
 * @email   ptz19861212@163.com
 * @version 0.0.1
 * @date    2013-12-02 13:35:28 星期一 
 * @history (1).2013-12-02 13:35:28 星期一 create
 */
/* Copyright (C)
 * 
 * My own license
 * All right reserved
 * 
 */

#ifndef __MENU_PARAM_ALARM_VIBRATION_H__
#define __MENU_PARAM_ALARM_VIBRATION_H__

/**
 * @brief   菜单初始化
 */
void MenuParamAlarmVibrationPreInit(void);


/**
 * @brief   菜单初始化
 */
void MenuParamAlarmVibrationInit(void);


/**
 * @brief   进入子菜单
 */
void MenuParamAlarmVibrationChild(void);


/**
 * @brief   进入父菜单
 */
void MenuParamAlarmVibrationParent(void);


/**
 * @brief   下一条菜单项
 */
void MenuParamAlarmVibrationNext(void);


/**
 * @brief   上一条菜单项
 */
void MenuParamAlarmVibrationPrev(void);


/**
 * @brief   输入函数保存的数值提取获得，用于初次进入的数值显示
 */
//void MenuParamAlarmVibrationBinaryGet(E_TurnState* lpState);


/**
 * @brief   输入函数数值保存
 */
//void MenuParamAlarmVibrationSave(E_TurnState lTurn);




// 菜单的资源
extern const struct S_MenuResource gMenuRsrParamAlarmVibration;

#endif
