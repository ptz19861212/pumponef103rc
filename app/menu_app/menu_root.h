/**
 * @file    menu_root.h
 * @brief   根菜单 头文件
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

#ifndef __MENU_ROOT_H__
#define __MENU_ROOT_H__

/**
 * @brief   菜单初始化
 */
void MenuRootPreInit(void);


/**
 * @brief   菜单初始化
 */
void MenuRootInit(void);


/**
 * @brief   进入子菜单
 */
void MenuRootChild(void);


/**
 * @brief   进入父菜单
 */
void MenuRootParent(void);


/**
 * @brief   下一条菜单项
 */
void MenuRootNext(void);


/**
 * @brief   上一条菜单项
 */
void MenuRootPrev(void);


// 菜单的资源
extern const struct S_MenuResource gMenuRsrRoot;


#endif
