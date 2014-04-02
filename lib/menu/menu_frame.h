/**
 * @file    menu_frame.h
 * @brief   菜单 框架代码的外露头文件
 * @author  ptz
 * @email   ptz19861212@163.com
 * @version 0.0.1
 * @date    2013-12-01 18:52:28 星期日 
 * @history (1).2013-12-01 18:52:28 星期日 create
 */
/* Copyright (C)
 * 
 * My own license
 * All right reserved
 * 
 */

#ifndef __MENU_FRAME_H__
#define __MENU_FRAME_H__

#include "my_gas.h"
#include "my_device.h"
#include "my_menu.h"
#include "display_uc1701.h"
#include "display.h"


/**
 * @brief   菜单项语言初始化
 */
void MenuLangInit(void);


/**
 * @brief   获取当前的菜单项是那一条
 *
 * @param   lpItem 地址
 */
void MenuItemGet(menu_t* lpItem);


/**
 * @brief   设置当前的菜单项是那一条
 *
 * @param   lItem
 */
void MenuItemSet(menu_t lItem);


/**
 * @brief   按键 下一条
 */
void MenuKeyNext(void);


/**
 * @brief   按键 上一条
 */
void MenuKeyPrev(void);


/**
 * @brief   菜单处理的进入预初始化
 */
void MenuLoadPreInit(void);


/**
 * @brief   菜单处理的进入初始化
 */
void MenuLoadInit(void);


/**
 * @brief   按键 子菜单
 */
void MenuKeyChild(void);


/**
 * @brief   按键 父菜单
 */
void MenuKeyParent(void);


/**
 * @brief   按键 调用函数
 */
void MenuKey(uint8_t lKey);


/**
 * @brief   菜单无操作倒计时
 */
void MenuNoOperateCountdown(void);


/**
 * @brief   菜单无操作刷新
 */
void MenuNoOperateFresh(void);



/********************************* 菜单处理 ****************************************/

