/**
 * @file    menu_frame_in.h
 * @brief   菜单 框架内含头文件
 * @author  ptz
 * @email   ptz19861212@163.com
 * @version 0.0.1
 * @date    2013-12-01 18:53:28 星期日 
 * @history (1).2013-12-01 18:53:28 星期日 create
 */
/* Copyright (C)
 * 
 * My own license
 * All right reserved
 * 
 */

#ifndef __MENU_FRAME_IN_H__
#define __MENU_FRAME_IN_H__

#include "stm32f10x.h"
#include "menu_tab.h"
#include "menu_frame.h"
//#include "menu_root.h"
//#include "menu_param.h"
#include "my_define.h"
#include "my_language.h"
#include "my_display.h"
#include "string.h"
#include "num_to_str.h"
#include "key.h"
#include "gas_alarm_get.h"
#include "my_math.h"
#include "my_menu.h"


/******************** 菜单相关配置 **************************/
// 一个屏幕能显示的最多菜单项的数目，通常取决于屏幕的宽度
#define CONFIG_ITEM_DISP_MAX			3
// 菜单最大深度，最简单的菜单也有两层深度
#define CONFIG_DEPTH_MAX					4
// 菜单本身名字的坐标
#define CONFIG_MENU_SELF_TXT_X_START			0
#define CONFIG_MENU_SELF_TXT_Y_START			(64 - 16 + 1)
// 菜单虚线位置
#define CONFIG_MENU_DOT_LINE_X_START			0
#define CONFIG_MENU_DOT_LINE_X_END				125
#define CONFIG_MENU_DOT_LINE_Y_START			47



/******************** 滚动条相关配置 ***********************/
// 滚动条滑块左边宽度
#define CONFIG_SCROLL_BAR_EX			1
// 滚动条长线的X坐标
#define CONFIG_SCROLL_BAR_X				126
// 滚动条区域的坐标
#define CONFIG_SCROLL_BAR_X_START		(126 - 1)
#define CONFIG_SCROLL_BAR_X_END			(126 + 1)
#define CONFIG_SCROLL_BAR_Y_START		0
#define CONFIG_SCROLL_BAR_Y_END			47
// 滚动条文字宽度
#define CONFIG_SCROLL_BAR_TXT_X			5
#define CONFIG_SCROLL_BAR_TXT_Y			10

// 滚动条文字最右边边界
#define CONFIG_SCROLL_BAR_TXT_X_END	127
#define CONFIG_SCROLL_BAR_TXT_X_START	64
// 滚动条文字Y轴
#define CONFIG_SCROLL_BAR_TXT_Y_START	(63 - CONFIG_SCROLL_BAR_TXT_Y)
#define CONFIG_SCROLL_BAR_TXT_Y_END	63


/********************* 计算滚动条数字字符长度 *******************/
// 获得实际菜单是8位还是16位等等
#define MENU_SCROLL_TXT_TYPE_SIZE			(sizeof(menu_t) / sizeof(uint8_t))
// 获得数字十进制的长度，8位是3个字符（256），16位是5个（65535），32位是10个
#if (CONFIG_MENU_BITS == 8)
	#define MENU_SCROLL_TXT_LEN 			TYPE_U8_LEN
#elif (CONFIG_MENU_BITS == 16)
	#define MENU_SCROLL_TXT_LEN 			TYPE_U16_LEN
#elif (CONFIG_MENU_BITS == 32)
	#define MENU_SCROLL_TXT_LEN 			TYPE_U32_LEN
