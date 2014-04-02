/**
 * @file    display_app.c
 * @brief   
 * @author  ptz
 * @email   ptz19861212@163.com
 * @version 0.0.1
 * @date    2014-01-06 17:08:15 星期一 
 * @history (1).2014-01-06 17:08:15 星期一 create
 */
/* Copyright (C)
 * 
 * My own license
 * All right reserved
 * 
 */

#include "display_app_in.h"

/**
 * @brief   显示正确状态
 *
 * @param   lX
 * @param   lY
 */
//void DisSymCor(uint8_t lX, uint8_t lY)
//{
//	S_Lcd_Char lChar;
//
//	lChar.Font = DIS_SYM_COR_FONT;
//	lChar.PS.X = lX;
//	lChar.PS.Y = lY;
//	lChar.Size.X = DIS_SYM_COR_SIZE_X;
//	lChar.Size.Y = DIS_SYM_COR_SIZE_Y;
//
//	DisCharSet(&lChar);
//}

/**
 * @brief   显示错误状态
 *
 * @param   lX
 * @param   lY
 */
//void DisSymWron(uint8_t lX, uint8_t lY)
//{
////	DisCharSet(lX, lY, DIS_SYM_WRON_FONT, DIS_SYM_WRON_SIZE_X,
////				DIS_SYM_WRON_SIZE_Y);
//
//	S_Lcd_Char lChar;
//
//	lChar.Font = DIS_SYM_WRON_FONT;
//	lChar.PS.X = lX;
//	lChar.PS.Y = lY;
//	lChar.Size.X = DIS_SYM_WRON_SIZE_X;
//	lChar.Size.Y = DIS_SYM_WRON_SIZE_Y;
//
//	DisCharSet(&lChar);
//}

/**
 * @brief   显示报警状态
 *
 * @param   lX
 * @param   lpAlar
 * @param   lY
 */
//void DisSymAlar(const uint8_t *lpAlar, uint8_t lX, uint8_t lY)
//{
//	DisStr(lpAlar, lX, lY, DIS_SYM_ALAR_FONT, DIS_SYM_ALAR_SIZE_X,
//			DIS_SYM_ALAR_SIZE_Y, DIS_SYM_ALAR_SIZE);
//
//}

/**
 * @brief   反显报警状态
 *
 * @param   lX
 * @param   lY
 */
//void DisSymAlarRev(uint8_t lX, uint8_t lY)
//{
//	S_Lcd_Area_Rectangle lRec;
//
//	lRec.PS.X = lX - 2;
//	lRec.PS.Y = lY;
//	lRec.PE.X = lX + 5 * DIS_SYM_ALAR_SIZE_X + 1;
//	lRec.PE.Y = lY + DIS_SYM_ALAR_SIZE_Y;
//
//	DisRecRev(&lRec);
//}

/**
 * @brief   清除报警状态
 *
 * @param   lX
 * @param   lY
 */
//void DisSymAlarClr(uint8_t lX, uint8_t lY)
//{
//	S_Lcd_Area_Rectangle lRec;
//
//	lRec.PS.X = lX - 2;
//	lRec.PS.Y = lY;
//	lRec.PE.X = lX + 5 * DIS_SYM_ALAR_SIZE_X + 1;
//	lRec.PE.Y = lY + DIS_SYM_ALAR_SIZE_Y;
//
//	DisRecFillClr(&lRec);
//}



/**
 * @brief   显示风扇
 */
