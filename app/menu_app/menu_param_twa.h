/**
 * @file    menu_param_twa.h
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

#ifndef __MENU_PARAM_TWA_H__
#define __MENU_PARAM_TWA_H__

#include "my_num.h"


/**
 * @brief   菜单初始化
 */
void MenuParamTwaPreInit(void);


/**
 * @brief   菜单初始化
 */
void MenuParamTwaInit(void);


/**
 * @brief   进入子菜单
 */
void MenuParamTwaChild(void);


/**
 * @brief   进入父菜单
 */
void MenuParamTwaParent(void);


/**
 * @brief   下一条菜单项
 */
void MenuParamTwaNext(void);


/**
 * @brief   上一条菜单项
 */
void MenuParamTwaPrev(void);


/**
 * @brief   输入函数数值获得
 */
void MenuParamTwaGet(void);


/**
 * @brief   输入函数数值设置
 */
void MenuParamTwaSet(void);


/**
 * @brief   输入函数保存的数值获得
 */
void MenuParamTwaValueGet(S_Value_U16* lpValue);


/**
 * @brief   输入函数数值保存
 */
void MenuParamTwaSave(void);




// 菜单的资源
extern const struct S_MenuResource gMenuRsrParamTwa;

#endif