#endif
//#define MENU_SCROLL_TXT_LEN			\
//									((MENU_SCROLL_TXT_TYPE_SIZE == 1) ? \
//									TYPE_U8_LEN : \
//									(MENU_SCROLL_TXT_TYPE_SIZE == 2) ? \
//									TYPE_U16_LEN : \
//									TYPE_U32_LEN)
// 计算滚动条文字字符数组的大小，数字之间用'-'来分割，所以例如"1-2-3"，分为3个部分
// 分别是 1 -2 -3，其中-n需要的多少是和数字是8位还是16位等相关的，如果是8位那么，
// -n就是 3+1，是4位。所以 "1-2-3"大小计算位 3 (+1+3) (+1+3) +1，后面的+1是字符串结束附'\0'
// 所以可以简单的写成 4 * 菜单深度
#define MENU_SCROLL_TXT_SIZE	((MENU_SCROLL_TXT_LEN + 1) * CONFIG_DEPTH_MAX)

// 根据数字类型的长度确定真正的数字转换函数
#if (CONFIG_MENU_BITS == 8)
	#define NUM_TO_STR(lAdd) 			DecToStrU8(lAdd)
#elif (CONFIG_MENU_BITS == 16)
	#define NUM_TO_STR(lAdd) 			DecToStrU16(lAdd)
#elif (CONFIG_MENU_BITS == 32)
	#define NUM_TO_STR(lAdd) 			DecToStrU32(lAdd)
#endif

//#define NUM_TO_STR(lD, lN, lP)	\
//									(MENU_SCROLL_TXT_TYPE_SIZE == 1) ? \
//									DecToStrU8(lD, lN, lP) : \
//									((MENU_SCROLL_TXT_TYPE_SIZE == 2) ? \
//									DecToStrU16(lD, lN, lP) : \
//									DecToStrU32(lD, lN, lP))

/*******************  屏幕LCD相关配置 *********************/
// 菜单项显示区域x方向开始
#define CONFIG_ITEM_X_START				0
#define CONFIG_ITEM_X_END				122
#define CONFIG_ITEM_Y_START				0
#define CONFIG_ITEM_Y_END				47
// 菜单项处理显示区域
#define CONFIG_ITEM_DESPOSE_LCD_X_SIZE			128
// 菜单项处理的单个字符在X方向的大小
#define CONFIG_ITEM_DESPOSE_TXT_X_SIZE			8

// 反显菜单项x方向结束数值
#define CONFIG_ITEM_REV_X				122

// 每条菜单项在y方向的间隔
#define CONFIG_ITEM_GAP_Y				0

// 菜单项文字的x方向开始的数值 注意这个数值是因为反显导致x=0的那边不容易看得清除
#define CONFIG_ITEM_TXT_X				1

// 菜单显示的x方向的开始数值
#define CONFIG_ITEM_OFFSET_X			0

// 菜单项的y方向字符的大小
#define CONFIG_ITEM_SIZE_Y				16

// 菜单显示的y方向的开始数值，数值是屏幕上面的黑边 4,在加上菜单项之间的间隔 3
#define CONFIG_ITEM_OFFSET_Y			(0 + CONFIG_ITEM_GAP_Y)

// 每条菜单项在Y方向具体坐标的间隔
#define CONFIG_ITEM_OFFSET_GAP_Y		(CONFIG_ITEM_GAP_Y + CONFIG_ITEM_SIZE_Y)


/***************************** LCD 菜单项处理 ***********************************/
#define CONFIG_DISPOSE_POS_X_START			0
#define CONFIG_DISPOSE_POS_X_END			128
#define CONFIG_DISPOSE_POS_Y_GAP			16
#define CONFIG_DISPOSE_TXT_SIZE_X			8
#define CONFIG_DISPOSE_TXT_SIZE_Y			16


/***************************** 退出 ************************************/
// 菜单长时间误操作，自动退出
#define CONFIG_MENU_NO_OPERATE_SECOND				10

/***************************** 预定义 ***********************/

//// 不进行菜单初始化
//#define MENU_FRESH_NO_ACTION			0
//
//// 正常从父菜单进入子菜单，由系统进行初始化
//#define MENU_FRESH_AUTO_INIT			1
//
//// 手动进行初始化
//#define MENU_FRESH_MANUAL_INIT			2
//
//// 重新绘制画面
//#define MENU_FRESH_REFRESH				3


