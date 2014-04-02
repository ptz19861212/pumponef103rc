/**
 * @file    menu_param_stel.h
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

#ifndef __MENU_PARAM_BAK_H__
#define __MENU_PARAM_BAK_H__

/**
 * @brief   菜单初始化
 */
void MenuParamBakPreInit(void);


/**
 * @brief   菜单初始化
 */
void MenuParamBakInit(void);


/**
 * @brief   进入子菜单
 */
void MenuParamBakChild(void);


/**
 * @brief   进入父菜单
 */
void MenuParamBakParent(void);


/**
 * @brief   下一条菜单项
 */
void MenuParamBakNext(void);


/**
 * @brief   上一条菜单项
 */
void MenuParamBakPrev(void);


// 菜单的资源
extern const struct S_MenuResource gMenuRsrParamBak;

#endif
