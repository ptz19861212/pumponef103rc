/**
 * @file    menu_user_group.h
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

#ifndef __MENU_USER_GROUP_H__
#define __MENU_USER_GROUP_H__

/**
 * @brief   菜单初始化
 */
void MenuUserGroupPreInit(void);


/**
 * @brief   菜单初始化
 */
void MenuUserGroupInit(void);


/**
 * @brief   进入子菜单
 */
void MenuUserGroupChild(void);


/**
 * @brief   进入父菜单
 */
void MenuUserGroupParent(void);


/**
 * @brief   下一条菜单项
 */
void MenuUserGroupNext(void);


/**
 * @brief   上一条菜单项
 */
void MenuUserGroupPrev(void);


// 菜单的资源
extern const struct S_MenuResource gMenuRsrUserGroup;

#endif
