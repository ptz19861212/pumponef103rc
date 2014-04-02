/**
 * @file    display.c
 * @brief   
 * @author  ptz
 * @email   ptz19861212@163.com
 * @version 0.0.1
 * @date    2014-01-05 14:59:09 星期日 
 * @history (1).2014-01-05 14:59:09 星期日 create
 */
/* Copyright (C)
 * 
 * My own license
 * All right reserved
 * 
 */

#include "display_in.h"

static uint8_t sLang = 0;

/**
 * @brief   显示语言设置
 *
 * @param   lLang
 */
void Lcd__LangSet(E_Language lLang)
{
	sLang = lLang;
}


/**
 * @brief   显示语言 获得
 *
 * @param   lLang
 */
E_Language Lcd__LangGet(void)
{
	return sLang;
}


// 菜单项字体指针
const static S_Lcd_Txt* spItem[] =
{
		&CONFIG_ITEM_EN,
		&CONFIG_ITEM_CN,
};


/**
 * @brief   显示菜单项
 *
 * @param   lpItem
 */
void Lcd__MenuItemDisp(S_Lcd__Item* lpItem)
{
	S_Lcd_String lStr;

	lStr.Char = lpItem->Char;

	if (*(lpItem->Char) < 0x80)
	{
		lStr.Txt = spItem[LANGUAGE_EN];
		lStr.PS.Y = lpItem->Pos *
//							spItem[LANGUAGE_EN]->Pixel.Y;
							spItem[LANGUAGE_EN]->Own.Y;
	}
	else
	{
		lStr.Txt = spItem[LANGUAGE_CN];
		lStr.PS.Y = lpItem->Pos *
//							spItem[LANGUAGE_CN]->Pixel.Y;
							spItem[LANGUAGE_CN]->Own.Y;
	}

//	lStr.Txt = spItem[sLang];
	// 这个是为了反显的时候屏幕最左边也好看
	lStr.PS.X = 1;
//	lStr.PS.Y = lpItem->Pos * spItem[sLang]->Pixel.Y;

	DisStr(&lStr);
}


/**
 * @brief   显示菜单触发项，居中显示，一般是 选择和输入项
 *
 * @param   lpItem
 */
void Lcd__MenuItemMidDisp(S_Lcd__Item_Mid* lpItem)
{
	S_Lcd_String_Middle lStr;

	lStr.Str.Char = lpItem->Item.Char;

	if (*(lpItem->Item.Char) < 0x80)
	{
		lStr.Str.Txt = spItem[LANGUAGE_EN];
		lStr.Str.PS.Y = lpItem->Item.Pos *
//							spItem[LANGUAGE_EN]->Pixel.Y;
							spItem[LANGUAGE_EN]->Own.Y;
	}
	else
	{
		lStr.Str.Txt = spItem[LANGUAGE_CN];
		lStr.Str.PS.Y = lpItem->Item.Pos *
//							spItem[LANGUAGE_CN]->Pixel.Y;
							spItem[LANGUAGE_CN]->Own.Y;
	}

	// 这个是为了反显的时候屏幕最左边也好看
	lStr.Str.PS.X = CONFIG_ITEM_X_START;
	lStr.Len = lpItem->Len;

//	DisStr(&lStr);
	DisStrMiddle(&lStr);
}


/**
 * @brief   反显菜单项
 *
 * @param   lPos
 */
void Lcd__MenuItemRev(my_lcd_t lPos)
{
	// 例如，第一行子的Y方向的大小是 16,占据了 0 - 15 行，所以计算反显的时候要 - 1
	// 否则会多反显一行，可能会造成反显一行的右下角多了一小块，其实是反显的左下已经被下一行
	// 给遮住了，才显得右下多了一小块

	S_Lcd_Area_Rectangle lRec;

	lRec.PS.X = (CONFIG_ITEM_X_START > 0)?
						(CONFIG_ITEM_X_START - 1): 0;
//	lRec.PS.Y = lPos * spItem[sLang]->Pixel.Y;
	lRec.PS.Y = lPos * spItem[sLang]->Own.Y;
	lRec.PE.X = CONFIG_ITEM_X_END;
//	lRec.PE.Y = lRec.PS.Y + spItem[sLang]->Pixel.Y - 1;
	lRec.PE.Y = lRec.PS.Y + spItem[sLang]->Own.Y - 1;
	DisRecRev(&lRec);
}


