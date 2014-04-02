/**
 * @file    display.h
 * @brief   
 * @author  ptz
 * @email   ptz19861212@163.com
 * @version 0.0.1
 * @date    2014-01-05 14:59:28 星期日 
 * @history (1).2014-01-05 14:59:28 星期日 create
 */
/* Copyright (C)
 * 
 * My own license
 * All right reserved
 * 
 */

#ifndef __DISPLAY_H__
#define __DISPLAY_H__

#include "my_language.h"
#include "my_display.h"


/************************************* 上层显示结构体 ********************************/
typedef struct
{
	// 字符串
//	const char* lpChar;
	const char* Char;
	// 在屏幕上的位置是第几行
//	my_lcd_t lPos;
	my_lcd_t Pos;
}S_Lcd__Item;

typedef struct
{
	// 字符串
//	const char* lpChar;
	// 在屏幕上的位置是第几行
//	my_lcd_t lPos;
	S_Lcd__Item Item;
	// 居中显示，运行的长度
	my_lcd_t Len;
}S_Lcd__Item_Mid;

typedef struct
{
	// 滚动条长度
	my_lcd_t Len;
	// 滚动条的起始Y坐标
	my_lcd_t Y;
}S_Lcd__ScrollBar;

typedef struct
{
	// 字符串
//	const char* lpChar;
	const char* Char;
	// 在X方向的起始位置
	// 这个在菜单中的位置是确定的，都是挨着屏幕右边的滚动条
//	my_lcd_t X;
	// 在屏幕上的位置是第几行
	my_lcd_t Pos;
}S_Lcd__Unit;


typedef struct
{
	// 显示的字符串和位置
	S_Lcd__Item_Mid Trig;
	// 闪烁的位
	uint8_t Index;
}S_Lcd__Blink;


/**
 * @brief   显示语言设置
 *
 * @param   lLang
 */
void Lcd__LangSet(E_Language lLang);


/**
 * @brief   显示语言 获得
 *
 * @param   lLang
 */
E_Language Lcd__LangGet(void);



/**
 * @brief   显示菜单项
 *
 * @param   lpItem
 */
void Lcd__MenuItemDisp(S_Lcd__Item* lpItem);


/**
 * @brief   显示菜单触发项，居中显示，一般是 选择和输入项
 *
 * @param   lpItem
 */
void Lcd__MenuItemMidDisp(S_Lcd__Item_Mid* lpItem);


/**
 * @brief   反显菜单项
 *
 * @param   lPos
 */
void Lcd__MenuItemRev(my_lcd_t lPos);



/**
 * @brief   显示分割的虚线
 *
 * @param   lpItem
 */
void Lcd__MenuDivLineDisp(void);


/**
 * @brief   显示滚动条
 *
 * @param   lpScrollBar
 */
void Lcd__MenuScrollBarDisp(S_Lcd__ScrollBar* lpScrollBar);


/**
 * @brief   显示滚动条附属文字
 *
 * @param   lpChar
 */
void Lcd__MenuScrollBarTxtDisp(const char* lpChar);


/**
 * @brief   显示菜单本身文字
 *
 * @param   lpChar
 */

void Lcd__MenuSelfTxtDisp(const char* lpChar);


/**
 * @brief   单位显示
 *
 * @param   lpUnit
 */
void Lcd__MenuUnitDisp(S_Lcd__Unit* lpUnit);


/**
 * @brief   单位显示
 *
 * @param   lpUnit
 */
void Lcd__UnitDisp(const char* lpUnit);


/**
 * @brief   显示气体名称
 *
 * @param   lpName
 */
void Lcd__GasNameDisp(const char* lpName);


/**
 * @brief   显示状态 检测，高报，低报
 *
 * @param   lpState
 */
void Lcd__StatDisp(const char* lpState);


/**
 * @brief   显示气体数值
 *
 * @param   lpValue
 */
void Lcd__GasValueDisp(S_Value_U16* lpValue);


/**
 * @brief   清除气体数值
 */
void Lcd__GasValueClr(void);


/**
 * @brief   显示菜单触发项，居中显示，一般是 选择和输入项，在Y方向，以半行 8像素上下移动
 *
 * @param   lpItem
 */
my_lcd_t Lcd__FrameItemMidDispHalf(S_Lcd__Item_Mid* lpItem);


/**
 * @brief   显示菜单触发项，居中显示，一般是 选择和输入项
 *
 * @param   lpItem
 */
