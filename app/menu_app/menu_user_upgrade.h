/**
 * @file    menu_user_upgrade.h
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

#ifndef __MENU_USER_UPGRADE_H__
#define __MENU_USER_UPGRADE_H__

/**
 * @brief   菜单初始化
 */
void MenuUserUpgradePreInit(void);


/**
 * @brief   菜单初始化
 */
void MenuUserUpgradeInit(void);


/**
 * @brief   进入子菜单
 */
void MenuUserUpgradeChild(void);


/**
 * @brief   进入父菜单
 */
void MenuUserUpgradeParent(void);


/**
 * @brief   下一条菜单项
 */
void MenuUserUpgradeNext(void);


/**
 * @brief   上一条菜单项
 */
void MenuUserUpgradePrev(void);


// 菜单的资源
extern const struct S_MenuResource gMenuRsrUserUpgrade;

#endif