//
//// 菜单项实际处理的标签
//struct S_MenuDisposeResourceLabel
//{
//	// 标签字符串数组
//	const char*** Txt;
//	// 标签字符串行数
//	uint8_t Num;
//};
//
//// 菜单项实际处理的按键选择
//struct S_MenuDisposeResourceEnter
//{
//	// 通用按键选择字符串数组
//	const char*** Txt;
//	// 字符串行数
//	uint8_t Num;
//	// 通用按键选择字符串起始行数
//	uint8_t IndexInit;
//	// 通用按键选择的字符串在本身这个数组中占有的位置，用来提供按键是选择YES还是NO
////	uint8_t Index;
//};
//
//struct S_MenuDisposeResourceReverse
//{
//	// 初始反显行下标
//	my_lcd_t LineInit;
//	// 初始反显行使能
//	FunctionalState Control;
//};
//
//typedef struct
//{
//	// 锁定行下标
//	my_lcd_t Line;
//	// 锁定行使能
//	FunctionalState Control;
//}S_MenuDisposeResourceLock;
//
//// 处理资源
//struct S_MenuDisposeResource
//{
//	// label
//	struct S_MenuDisposeResourceLabel Label;
//	// enter
//	struct S_MenuDisposeResourceEnter Enter;
//	// reverse
//	struct S_MenuDisposeResourceReverse Reverse;
//	// lock, 用于输入数值，锁定行的功能
//	S_MenuDisposeResourceLock Lock;
//};
//
//// 屏幕总共行数
//#define CONFIG_MENU_LCD_LINE_NUM			4
//
//// 标签字符串数组
//// 标签字符串数组的英文 用来计算标签有几条
//// 输入的字符串数组
//// 输入字符串数组的英文，用来计算行数有几行
//// 根据输入的字符串数组的行数，来计算输入的起始行具体是那一行
//// 初次进入反显的是那一行
//// 初次反显功能使能
//// 输入数值锁定的行是那一行
//// 锁定功能使能，输入当中是否存在像输入数值那样需要锁定
//#define MENU_ITEM_DISPOSE_BUILD(label, label_en, enter, enter_en, \
//						line_rev, rev, line_lock, lock)	\
//										label,\
//										MENU_RESOURCE_ITEM_NUM(label_en),\
//										enter,\
//										MENU_RESOURCE_ITEM_NUM(enter_en),\
//										(4 - MENU_RESOURCE_ITEM_NUM(enter_en)),\
//										line_rev,\
//										rev,\
//										line_lock,\
//										lock
//
//
///**
// * @brief   菜单处理初始化
// */
//void MenuDisposeInit(const struct S_MenuDisposeResource* lpMenuDspsRsr);
//
//
///**
// * @brief   菜单处理的进入初始化
// */
//void MenuDisposeChildInit(void);
//
//
///**
// * @brief   菜单项最终处理显示
// */
//void MenuDisposeDisp(void);
//
//
///**
// * @brief   菜单项最终处理数值显示
// *
// * @param   lValue 数值
// * @param   lPoint 小数点位置
// * @param   lPos 放置位置
// */
//void MenuDisposeValueDisp16(my_gas_t lValue, uint8_t lPoint, uint8_t lPos);
//
//
///**
// * @brief   菜单处理的进入
// */
//void MenuDisposeEntry(void);
//
//
///**
// * @brief   获取处理的选择
// */
//void MenuDisposeChooseGet(uint8_t* lpLine, uint8_t** lpAny);
//
//
///**
// * @brief   菜单处理，是否需要锁定的判定
// *
// * @param   lpLock 用于返回是否锁定
// */
//void MenuDisposeLockJudge(E_LockState* lpLock);
//
//
///**
// * @brief   获得锁定的判定
// *
// * @param   lpLock 用于返回是否锁定
// */
//void MenuDisposeLockGet(E_LockState* lpLock);
//
//
///**
// * @brief   按键 下一条
// */
//void MenuDisposeKeyNext(void);
//
//
///**
// * @brief   按键 上一条
// */
//void MenuDisposeKeyPrev(void);
//
//
///**
// * @brief   输入控制函数
// *
// * @param   lLine 输入的是屏幕的第几行
// * @param   lpRet
// */
//void MenuDisposeValueInputDisp(my_lcd_t lLine);
//
//
///**
// * @brief   输入控制函数结束
// */
//void MenuDisposeValueInputOk(void);
//
//
///**
// * @brief   输入控制函数退出
// */
//void MenuDisposeValueInputCancel(void);
//
//
///**
// * @brief   输入控制函数+
// *
// * @param   lLine 输入的是屏幕的第几行
// */
//void MenuDisposeValueInputPlus(my_lcd_t lLine);
//
//
///**
// * @brief   输入控制函数-
// *
// * @param   lLine 输入的是屏幕的第几行
// */
//void MenuDisposeValueInputMinus(my_lcd_t lLine);
//
//
//
///**
// * @brief   菜单区域闪烁设置
// *
// * @param   lStart 开始的点
// * @param   lEnd 结束的点
// */
//void MenuBlinkSet(S_Lcd_Point* lStart, S_Lcd_Point* lEnd);
//
//
///**
// * @brief   菜单区域闪烁
// */
//void MenuBlink(struct S_Device* lpDev);
//
//
///**
// * @brief   菜单区域闪烁停止
// */
//void MenuBlinkOff(void);
//
//
//// 使能字符串 英文
//extern const char *gMenuFrameEnableTxtEn[2];
//
//// 使能字符串 指针数组
//extern const char **gMenuFrameEnableTxt[2];
//
//// 输入字符串 英文
//extern const char *gMenuFrameInputTxtEn[3];
//
//// 输入字符串 指针数组
//extern const char **gMenuFrameInputTxt[3];

#endif