/**
 * @brief   显示分割的虚线
 */
void Lcd__MenuDivLineDisp(void)
{
	S_Lcd_Line_Horizon lHor;

	lHor.XS = gLcdScreen.PS.X;
	lHor.XE = gLcdScreen.PE.X;
//	lHor.Y = CONFIG_DIV_LINE_POS * spItem[sLang]->Pixel.Y;
	lHor.Y = CONFIG_DIV_LINE_POS * spItem[sLang]->Own.Y;

	DisHorDotLinSet(&lHor);
}


/**
 * @brief   显示滚动条
 *
 * @param   lpScrollBar
 */
void Lcd__MenuScrollBarDisp(S_Lcd__ScrollBar* lpScrollBar)
{
	S_Lcd_Bar_Scroll lBar;

	lBar.X = CONFIG_SCROLL_BAR_X;
//	lBar.YS = CONFIG_SCROLL_BAR_POS_Y * spItem[sLang]->Pixel.Y;
	lBar.YS = CONFIG_SCROLL_BAR_POS_Y * spItem[sLang]->Own.Y;
	lBar.YE = gLcdScreen.PE.Y + 1 -
				CONFIG_SCROLL_BAR_POS_Y_END *
//					spItem[sLang]->Pixel.Y;
					spItem[sLang]->Own.Y;
	// 滚动条X 方向的扩展宽度
	lBar.SXEx = CONFIG_SCROLL_BAR_X_EX;
	// 滚动条Y方向的长度
	lBar.SYLen = lpScrollBar->Len;
	// 滚动条滑块的Y方向的坐标
	lBar.SYS = lpScrollBar->Y;

	DisScrollBar(&lBar);
}


// 滚动条字体指针
const static S_Lcd_Txt* spScrollBarTxt = &CONFIG_SCROLL_BAR_TXT;

/**
 * @brief   显示滚动条附属文字
 *
 * @param   lpChar
 */
void Lcd__MenuScrollBarTxtDisp(const char* lpChar)
{
	S_Lcd_String_Right lStr;

	lStr.Str.Char = lpChar;
	lStr.Len = CONFIG_SCROLL_BAR_TXT_LEN;
	lStr.Str.PS.X = gLcdScreen.PE.X + 1 -
					CONFIG_SCROLL_BAR_TXT_LEN *
//						spScrollBarTxt->Pixel.X;
						spScrollBarTxt->Own.X;
	lStr.Str.PS.Y = gLcdScreen.PE.Y + 1 -
//						spScrollBarTxt->Pixel.Y;
						spScrollBarTxt->Own.Y;
	lStr.Str.Txt = spScrollBarTxt;

	DisStrRight(&lStr);
}


// 菜单本身字体指针
const static S_Lcd_Txt* spMenuSelf[] =
{
		&CONFIG_SELF_EN,
		&CONFIG_SELF_CN,
};


/**
 * @brief   显示菜单本身文字
 *
 * @param   lpChar
 */
void Lcd__MenuSelfTxtDisp(const char* lpChar)
{
	S_Lcd_String lStr;

	lStr.Char = lpChar;
	lStr.PS.X = gLcdScreen.PS.X;
	lStr.PS.Y = gLcdScreen.PE.Y + 1 -
//						spMenuSelf[sLang]->Pixel.Y;
						spMenuSelf[sLang]->Own.Y;
	lStr.Txt = spMenuSelf[sLang];

	DisStr(&lStr);
}


// 菜单单位字体指针
const static S_Lcd_Txt* spMenuUnit = &CONFIG_MENU_UNIT;

/**
 * @brief   单位显示
 *
 * @param   lpUnit
 */
void Lcd__MenuUnitDisp(S_Lcd__Unit* lpUnit)
{
	S_Lcd_String_Right lStr;

	lStr.Str.Char = lpUnit->Char;

	lStr.Str.Txt = spMenuUnit;
	lStr.Len = CONFIG_MENU_UNIT_LEN;
//	lStr.Str.PS.X = lpUnit->X;
	lStr.Str.PS.X = CONFIG_ITEM_X_END - 1 -
//						lStr.Len * spMenuUnit->Pixel.X;
						lStr.Len * spMenuUnit->Own.X;
//	lStr.Str.PS.Y = lpUnit->Pos * spMenuUnit->Pixel.Y;
	lStr.Str.PS.Y = lpUnit->Pos * spMenuUnit->Own.Y;

	DisStrRight(&lStr);
}