void Lcd__FanDisp(void)
{
	S_Lcd_Char lChar;
	static uint8_t sDisSymFanCount = 0;

	lChar.Font = gLcdSymbolFan.Font +
					sDisSymFanCount * gLcdSymbolFan.Size;

//	switch (sDisSymFanCount)
//	{
//		case DIS_SYM_FAN_1:
//			lChar.Font = DIS_SYM_FAN_FONT + DIS_SYM_FAN_SIZE * 1;
//			break;
//
//		case DIS_SYM_FAN_2:
//			lChar.Font = DIS_SYM_FAN_FONT + DIS_SYM_FAN_SIZE * 2;
//			break;
//
//		case DIS_SYM_FAN_ALL:
//			lChar.Font = DIS_SYM_FAN_FONT + DIS_SYM_FAN_SIZE * 0;
//			break;
//	}

	lChar.PS.X = CONFIG_FAN_X;
	lChar.PS.Y = CONFIG_FAN_Y;
	lChar.Pixel.X = gLcdSymbolFan.Pixel.X;
	lChar.Pixel.Y = gLcdSymbolFan.Pixel.Y;

	DisCharSet(&lChar);

	sDisSymFanCount++;

	// >2 是显示3个
//	if (sDisSymFanCount > 2)
	// >1 只有两个循环显示
//	if (sDisSymFanCount > 1)
	if (sDisSymFanCount > 0)
	{
		sDisSymFanCount = 0;
	}
}

//void DisSymFan(S_Lcd_Point* lpPoint)
//{
//	S_Lcd_Char lChar;
//	static uint8_t sDisSymFanCount = 1;
//
//	switch (sDisSymFanCount)
//	{
//		case DIS_SYM_FAN_1:
//			lChar.Font = DIS_SYM_FAN_FONT + DIS_SYM_FAN_SIZE * 1;
//			break;
//
//		case DIS_SYM_FAN_2:
//			lChar.Font = DIS_SYM_FAN_FONT + DIS_SYM_FAN_SIZE * 2;
//			break;
//
//		case DIS_SYM_FAN_ALL:
//			lChar.Font = DIS_SYM_FAN_FONT + DIS_SYM_FAN_SIZE * 0;
//			break;
//	}
//
//	lChar.PS.X = lpPoint->X;
//	lChar.PS.Y = lpPoint->Y;
//	lChar.Size.X = DIS_SYM_FAN_SIZE_X;
//	lChar.Size.Y = DIS_SYM_FAN_SIZE_Y;
//
//	DisCharSet(&lChar);
//
//	sDisSymFanCount++;
//
//	if (sDisSymFanCount > 3)
//	{
//		sDisSymFanCount = 1;
//	}
//}


/**
 * @brief   清除风扇
 */
void Lcd__FanClr(void)
{
	S_Lcd_Area_Rectangle lRec;

	lRec.PS.X = CONFIG_FAN_X;
	lRec.PS.Y = CONFIG_FAN_Y;
	lRec.PE.X = CONFIG_FAN_X + gLcdSymbolFan.Pixel.X;
	lRec.PE.Y = CONFIG_FAN_Y + gLcdSymbolFan.Pixel.Y;

	DisRecFillClr(&lRec);
}

//void DisSymFanClr(S_Lcd_Point* lpPoint)
//{
//	S_Lcd_Area_Rectangle lRec;
//
//	lRec.PS.X = lpPoint->X;
//	lRec.PS.Y = lpPoint->Y;
//	lRec.PE.X = lpPoint->X + DIS_SYM_FAN_SIZE_X;
//	lRec.PE.Y = lpPoint->Y + DIS_SYM_FAN_SIZE_Y;
//
//	DisRecFillClr(&lRec);
//}

/**
 * @brief   显示充电状态
 */
void Lcd__ChargeDisp(void)
{
	S_Lcd_Char lChar;

	lChar.Font = gLcdSymbolCharge.Font;
	lChar.PS.X = CONFIG_CHARGE_X;
	lChar.PS.Y = CONFIG_CHARGE_Y;
	lChar.Pixel.X = gLcdSymbolCharge.Pixel.X;
	lChar.Pixel.Y = gLcdSymbolCharge.Pixel.Y;

	DisCharSet(&lChar);
}

//void DisSymChar(uint8_t lX, uint8_t lY)
//{
////	DisCharSet(lX, lY, DIS_SYM_CHAR_FONT, DIS_SYM_CHAR_SIZE_X,
////				DIS_SYM_CHAR_SIZE_Y);
//
//	S_Lcd_Char lChar;
//
//	lChar.Font = DIS_SYM_CHAR_FONT;
//	lChar.PS.X = lX;
//	lChar.PS.Y = lY;
//	lChar.Size.X = DIS_SYM_CHAR_SIZE_X;
//	lChar.Size.Y = DIS_SYM_CHAR_SIZE_Y;
//
//	DisCharSet(&lChar);
//}

