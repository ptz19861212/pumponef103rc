/**
 * @file    menu_param_alarm_sound.h
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

#ifndef __MENU_PARAM_ALARM_SOUND_H__
#define __MENU_PARAM_ALARM_SOUND_H__


#include "my_num.h"


/**
 * @brief   菜单初始化
 */
void MenuParamAlarmSoundPreInit(void);


/**
 * @brief   菜单初始化
 */
void MenuParamAlarmSoundInit(void);


/**
 * @brief   进入子菜单
 */
void MenuParamAlarmSoundChild(void);


/**
 * @brief   进入父菜单
 */
void MenuParamAlarmSoundParent(void);


/**
 * @brief   下一条菜单项
 */
void MenuParamAlarmSoundNext(void);


/**
 * @brief   上一条菜单项
 */
void MenuParamAlarmSoundPrev(void);


///**
// * @brief   输入函数数值获得
// */
//void MenuParamAlarmSoundGet(void);
//
//
///**
// * @brief   输入函数数值设置
// */
//void MenuParamAlarmSoundSet(void);


/**
 * @brief   输入函数保存的数值提取获得，用于初次进入的数值显示
 */
//void MenuParamAlarmSoundBinaryGet(E_TurnState* lpState);


/**
 * @brief   输入函数数值保存
 */
//void MenuParamAlarmSoundSave(E_TurnState lTurn);




// 菜单的资源
extern const struct S_MenuResource gMenuRsrParamAlarmSound;

#endif