/**
 * @brief   单位显示在有边框的情况下
 *
 * @param   lpUnit
 */
//void Lcd__FrameUnitDisp(S_Lcd__Unit* lpUnit)
//{
//	S_Lcd_String_Right lStr;
//
//	lStr.Str.Char = lpUnit->Char;
//	lStr.Str.Txt = spMenuUnit;
//	lStr.Len = CONFIG_MENU_UNIT_LEN;
////	lStr.Str.PS.X = lpUnit->X;
//	lStr.Str.PS.X = CONFIG_ITEM_X_END - 1 -
////						lStr.Len * spMenuUnit->Pixel.X;
//						lStr.Len * spMenuUnit->Own.X;
////	lStr.Str.PS.Y = lpUnit->Pos * spMenuUnit->Pixel.Y;
//	lStr.Str.PS.Y = lpUnit->Pos * spMenuUnit->Own.Y;
//
//	DisStrRight(&lStr);
//}


// 单位字体指针
const static S_Lcd_Txt* spUnit = &CONFIG_UNIT;

/**
 * @brief   单位显示
 *
 * @param   lpUnit
 */
void Lcd__UnitDisp(const char* lpUnit)
{
	S_Lcd_String_Right lStr;

	lStr.Str.Char = lpUnit;
	lStr.Str.Txt = spUnit;
	lStr.Str.PS.X = gLcdScreen.PE.X + 1 -
//						CONFIG_UNIT_LEN * spUnit->Pixel.X;
						CONFIG_UNIT_LEN * spUnit->Own.X;
//	lStr.Str.PS.Y = CONFIG_UNIT_POS * spUnit->Pixel.Y;
	lStr.Str.PS.Y = CONFIG_UNIT_POS * spUnit->Own.Y;
	lStr.Len = CONFIG_UNIT_LEN;

	DisStrRight(&lStr);
}


// 气体名称非数字字体指针
const static S_Lcd_Txt* spGasName[] =
{
		&CONFIG_GAS_NAME_EN_LCD,
		&CONFIG_GAS_NAME_CN_LCD,
};

// 气体名称数字字体指针
const static S_Lcd_Txt* spGasNameNum = &CONFIG_GAS_NAME_NUM;

/**
 * @brief   显示气体名称
 *
 * @param   lpName
 */
void Lcd__GasNameDisp(const char* lpName)
{
	if (sLang == LANGUAGE_EN)
	{
		S_Lcd_String_Dual lStr;

		lStr.Char = lpName;
		lStr.PS.X = gLcdScreen.PS.X;
		lStr.PS.Y = gLcdScreen.PE.Y + 1 -
//							spGasName[sLang]->Pixel.Y;
							spGasName[sLang]->Own.Y;
		lStr.TxtLarge = spGasName[sLang];
		lStr.TxtSmall = spGasNameNum;
		DisStrDual(&lStr);
	}
	else
	{
		S_Lcd_String lStr;

		lStr.Char = lpName;
		lStr.PS.X = gLcdScreen.PS.X;
		lStr.PS.Y = gLcdScreen.PE.Y + 1 -
//							spGasName[sLang]->Pixel.Y;
							spGasName[sLang]->Own.Y;
		lStr.Txt = spGasName[sLang];
		DisStr(&lStr);
	}
}


// 状态字体指针
const static S_Lcd_Txt* spState[] =
{
		&CONFIG_STATE_EN,
		&CONFIG_STATE_CN,
};

/**
 * @brief   显示状态 检测，高报，低报
 *
 * @param   lpState
 */
void Lcd__StatDisp(const char* lpState)
{
	S_Lcd_String_Right lStr;

	lStr.Str.Char = lpState;
	lStr.Str.Txt = spState[sLang];
	lStr.Str.PS.X = gLcdScreen.PE.X + 1 -
						CONFIG_STATE_LEN *
//							spState[LANGUAGE_EN]->Pixel.X;
							spState[LANGUAGE_EN]->Own.X;
//	lStr.Str.PS.Y = CONFIG_STATE_POS * spState[sLang]->Pixel.Y;
	lStr.Str.PS.Y = CONFIG_STATE_POS * spState[sLang]->Own.Y;
	lStr.Len = CONFIG_STATE_LEN;

	DisStrRight(&lStr);
}