/**
 * @brief   清除充电状态
 */
void Lcd__ChargeClr(void)
{
	S_Lcd_Area_Rectangle lRec;

	lRec.PS.X = CONFIG_CHARGE_X;
	lRec.PS.Y = CONFIG_CHARGE_Y;
	lRec.PE.X = CONFIG_CHARGE_X + gLcdSymbolCharge.Pixel.X;
	lRec.PE.Y = CONFIG_CHARGE_Y + gLcdSymbolCharge.Pixel.Y;

	DisRecFillClr(&lRec);
}


//void DisSymCharClr(uint8_t lX, uint8_t lY)
//{
//	S_Lcd_Area_Rectangle lRec;
//
//	lRec.PS.X = lX;
//	lRec.PS.Y = lY;
//	lRec.PE.X = lX + DIS_SYM_CHAR_SIZE_X;
//	lRec.PE.Y = lY + DIS_SYM_CHAR_SIZE_Y;
//
//	DisRecFillClr(&lRec);
////	DisRecFillClr(lX, lY, lX + DIS_SYM_CHAR_SIZE_X, lY + DIS_SYM_CHAR_SIZE_Y);
//}


/**
 * @brief   显示大号充电状态
 */
void Lcd__ChargeLargeDisp(void)
{
	S_Lcd_Char lChar;

	lChar.Font = gLcdSymbolChargeLarge.Font;
	lChar.PS.X = CONFIG_CHARGE_LARGE_X;
	lChar.PS.Y = CONFIG_CHARGE_LARGE_Y;
	lChar.Pixel.X = gLcdSymbolChargeLarge.Pixel.X;
	lChar.Pixel.Y = gLcdSymbolChargeLarge.Pixel.Y;

	DisCharSet(&lChar);
}


/**
 * @brief   显示大号充电状态
 */
//void DisSymCharLar(uint8_t lX, uint8_t lY)
//{
////	DisCharSet(lX, lY, DIS_SYM_CHAR_LAR_FONT, DIS_SYM_CHAR_LAR_SIZE_X,
////				DIS_SYM_CHAR_LAR_SIZE_Y);
//
//	S_Lcd_Char lChar;
//
//	lChar.Font = DIS_SYM_CHAR_LAR_FONT;
//	lChar.PS.X = lX;
//	lChar.PS.Y = lY;
//	lChar.Size.X = DIS_SYM_CHAR_LAR_SIZE_X;
//	lChar.Size.Y = DIS_SYM_CHAR_LAR_SIZE_Y;
//
//	DisCharSet(&lChar);
//}

/**
 * @brief   显示大号充满状态
 */
void Lcd__ChargeFullLargeDisp(void)
{
	S_Lcd_Char lChar;

	lChar.Font = gLcdSymbolChargeFullLarge.Font;
	lChar.PS.X = CONFIG_CHARGE_FULL_LARGE_X;
	lChar.PS.Y = CONFIG_CHARGE_FULL_LARGE_Y;
	lChar.Pixel.X = gLcdSymbolChargeFullLarge.Pixel.X;
	lChar.Pixel.Y = gLcdSymbolChargeFullLarge.Pixel.Y;

	DisCharSet(&lChar);
}

//void DisSymFull(uint8_t lX, uint8_t lY)
//{
////	DisCharSet(lX, lY, DIS_SYM_FULL_FONT, DIS_SYM_FULL_SIZE_X,
////				DIS_SYM_FULL_SIZE_Y);
//
//	S_Lcd_Char lChar;
//
//	lChar.Font = DIS_SYM_FULL_FONT;
//	lChar.PS.X = lX;
//	lChar.PS.Y = lY;
//	lChar.Size.X = DIS_SYM_FULL_SIZE_X;
//	lChar.Size.Y = DIS_SYM_FULL_SIZE_Y;
//
//	DisCharSet(&lChar);
//}

/**
 * @brief   显示电池状态
 *
 * @param   lValue
 */
