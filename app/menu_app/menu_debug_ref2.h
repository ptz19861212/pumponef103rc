/**
 * @file    menu_debug_ref2.h
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

#ifndef __MENU_DEBUG_REF2_H__
#define __MENU_DEBUG_REF2_H__

/**
 * @brief   菜单初始化
 */
void MenuDebugRef2PreInit(void);


/**
 * @brief   菜单初始化
 */
void MenuDebugRef2Init(void);


/**
 * @brief   进入子菜单
 */
void MenuDebugRef2Child(void);


/**
 * @brief   进入父菜单
 */
void MenuDebugRef2Parent(void);


/**
 * @brief   下一条菜单项
 */
void MenuDebugRef2Next(void);


/**
 * @brief   上一条菜单项
 */
void MenuDebugRef2Prev(void);


// 菜单的资源
extern const struct S_MenuResource gMenuRsrDebugRef2;

#endif
