/**
 * @file    my_menu.h
 * @brief   
 * @author  ptz
 * @email   ptz19861212@163.com
 * @version 0.0.1
 * @date    2014-01-04 21:06:34 星期六 
 * @history (1).2014-01-04 21:06:34 星期六 create
 */
/* Copyright (C)
 * 
 * My own license
 * All right reserved
 * 
 */


#ifndef __MY_MENU_H__
#define __MY_MENU_H__

#include "config_bsp.h"
#include "my_num.h"


#if (CONFIG_MENU_BITS == 8)
	typedef uint8_t 						menu_t;
	typedef S_Value_Array_U8				S_Value_Scroll_Bar_Txt;
#endif

typedef void (*MenuFun)(void);

#ifdef CONFIG_LCD_CHIP_UC1701
	// 为了好看，滚动条最上面和下面保留的点
	#define SCROLL_BAR_REMAIN_DOT		3
	// 滚动条滑块最短长度
	#define SCROLL_BAR_LEN_MIN			3
#endif


// 用于菜单根据按键调用相应的菜单函数
//struct S_MenuTab
typedef struct
{
	menu_t MenuIndex;
	MenuFun PreInit;
	MenuFun Init;
	MenuFun Child;
	MenuFun Parent;
	MenuFun Next;
	MenuFun Prev;
}S_MenuTab;


struct S_MenuResource
{
	// 菜单执行函数
	MenuFun Action;
	// 菜单项的个数
	menu_t Num;
	// 滚动条滑块长度
	menu_t ScrollLen;
	// 滚动条每次滑动长度
	menu_t ScrollGap;
	// 子菜单索引数组
	const menu_t *ItemIndex;
	// 子菜单资源数组
	const struct S_MenuResource **ItemResource;
	// 菜单本身文字 字符串
	const char **SelfText;
	// 菜单项文字字符串根据语言组成的数组
	const char ***ItemText;
};

/************************* 生成菜单资源结构体 ***********************/
// 获得菜单项的数目
#define MENU_RESOURCE_ITEM_NUM(itemen)		(sizeof(itemen) / sizeof(my_base_t))
// 获得滚动条滑块的本来长度
#define MENU_SCROLL_BAR_LEN_REAL(txt) \
									((48 - 2 * SCROLL_BAR_REMAIN_DOT) /\
									MENU_RESOURCE_ITEM_NUM(txt))
// 获得滚动条滑块的最终长度
#define MENU_SCROLL_BAR_LEN(txt)	\
									((MENU_SCROLL_BAR_LEN_REAL(txt)> \
									SCROLL_BAR_LEN_MIN) ? \
									MENU_SCROLL_BAR_LEN_REAL(txt) : \
									SCROLL_BAR_LEN_MIN)
// 获得滚动条每次滑动的距离
#define MENU_SCROLL_BAR_GAP(txt)		\
										((48 - 2 * SCROLL_BAR_REMAIN_DOT)\
										/ MENU_RESOURCE_ITEM_NUM(txt))
// 菜单资源结构体
#define MENU_RESOURCE(itemen, index, rsr, self, item)	\
										0,\
										MENU_RESOURCE_ITEM_NUM(itemen),\
										MENU_SCROLL_BAR_LEN(itemen),\
										MENU_SCROLL_BAR_GAP(itemen),\
										(const menu_t *)(index),\
										(const struct S_MenuResource **)(rsr),\
										(const char **)(self),\
										(const char ***)(item),




#endif