void Lcd__BatDisp(uint8_t lValue)
{
	uint8_t lBat = BAT_NONE;

	if (lValue >= DIS_SYM_BAT_80)
	{
		lBat = BAT_100;
	}
	else if (lValue >= DIS_SYM_BAT_60)
	{
		lBat = BAT_80;
	}
	else if (lValue >= DIS_SYM_BAT_40)
	{
		lBat = BAT_60;
	}
	else if (lValue >= DIS_SYM_BAT_20)
	{
		lBat = BAT_40;
	}
	else if (lValue >= DIS_SYM_BAT_5)
	{
		lBat = BAT_20;
	}
	else
	{
		lBat = BAT_NONE;
	}

//	if (lValue >= DIS_SYM_BAT_100)
//	{
//		lBat = BAT_100;
//	}
//	else if (lValue >= DIS_SYM_BAT_80)
//	{
//		lBat = BAT_80;
//	}
//	else if (lValue >= DIS_SYM_BAT_60)
//	{
//		lBat = BAT_60;
//	}
//	else if (lValue >= DIS_SYM_BAT_40)
//	{
//		lBat = BAT_40;
//	}
//	else if (lValue >= DIS_SYM_BAT_20)
//	{
//		lBat = BAT_20;
//	}
//	else
//	{
//		lBat = BAT_NONE;
//	}

//	S_Device* lpDev;
//	StateDevicePointGet(&lpDev);

	// 电池电量小于 20% 的时候，电池符号闪烁
//	if (lBat == BAT_80 && lpDev->pTemp->Blink == BLINK_OFF) {
//		S_Lcd_Area_Rectangle lRec;
//
//		lRec.PS.X = CONFIG_BAT_X;
//		lRec.PS.Y = CONFIG_BAT_Y;
//		lRec.PE.X = CONFIG_BAT_X + gLcdSymbolBat.Pixel.X;
//		lRec.PE.Y = CONFIG_BAT_Y + gLcdSymbolBat.Pixel.Y;
//		// 清除电池符号
//		DisRecFillClr(&lRec);
//	// 电池电量大于 20% 的时候，电池符号正常显示
//	} else {
//		S_Lcd_Char lChar;
//
//		lChar.Font = gLcdSymbolBat.Font + lBat * gLcdSymbolBat.Size;
//
//		lChar.PS.X = CONFIG_BAT_X;
//		lChar.PS.Y = CONFIG_BAT_Y;
//		lChar.Pixel.X = gLcdSymbolBat.Pixel.X;
//		lChar.Pixel.Y = gLcdSymbolBat.Pixel.Y;
//		// 显示电池符号
//		DisCharSet(&lChar);
//	}


	S_Lcd_Char lChar;

	lChar.Font = gLcdSymbolBat.Font + lBat * gLcdSymbolBat.Size;

	lChar.PS.X = CONFIG_BAT_X;
	lChar.PS.Y = CONFIG_BAT_Y;
	lChar.Pixel.X = gLcdSymbolBat.Pixel.X;
	lChar.Pixel.Y = gLcdSymbolBat.Pixel.Y;
	// 显示电池符号
	DisCharSet(&lChar);

}