my_lcd_t Lcd__FrameItemMidDisp(S_Lcd__Item_Mid* lpItem);


/**
 * @brief   反显输入菜单项，以半行作为显示的起点，比如说1/2行，1行，3/2行等等
 *
 * @param   lPos
 */
void Lcd__FrameItemRevHalf(my_lcd_t lPos);


/**
 * @brief   反显输入菜单项
 *
 * @param   lPos
 */
void Lcd__FrameItemRev(my_lcd_t lPos);


/**
 * @brief   菜单项最终处理数值显示，这个是数值输入时候显示，当前的某一位处于闪烁状态
 * 				这个是数值输入的底层函数，被 MenuDisposeValueInputDisp 调用的
 *
 * @param   lpArray 显示数组
 * @param   lPos 放置位置
 * @param   lIndex 当前输入的位
 */
//static void MenuDisposeInputDisp(char* lpArray, uint8_t lPos, uint8_t lIndex)
void Lcd__MenuInputValueBlinkDispHalf(S_Lcd__Blink* lpBlink);





///**
// * @brief   显示滚动条附属文字
// *
// * @param   lpScroll
// * @param   lX
// * @param   lY
// */
//void DisScrollBarTxt(const uint8_t *lpScroll, uint8_t lX, uint8_t lY);
//
//
///**
// * @brief   显示菜单本身文字
// *
// * @param   lpMenu
// * @param   lX
// * @param   lY
// */
//void DisMenuSelfTxt(const uint8_t *lpMenu, uint8_t lX, uint8_t lY);
//
//
///**
// * @brief   显示单位
// *
// * @param   lpUnit
// * @param   lX
// * @param   lY
// */
//void DisUnit(const uint8_t *lpUnit, uint8_t lX, uint8_t lY);
//
///**
// * @brief   显示气体名称
// *
// * @param   lpName
// * @param   lX
// * @param   lY
// */
//void DisGasName(const uint8_t *lpName, uint8_t lX, uint8_t lY);
//
///**
// * @brief   显示状态 检测，高报，低报
// *
// * @param   lpStat
// * @param   lX
// * @param   lY
// */
//void DisStat(const uint8_t *lpStat, uint8_t lX, uint8_t lY);
//
///**
// * @brief   显示正确状态
// *
// * @param   lX
// * @param   lY
// */
//void DisSymCor(uint8_t lX, uint8_t lY);
//
///**
// * @brief   显示错误状态
// *
// * @param   lX
// * @param   lY
// */
//void DisSymWron(uint8_t lX, uint8_t lY);
//
///**
// * @brief   显示报警状态
// *
// * @param   lpAlar
// * @param   lX
// * @param   lY
// */
//void DisSymAlar(const uint8_t *lpAlar, uint8_t lX, uint8_t lY);
//
///**
// * @brief   反显报警状态
// *
// * @param   lX
// * @param   lY
// */
//void DisSymAlarRev(uint8_t lX, uint8_t lY);
//
///**
// * @brief   清除报警状态
// *
// * @param   lX
// * @param   lY
// */
//void DisSymAlarClr(uint8_t lX, uint8_t lY);
//
///**
// * @brief   显示风扇
// *
// * @param   lFan 风扇显示状态
// * @param   lX
// * @param   lY
// */
//void DisSymFan(S_Lcd_Point* lpPoint);
//
//
///**
// * @brief   清除风扇
// *
// * @param   lpPoint
// */
//void DisSymFanClr(S_Lcd_Point* lpPoint);
//
//
///**
// * @brief   显示充电状态
// *
// * @param   lX
// * @param   lY
// */
//void DisSymChar(uint8_t lX, uint8_t lY);
//
///**
// * @brief   清除充电状态
// *
// * @param   lX
// * @param   lY
// */
//void DisSymCharClr(uint8_t lX, uint8_t lY);
//
///**
// * @brief   显示大号充电状态
// *
// * @param   lX
// * @param   lY
// */
//void DisSymCharLar(uint8_t lX, uint8_t lY);
//
///**
// * @brief   显示大号充满状态
// *
// * @param   lX
// * @param   lY
// */
//void DisSymFull(uint8_t lX, uint8_t lY);
//
///**
// * @brief   显示电池状态
// *
// * @param   lBat
// * @param   lX
// * @param   lY
// */
//void DisSymBat(uint8_t lBat, uint8_t lX, uint8_t lY);

#endif
