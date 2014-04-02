/**
 * @file    menu_rst_cali.h
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

#ifndef __MENU_RST_CALI_H__
#define __MENU_RST_CALI_H__

/**
 * @brief   菜单初始化
 */
void MenuRestoreCaliPreInit(void);


/**
 * @brief   菜单初始化
 */
void MenuRestoreCaliInit(void);


/**
 * @brief   进入子菜单
 */
void MenuRestoreCaliChild(void);


/**
 * @brief   进入父菜单
 */
void MenuRestoreCaliParent(void);


/**
 * @brief   下一条菜单项
 */
void MenuRestoreCaliNext(void);


/**
 * @brief   上一条菜单项
 */
void MenuRestoreCaliPrev(void);


// 菜单的资源
extern const struct S_MenuResource gMenuRsrRestoreCali;

#endif