//void DisSymBat(uint8_t lValue, uint8_t lX, uint8_t lY)
////void DisSymBat(uint8_t lValue, S_Lcd_Point* lpPoint)
//{
//	uint8_t lBat = DIS_SYM_BAT_NONE;
//
//	if (lValue >= DIS_SYM_BAT_100)
//	{
//		lBat = DIS_SYM_BAT_100;
//	}
//	else if (lValue >= DIS_SYM_BAT_80)
//	{
//		lBat = DIS_SYM_BAT_80;
//	}
//	else if (lValue >= DIS_SYM_BAT_60)
//	{
//		lBat = DIS_SYM_BAT_60;
//	}
//	else if (lValue >= DIS_SYM_BAT_40)
//	{
//		lBat = DIS_SYM_BAT_40;
//	}
//	else if (lValue >= DIS_SYM_BAT_20)
//	{
//		lBat = DIS_SYM_BAT_20;
//	}
//	else
//	{
//		lBat = DIS_SYM_BAT_NONE;
//	}
//
//	S_Lcd_Char lChar;
//
//	switch (lBat)
//	{
//		case DIS_SYM_BAT_NONE:
//			lChar.Font = DIS_SYM_BAT_FONT + FONT_SYMBOL_BAT_NONE *
//								DIS_SYM_BAT_SIZE;
//
////			DisCharSet(lX, lY, (DIS_SYM_BAT_FONT + FONT_SYMBOL_BAT_NONE
////						* DIS_SYM_BAT_SIZE), DIS_SYM_BAT_SIZE_X,
////						DIS_SYM_BAT_SIZE_Y);
//			break;
//		case DIS_SYM_BAT_20:
//			lChar.Font = DIS_SYM_BAT_FONT + FONT_SYMBOL_BAT_20 *
//								DIS_SYM_BAT_SIZE;
//
////			DisCharSet(lX, lY, (DIS_SYM_BAT_FONT + FONT_SYMBOL_BAT_20
////						* DIS_SYM_BAT_SIZE), DIS_SYM_BAT_SIZE_X,
////						DIS_SYM_BAT_SIZE_Y);
//			break;
//		case DIS_SYM_BAT_40:
//			lChar.Font = DIS_SYM_BAT_FONT + FONT_SYMBOL_BAT_40 *
//								DIS_SYM_BAT_SIZE;
////			DisCharSet(lX, lY, (DIS_SYM_BAT_FONT + FONT_SYMBOL_BAT_40
////						* DIS_SYM_BAT_SIZE), DIS_SYM_BAT_SIZE_X,
////						DIS_SYM_BAT_SIZE_Y);
//			break;
//		case DIS_SYM_BAT_60:
//			lChar.Font = DIS_SYM_BAT_FONT + FONT_SYMBOL_BAT_60 *
//								DIS_SYM_BAT_SIZE;
////			DisCharSet(lX, lY, (DIS_SYM_BAT_FONT + FONT_SYMBOL_BAT_60
////						* DIS_SYM_BAT_SIZE), DIS_SYM_BAT_SIZE_X,
////						DIS_SYM_BAT_SIZE_Y);
//			break;
//		case DIS_SYM_BAT_80:
//			lChar.Font = DIS_SYM_BAT_FONT + FONT_SYMBOL_BAT_80 *
//								DIS_SYM_BAT_SIZE;
////			DisCharSet(lX, lY, (DIS_SYM_BAT_FONT + FONT_SYMBOL_BAT_80
////						* DIS_SYM_BAT_SIZE), DIS_SYM_BAT_SIZE_X,
////						DIS_SYM_BAT_SIZE_Y);
//			break;
//		case DIS_SYM_BAT_100:
//			lChar.Font = DIS_SYM_BAT_FONT + FONT_SYMBOL_BAT_100 *
//								DIS_SYM_BAT_SIZE;
////			DisCharSet(lX, lY, (DIS_SYM_BAT_FONT + FONT_SYMBOL_BAT_100
////						* DIS_SYM_BAT_SIZE), DIS_SYM_BAT_SIZE_X,
////						DIS_SYM_BAT_SIZE_Y);
//			break;
//		case DIS_SYM_BAT_FULL:
//			lChar.Font = DIS_SYM_BAT_FONT + FONT_SYMBOL_BAT_FULL *
//								DIS_SYM_BAT_SIZE;
////			DisCharSet(lX, lY, (DIS_SYM_BAT_FONT + FONT_SYMBOL_BAT_FULL
////						* DIS_SYM_BAT_SIZE), DIS_SYM_BAT_SIZE_X,
////						DIS_SYM_BAT_SIZE_Y);
//			break;
//		default:
//			break;
//	}
//
//	lChar.PS.X = lX;
//	lChar.PS.Y = lY;
//	lChar.Size.X = DIS_SYM_BAT_SIZE_X;
//	lChar.Size.Y = DIS_SYM_BAT_SIZE_Y;
//
//	DisCharSet(&lChar);
//}
