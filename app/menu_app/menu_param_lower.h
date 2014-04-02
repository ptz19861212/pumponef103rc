/**
 * @file    menu_par_lower.h
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

#ifndef __MENU_PARAM_LOWER_H__
#define __MENU_PARAM_LOWER_H__

#include "my_num.h"

/**
 * @brief   菜单初始化
 */
void MenuParamLowerPreInit(void);


/**
 * @brief   菜单初始化
 */
void MenuParamLowerInit(void);


/**
 * @brief   进入子菜单
 */
void MenuParamLowerChild(void);


/**
 * @brief   进入父菜单
 */
void MenuParamLowerParent(void);


/**
 * @brief   下一条菜单项
 */
void MenuParamLowerNext(void);


/**
 * @brief   上一条菜单项
 */
void MenuParamLowerPrev(void);


/**
 * @brief   输入函数数值获得
 */
//void MenuParamLowerGet(void);


/**
 * @brief   输入函数数值设置
 */
//void MenuParamLowerSet(void);


/**
 * @brief   输入函数保存的数值获得
 */
//void MenuParamLowerValueGet(S_Value_U16* lpValue);


/**
 * @brief   输入函数数值保存
 */
//void MenuParamLowerSave(void);




// 菜单的资源
extern const struct S_MenuResource gMenuRsrParamLower;

#endif