// 气体数值数字字体指针
const static S_Lcd_Txt* spGasValueNum = &CONFIG_GAS_VALUE;

/**
 * @brief   显示气体数值
 *
 * @param   lpValue
 */
void Lcd__GasValueDisp(S_Value_U16* lpValue)
{
	S_Lcd_Value_Right_U16 lRight;
	uint8_t lData[7];

	lRight.Array.Value.Num = lpValue->Num;
	lRight.Array.Value.Point = lpValue->Point;
	lRight.Array.Char = lData;
//	lRight.Value.Len = CONFIG_GAS_VALUE_LEN;
	lRight.Str.Len = CONFIG_GAS_VALUE_LEN;
	lRight.Str.Str.Char = lData;
//	lRight.Str.Str.PS.X = gLcdScreen.PE.X + 1 -
//								CONFIG_UNIT_LEN * spUnit->Pixel.X -
//								CONFIG_GAS_VALUE_LEN * spGasValueNum->Pixel.X;
	lRight.Str.Str.PS.X = CONFIG_GAS_VALUE_X;
//	lRight.Str.Str.PS.Y = CONFIG_GAS_VALUE_POS * spUnit->Pixel.Y;
	lRight.Str.Str.PS.Y = CONFIG_GAS_VALUE_POS *
//								spUnit->Pixel.Y;
								spUnit->Own.Y;
	lRight.Str.Str.Txt = spGasValueNum;

//	DisStrRight(&lRight);
	DisNumRight(&lRight);
}


/**
 * @brief   清除气体数值
 */
void Lcd__GasValueClr(void)
{
	S_Lcd_Area_Rectangle lRec;

	lRec.PS.X = CONFIG_GAS_VALUE_X;
//	lRec.PS.Y = CONFIG_GAS_VALUE_POS * spUnit->Pixel.Y;
	lRec.PS.Y = CONFIG_GAS_VALUE_POS * spUnit->Own.Y;
	lRec.PE.X = lRec.PS.X +
					CONFIG_GAS_VALUE_LEN *
//						spGasValueNum->Pixel.X - 1;
						spGasValueNum->Own.X - 1;
//	lRec.PE.Y = lRec.PS.Y + spGasValueNum->Pixel.Y - 1;
	lRec.PE.Y = lRec.PS.Y + spGasValueNum->Own.Y - 1;

	DisRecFillClr(&lRec);
}


/**
 * @brief   显示菜单触发项，居中显示，一般是 选择和输入项，在Y方向，
 * 				以半行 8像素上下移动
 *
 * @param   lpItem
 */
my_lcd_t Lcd__FrameItemMidDispHalf(S_Lcd__Item_Mid* lpItem)
{
	S_Lcd_String_Middle lStr;

	lStr.Str.Char = lpItem->Item.Char;

	if (*(lpItem->Item.Char) < 0x80)
	{
		lStr.Str.Txt = spItem[LANGUAGE_EN];
		lStr.Str.PS.Y = (lpItem->Item.Pos *
//							spItem[LANGUAGE_EN]->Pixel.Y) >> 1;
							spItem[LANGUAGE_EN]->Own.Y) >> 1;
	}
	else
	{
		lStr.Str.Txt = spItem[LANGUAGE_CN];
		lStr.Str.PS.Y = (lpItem->Item.Pos *
//							spItem[LANGUAGE_CN]->Pixel.Y) >> 1;
							spItem[LANGUAGE_CN]->Own.Y) >> 1;
	}

//	lStr.Str.Txt = spItem[sLang];
	// 这个是为了反显的时候屏幕最左边也好看
	lStr.Str.PS.X = CONFIG_INPUT_REV_X_START + 1;
//	lStr.Str.PS.Y = (lpItem->Item.Pos * spItem[sLang]->Pixel.Y) >> 1;
	lStr.Len = lpItem->Len;

	DisStrMiddle(&lStr);

	return lStr.Str.PS.X;
}


/**
 * @brief   显示菜单触发项，居中显示，一般是 选择和输入项
 *
 * @param   lpItem
 */
my_lcd_t Lcd__FrameItemMidDisp(S_Lcd__Item_Mid* lpItem)
{
	lpItem->Item.Pos *= 2;
	return Lcd__FrameItemMidDispHalf(lpItem);
}