// 当前指向菜单
struct S_MenuItem
{
	// 当前的菜单项 0 ~ (ItemNum - 1)
	menu_t Item;
	// 当前的菜单项总数
	menu_t ItemNum;
	// 当前的显示在屏幕上的位置 0 ~ (CONFIG_ITEM_DIS_MAX - 1)
	menu_t Where;
	// 滚动条滑块长度
	menu_t ScrollLen;
	// 滚动条滑块每次移动距离
	menu_t ScrollGap;
};


// 菜单框架 包括菜单索引和菜单资源
struct S_MenuFrame
{
	// 当前的菜单状态机的状态数值，也就是在菜单数组中的索引下标
	menu_t MenuIndex;
	// 菜单项资源指针
	const struct S_MenuResource *MenuRsr;
};


// 菜单显示
struct S_MenuDisp
{
	// ItemNum 和 CONFIG_ITEM_DIS_MAX 中的较小值
	menu_t DispMin;
	// 菜单本身字符串
	const char *TextSelf;
	// 显示菜单项的字符串的数组
	const char **TextItem;
};


// 当前菜单控制
struct S_MenuCtr
{
	// 控制显示刷新
	//uint8_t Fresh;
	// 控制显示语言
//	menu_t Lang;
	E_Language Lang;
};


// 备份用的结构体
struct S_MenuBak
{
	// 菜单项备份数组
	menu_t MenuIndex[CONFIG_DEPTH_MAX - 1];
	// 菜单资源备份
	const struct S_MenuResource *MenuRsr[CONFIG_DEPTH_MAX - 1];
	// 菜单层数
	menu_t Depth;
	// 菜单项备份数组
	menu_t Item[CONFIG_DEPTH_MAX - 1];
	// 菜单项的显示位置备份数组
	menu_t Where[CONFIG_DEPTH_MAX - 1];
};


/************************************ 菜单最终的选择处理 *******************************/
//
//// 菜单处理框架 包括菜单索引和菜单处理资源
//struct S_MenuDisposeFrame
//{
//	// 当前的菜单状态机的状态数值，
//	menu_t MenuIndex;
//	// 菜单项处理资源指针
//	const struct S_MenuDisposeResource* MenuDspsRsr;
//};
//
//// 处理的显示文字
//struct S_MenuDisposeDispText
//{
//	// 显示字符串的数组
//	const char **Txt;
//	// 显示字符串数组的行数
//	uint8_t Num;
//	// 在屏幕上面显示的初始行
//	uint8_t LineInit;
//};
//
//// 反显
//struct S_MenuDisposeDispReverse
//{
//	// 反显的最初始的行
//	uint8_t LineInit;
//	// 初始反显的使能，可能有些处理不需要初始反显一整个行
//	FunctionalState Ctr;
//};
//
//// 菜单显示
//struct S_MenuDisposeDisp
//{
//	// 标签
//	struct S_MenuDisposeDispText Label;
//	// 选择
//	struct S_MenuDisposeDispText Enter;
//	// 反显
//	struct S_MenuDisposeDispReverse Reverse;
//};
//
//// 菜单处理的选择
//struct S_MenuDisposeCtr
//{
//	// 最终选择返回的是相对于屏幕的第几行，至于相当于ENTER的，可以通过ENTER初始行，计算
//	uint8_t Line;
//	// 相当于ENTER的第几行，简单的计算就可以得到
//	uint8_t LineEnter;
//	// 是否允许锁定
//	FunctionalState Lock;
//	// 锁定的行，相对于ENTER来说
//	uint8_t LineLock;
//	// 当前的锁定状态
//	E_LockState State;
//	// 返回一个可能需要用到的指针
//	void* Any;
//};
//
//
//// 菜单区域闪烁
//struct S_MenuBlink
//{
//	S_Lcd_Point Start;
//	S_Lcd_Point End;
//	FunctionalState State;
//};

#endif
