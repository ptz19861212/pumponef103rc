/**
 * @file    display_in.h
 * @brief   
 * @author  ptz
 * @email   ptz19861212@163.com
 * @version 0.0.1
 * @date    2014-01-05 14:59:54 星期日 
 * @history (1).2014-01-05 14:59:54 星期日 create
 */
/* Copyright (C)
 * 
 * My own license
 * All right reserved
 * 
 */


#ifndef __DISPLAY_IN_H__
#define __DISPLAY_IN_H__

#include "display_uc1701.h"
#include "display.h"
#include "font_chinese.h"

/********************************** 选择字体 **************************************/
// 菜单项的文字选取
#define CONFIG_ITEM_EN						gLcdTxt8x16
#define CONFIG_ITEM_CN						gLcdTxt16x16
// 菜单滚动条字体
#define CONFIG_SCROLL_BAR_TXT				gLcdTxt5x10
// 菜单名的字体
#define CONFIG_SELF_EN						gLcdTxt8x16
#define CONFIG_SELF_CN						gLcdTxt16x16
// 菜单中单位的字体
#define CONFIG_MENU_UNIT						gLcdTxt8x16
// 单位的字体
#define CONFIG_UNIT							gLcdTxt8x16
// 气体名称的字体
#define CONFIG_GAS_NAME_NUM					gLcdTxt5x10
#define CONFIG_GAS_NAME_EN_LCD				gLcdTxt8x16
#define CONFIG_GAS_NAME_CN_LCD				gLcdTxt16x16
// 状态（检测，一级报警，二级报警）的字体
#define CONFIG_STATE_EN						gLcdTxt8x16
#define CONFIG_STATE_CN						gLcdTxt16x16
// 气体数值字体
#define CONFIG_GAS_VALUE						gLcdTxt16x32

/******************************** 菜单项 *****************************************/
// 普通菜单项x 坐标开始
#define CONFIG_ITEM_X_START					1
// 普通菜单项X 坐标结束
#define CONFIG_ITEM_X_END					122


/********************************** 菜单分割线 ***********************************/
// 菜单中的分割线在第几行
#define CONFIG_DIV_LINE_POS					3

/********************************** 菜单滚动条 ************************************/
// 菜单滚动条的X坐标
#define CONFIG_SCROLL_BAR_X					126
// 滚动条X方向扩展宽度
#define CONFIG_SCROLL_BAR_X_EX				1
// 滚动条Y方向起始的行
#define CONFIG_SCROLL_BAR_POS_Y				0
// 滚动条Y方向结束的时候还剩下几行
#define CONFIG_SCROLL_BAR_POS_Y_END		1

/********************************** 菜单滚动条文字 *******************************/
// 滚动条文字长度，这个是为了靠右显示
#define CONFIG_SCROLL_BAR_TXT_LEN			10

/********************************** 菜单单位显示 *********************************/
// 菜单单位文字长度，这个是为了靠右显示
#define CONFIG_MENU_UNIT_LEN				4

/********************************** 正常单位显示 *********************************/
// 正常单位文字长度，这个是为了靠右显示
#define CONFIG_UNIT_LEN						4
// 正常单位在第几行
#define CONFIG_UNIT_POS						2

/********************************** 状态显示 *************************************/
// 正常状态文字长度，这个是为了靠右显示
#define CONFIG_STATE_LEN						8
// 正常状态在第几行
#define CONFIG_STATE_POS						3

/********************************** 正常气体数值显示 *************************************/
// 正常气体数值文字长度，这个是为了靠右显示
#define CONFIG_GAS_VALUE_LEN				6
// 正常气体数值在第几行(相对于正常的其他大小的字体)
#define CONFIG_GAS_VALUE_POS				1
// 正常气体数值在X方向坐标
#define CONFIG_GAS_VALUE_X					0

/******************************* 菜单输入项反显坐标 ***********************************/
// 普通菜单项x 坐标开始
#define CONFIG_INPUT_REV_X_START				2
// 普通菜单项X 坐标结束
#define CONFIG_INPUT_REV_X_END					122


#endif
