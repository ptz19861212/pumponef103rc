/**
 * @file    menu_param_upper.h
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

#ifndef __MENU_PARAM_UPPER_H__
#define __MENU_PARAM_UPPER_H__

#include "my_num.h"


/**
 * @brief   菜单初始化
 */
void MenuParamUpperPreInit(void);


/**
 * @brief   菜单初始化
 */
void MenuParamUpperInit(void);


/**
 * @brief   进入子菜单
 */
void MenuParamUpperChild(void);


/**
 * @brief   进入父菜单
 */
void MenuParamUpperParent(void);


/**
 * @brief   下一条菜单项
 */
void MenuParamUpperNext(void);


/**
 * @brief   上一条菜单项
 */
void MenuParamUpperPrev(void);


/**
 * @brief   输入函数数值获得
 */
void MenuParamUpperGet(void);


/**
 * @brief   输入函数数值设置
 */
void MenuParamUpperSet(void);


/**
 * @brief   输入函数保存的数值获得
 */
void MenuParamUpperValueGet(S_Value_U16* lpValue);


/**
 * @brief   输入函数数值保存
 */
void MenuParamUpperSave(void);




// 菜单的资源
extern const struct S_MenuResource gMenuRsrParamUpper;

#endif