/**
 * @brief   反显输入菜单项，以半行作为显示的起点，比如说1/2行，1行，3/2行等等
 *
 * @param   lPos
 */
void Lcd__FrameItemRevHalf(my_lcd_t lPos)
{
	// 这个是为了反显的时候屏幕最左边也好看

	// 例如，第一行子的Y方向的大小是 16,占据了 0 - 15 行，所以计算反显的时候要 - 1
	// 否则会多反显一行，可能会造成反显一行的右下角多了一小块，其实是反显的左下已经被下一行
	// 给遮住了，才显得右下多了一小块

	S_Lcd_Area_Rectangle lRec;

	lRec.PS.X = CONFIG_INPUT_REV_X_START;
//	lRec.PS.Y = (lPos * spItem[sLang]->Pixel.Y) >> 1;
	lRec.PS.Y = (lPos * spItem[sLang]->Own.Y) >> 1;
	lRec.PE.X = CONFIG_INPUT_REV_X_END;
//	lRec.PE.Y = lRec.PS.Y + spItem[sLang]->Pixel.Y - 1;
	lRec.PE.Y = lRec.PS.Y + spItem[sLang]->Own.Y - 1;
	DisRecRev(&lRec);
}


/**
 * @brief   反显输入菜单项
 *
 * @param   lPos
 */
void Lcd__FrameItemRev(my_lcd_t lPos)
{
	Lcd__FrameItemRevHalf(lPos * 2);
}


/**
 * @brief   菜单处理某行清除，开始以半行为起点，也就是Y方向8个像素为起点
 */
void Lcd__FrameItemClrHalf(uint8_t lPos)
{
	S_Lcd_Area_Rectangle lRec;

	lRec.PS.X = CONFIG_INPUT_REV_X_START;
//	lRec.PS.Y = (lPos * spItem[sLang]->Pixel.Y) >> 1;
	lRec.PS.Y = (lPos * spItem[sLang]->Own.Y) >> 1;
	lRec.PE.X = CONFIG_INPUT_REV_X_END;
//	lRec.PE.Y = lRec.PS.Y + spItem[sLang]->Pixel.Y - 1;
	lRec.PE.Y = lRec.PS.Y + spItem[sLang]->Own.Y - 1;
	DisRecFillClr(&lRec);
}


/**
 * @brief   菜单处理某行清除，开始以半行为起点，也就是Y方向8个像素为起点
 */
void Lcd__FrameItemClr(uint8_t lPos)
{
	Lcd__FrameItemClrHalf(lPos * 2);
}


/**
 * @brief   菜单项最终处理数值显示，这个是数值输入时候显示，
 * 				当前的某一位处于闪烁状态
 * 				这个是数值输入的底层函数，被
 * 				MenuDisposeValueInputDisp 调用的
 *
 * @param   lpArray 显示数组
 * @param   lPos 放置位置
 * @param   lIndex 当前输入的位
 */
void Lcd__MenuInputValueBlinkDispHalf(S_Lcd__Blink* lpBlink)
{
	Lcd__FrameItemClrHalf(lpBlink->Trig.Item.Pos);

	// 居中显示，获得当前的居中的开始位置
	my_lcd_t lX;

	lX = Lcd__FrameItemMidDispHalf(&(lpBlink->Trig));

	// 反显某一位
	S_Lcd_Area_Rectangle lRec;
	lRec.PS.X = lX + lpBlink->Index *
//					spItem[LANGUAGE_EN]->Pixel.X;
					spItem[LANGUAGE_EN]->Own.X;
	lRec.PS.Y = (lpBlink->Trig.Item.Pos *
//					spItem[LANGUAGE_EN]->Pixel.Y) >> 1;
					spItem[LANGUAGE_EN]->Own.Y) >> 1;
//	lRec.PE.X = lRec.PS.X + spItem[LANGUAGE_EN]->Pixel.X - 1;
	lRec.PE.X = lRec.PS.X + spItem[LANGUAGE_EN]->Own.X - 1;
//	lRec.PE.Y = lRec.PS.Y + spItem[LANGUAGE_EN]->Pixel.Y - 1;
	lRec.PE.Y = lRec.PS.Y + spItem[LANGUAGE_EN]->Own.Y - 1;

	DisBlinkSet(&lRec);
}

