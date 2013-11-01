/**
 * @file    display_uc1701.c
 * @brief   显示驱动
 * @author  ptz
 * @email   ptz19861212@163.com
 * @version 0.0.1
 * @date    2013-08-13 15:18:46 星期二 
 * @history (1).2013-08-13 15:18:46 星期二 create
 */
/* Copyright (C)
 * 
 * My own license
 * All right reserved
 * 
 */

#include "display_uc1701_in.h"


/**
 * @brief   数字转换为字符串
 *
 * @param   lpData
 * @param   lNum
 * @param   lPoint
 */
static void NumTurn16(uint8_t *lpData, uint16_t lNum, uint8_t lPoint)
{
	uint8_t lI; 
	uint16_t lDiv1, lDiv2, lDiv3, lDiv4, lDiv5;
	lDiv1 = lDiv2 = lDiv3 = lDiv4 = lDiv5 = 0;

	for (lI = 0; lI < 6; lI++) 
		*(lpData + lI) = 0;

	lDiv1 = DIV_U16_10(lNum);
	*lpData = lNum - 10 * lDiv1 + '0';

	if (lNum >= 10) 
	{ 
		lDiv2 = DIV_U16_10(lDiv1);
		*(lpData + 1) = lDiv1 - 10 * lDiv2 + '0';
	}
	if (lNum >= 100) 
	{
		lDiv3 = DIV_U16_10(lDiv2);
		*(lpData + 2) = lDiv2 - 10 * lDiv3 + '0';
	}
	if (lNum >= 1000) 
	{
		lDiv4 = DIV_U16_10(lDiv3);
		*(lpData + 3) = lDiv3 - 10 * lDiv4 + '0';
	}
	if (lNum >= 10000) 
	{
		lDiv5 = DIV_U16_10(lDiv4);
		*(lpData + 4) = lDiv4 - 10 * lDiv5 + '0';
	}

	// 移出小数点的位置
	if (lPoint != POINT_HHHHH)
	{
		for (lI = 0; lI < (5 - lPoint); lI++)
			*(lpData + 5 - lI) = *(lpData + 5 - lI - 1);
	}
	else
		lI = 0;

	if (lI > 0)
	{
		// 添加小数点
		*(lpData + lPoint) = '.';

		if (*(lpData + lPoint + 1) == 0)
		{
			// 有需要的在小数点前面补0
			*(lpData + lPoint + 1) = '0';

			for (lI = 1; lI < lPoint; lI++)
			{
				// 如果小数点后面有补0的
				if (*(lpData + lPoint - lI) == 0)
					*(lpData + lPoint - lI) = '0';
				else
					break;
			}
		}
	}

	// 字符串交换变成正序。
	CharSwap(lpData, 6);
	// 字符串结束附。
	*(lpData + 6) = 0;
}

/**
 * @brief   显示大小一致的字符串
 *
 * @param   lpUnit
 * @param   lX
 * @param   lY
 * @param   lpFont
 * @param   lXSize
 * @param   lYSize
 * @param   lFSize
 */
void DisStr(uint8_t *lpStr, uint8_t lX, uint8_t lY, const uint8_t *lpFont, 
			uint8_t lXSize, uint8_t lYSize, uint8_t lFSize)
{
	uint8_t lTemp, lI;

	lI = 0;

	while (*(lpStr + lI))
	{
		lTemp = *(lpStr + lI) - FONT_ASCII_OMIT;
		DisCharSet((lX + lI * lXSize), lY, (lpFont + lTemp * lFSize), 
					lXSize, lYSize);
		lI++;
	}
}

/**
 * @brief   显示特殊的字符串，英文是一个大小，数字是另一个大小
 *
 * @param   lpStr
 * @param   lX
 * @param   lY
 * @param   lpFont1
 * @param   lXSize1
 * @param   lYSize1
 * @param   lFSize1
 * @param   lpFont2
 * @param   lXSize2
 * @param   lYSize2
 * @param   lFSize2
 */
void DisStrEx(uint8_t *lpStr, uint8_t lX, uint8_t lY, 
				const uint8_t *lpFont1, uint8_t lXSize1, uint8_t lYSize1, 
				uint8_t lFSize1, const uint8_t *lpFont2, uint8_t lXSize2, 
				uint8_t lYSize2, uint8_t lFSize2)
{
	uint8_t lTmp, lI;
	uint8_t lXTmp, lYEx;

	lI = 0;
	lXTmp = lX;
	lYEx = lY + (lYSize1 - lYSize2);


	while (*(lpStr + lI))
	{
		lTmp = *(lpStr + lI);

		if ((lTmp <= '9') && (lTmp >= '0'))
		{
			lTmp -= FONT_ASCII_OMIT;
			DisCharSet(lXTmp, lYEx, (lpFont2 + lTmp * lFSize2), 
					lXSize2, lYSize2);
			lXTmp += lXSize2;
		}
		else
		{
			lTmp -= FONT_ASCII_OMIT;
			DisCharSet(lXTmp, lY, (lpFont1 + lTmp * lFSize1), 
					lXSize1, lYSize1);
			lXTmp += lXSize1;
		}

		lI++;
	} //end of while (*(lpStr + lI))
}

/**
 * @brief   显示数字 数字区域都受影响
 *
 * @param   lNum
 * @param   lPoint
 * @param   lX
 * @param   lY
 * @param   lpFont
 * @param   lXSize
 * @param   lYSize
 * @param   lFSize
 */
void DisNum(uint16_t lNum, uint8_t lPoint, uint8_t lX, uint8_t lY, 
			const uint8_t *lpFont, uint8_t lXSize, uint8_t lYSize, 
			uint8_t lFSize)
{
	uint8_t lI, lTemp;
	uint8_t lData[7];

	NumTurn16(lData, lNum, lPoint);

	DisStr(lData, lX, lY, lpFont, lXSize, lYSize, lFSize);
}

/**
 * @brief   显示16x32的数字
 *
 * @param   lNum
 * @param   lPoint
 * @param   lX
 * @param   lY
 */
void DisNum16x32(uint16_t lNum, uint8_t lPoint, uint8_t lX, uint8_t lY)
{
	DisNum(lNum, lPoint, lX, lY, FONT_ASCII_16X32, FONT_ASCII_16X32_SIZE_X,
			FONT_ASCII_16X32_SIZE_Y, FONT_ASCII_16X32_SIZE);
}

/**
 * @brief   显示8x16的数字
 *
 * @param   lNum
 * @param   lPoint
 * @param   lX
 * @param   lY
 */
void DisNum8x16(uint16_t lNum, uint8_t lPoint, uint8_t lX, uint8_t lY)
{
	DisNum(lNum, lPoint, lX, lY, FONT_ASCII_16X32, FONT_ASCII_8X16_SIZE_X,
			FONT_ASCII_8X16_SIZE_Y, FONT_ASCII_8X16_SIZE);
}

/**
 * @brief   单位显示
 *
 * @param   lpUnit
 * @param   lX
 * @param   lY
 */
void DisUnit(uint8_t *lpUnit, uint8_t lX, uint8_t lY)
{
	DisStr(lpUnit, lX, lY, DIS_UNIT_FONT, DIS_UNIT_SIZE_X, DIS_UNIT_SIZE_Y,
			DIS_UNIT_SIZE);
}

/**
 * @brief   显示气体名称
 *
 * @param   lpName
 * @param   lX
 * @param   lY
 */
void DisGasName(uint8_t *lpName, uint8_t lX, uint8_t lY)
{
	DisStrEx(lpName, lX, lY, DIS_GAS_NAME_ASCII_FONT, 
				DIS_GAS_NAME_ASCII_SIZE_X, DIS_GAS_NAME_ASCII_SIZE_Y, 
				DIS_GAS_NAME_ASCII_SIZE, DIS_GAS_NAME_NUM_FONT, 
				DIS_GAS_NAME_NUM_SIZE_X, DIS_GAS_NAME_NUM_SIZE_Y, 
				DIS_GAS_NAME_NUM_SIZE);
}

/**
 * @brief   显示状态 检测，高报，低报
 *
 * @param   lpStat
 * @param   lX
 * @param   lY
 */
void DisStat(uint8_t *lpStat, uint8_t lX, uint8_t lY)
{
	DisStr(lpStat, lX, lY, DIS_STAT_FONT, DIS_STAT_SIZE_X, DIS_STAT_SIZE_Y,
			DIS_STAT_SIZE);
}

/**
 * @brief   显示正确状态
 *
 * @param   lX
 * @param   lY
 */
void DisSymCor(uint8_t lX, uint8_t lY)
{
	DisCharSet(lX, lY, DIS_SYM_COR_FONT, DIS_SYM_COR_SIZE_X, 
				DIS_SYM_COR_SIZE_Y);
}

/**
 * @brief   显示错误状态
 *
 * @param   lX
 * @param   lY
 */
void DisSymWron(uint8_t lX, uint8_t lY)
{
	DisCharSet(lX, lY, DIS_SYM_WRON_FONT, DIS_SYM_WRON_SIZE_X, 
				DIS_SYM_WRON_SIZE_Y);
}

/**
 * @brief   显示报警状态
 *
 * @param   lX
 * @param   lpAlar
 * @param   lY
 */
void DisSymAlar(uint8_t *lpAlar, uint8_t lX, uint8_t lY)
{
	DisStr(lpAlar, lX, lY, DIS_SYM_ALAR_FONT, DIS_SYM_ALAR_SIZE_X, 
			DIS_SYM_ALAR_SIZE_Y, DIS_SYM_ALAR_SIZE);
}

/**
 * @brief   反显报警状态
 *
 * @param   lX
 * @param   lY
 */
void DisSymAlarRev(uint8_t lX, uint8_t lY)
{
	DisRecRev(lX - 2, lY, (lX + 5 * DIS_SYM_ALAR_SIZE_X + 1), 
				(lY + DIS_SYM_ALAR_SIZE_Y));
}

/**
 * @brief   显示风扇
 *
 * @param   lX
 * @param   lY
 */
void DisSymFan(uint8_t lX, uint8_t lY)
{
	DisCharSet(lX, lY, DIS_SYM_FAN_FONT, DIS_SYM_FAN_SIZE_X, 
				DIS_SYM_FAN_SIZE_Y);
}

/**
 * @brief   显示充电状态
 *
 * @param   lX
 * @param   lY
 */
void DisSymChar(uint8_t lX, uint8_t lY)
{
	DisCharSet(lX, lY, DIS_SYM_CHAR_FONT, DIS_SYM_CHAR_SIZE_X, 
				DIS_SYM_CHAR_SIZE_Y);
}

/**
 * @brief   显示大号充电状态
 *
 * @param   lX
 * @param   lY
 */
void DisSymCharLar(uint8_t lX, uint8_t lY)
{
	DisCharSet(lX, lY, DIS_SYM_CHAR_LAR_FONT, DIS_SYM_CHAR_LAR_SIZE_X, 
				DIS_SYM_CHAR_LAR_SIZE_Y);
}

/**
 * @brief   显示大号充满状态
 *
 * @param   lX
 * @param   lY
 */
void DisSymFull(uint8_t lX, uint8_t lY)
{
	DisCharSet(lX, lY, DIS_SYM_FULL_FONT, DIS_SYM_FULL_SIZE_X, 
				DIS_SYM_FULL_SIZE_Y);
}

/**
 * @brief   显示电池状态
 *
 * @param   lBat
 * @param   lX
 * @param   lY
 */
void DisSymBat(uint8_t lBat, uint8_t lX, uint8_t lY)
{
	switch (lBat)
	{
		case DIS_SYM_BAT_NONE:
			DisCharSet(lX, lY, (DIS_SYM_BAT_FONT + FONT_SYMBOL_BAT_NONE
						* DIS_SYM_BAT_SIZE), DIS_SYM_BAT_SIZE_X, 
						DIS_SYM_BAT_SIZE_Y);
			break;
		case DIS_SYM_BAT_20:
			DisCharSet(lX, lY, (DIS_SYM_BAT_FONT + FONT_SYMBOL_BAT_20
						* DIS_SYM_BAT_SIZE), DIS_SYM_BAT_SIZE_X, 
						DIS_SYM_BAT_SIZE_Y);
			break;
		case DIS_SYM_BAT_40:
			DisCharSet(lX, lY, (DIS_SYM_BAT_FONT + FONT_SYMBOL_BAT_40
						* DIS_SYM_BAT_SIZE), DIS_SYM_BAT_SIZE_X, 
						DIS_SYM_BAT_SIZE_Y);
			break;
		case DIS_SYM_BAT_60:
			DisCharSet(lX, lY, (DIS_SYM_BAT_FONT + FONT_SYMBOL_BAT_60
						* DIS_SYM_BAT_SIZE), DIS_SYM_BAT_SIZE_X, 
						DIS_SYM_BAT_SIZE_Y);
			break;
		case DIS_SYM_BAT_80:
			DisCharSet(lX, lY, (DIS_SYM_BAT_FONT + FONT_SYMBOL_BAT_80
						* DIS_SYM_BAT_SIZE), DIS_SYM_BAT_SIZE_X, 
						DIS_SYM_BAT_SIZE_Y);
			break;
		case DIS_SYM_BAT_100:
			DisCharSet(lX, lY, (DIS_SYM_BAT_FONT + FONT_SYMBOL_BAT_100
						* DIS_SYM_BAT_SIZE), DIS_SYM_BAT_SIZE_X, 
						DIS_SYM_BAT_SIZE_Y);
			break;
		case DIS_SYM_BAT_FULL:
			DisCharSet(lX, lY, (DIS_SYM_BAT_FONT + FONT_SYMBOL_BAT_FULL
						* DIS_SYM_BAT_SIZE), DIS_SYM_BAT_SIZE_X, 
						DIS_SYM_BAT_SIZE_Y);
			break;
		default:
			break;
	}
}

/**
 * @brief   获得多个字符之间的等分间隔
 *
 * @param   lLenSum
 * @param   lLenChar
 * @param   lNum
 *
 * @return  
 */
uint8_t DisGapGet(uint8_t lLenSum, uint8_t lLenChar, uint8_t lNum)
{
	return ((lLenSum - lLenChar * lNum) / (lNum + 1));
}

/**
 * @brief   画点
 *
 * @param   lX
 * @param   lY
 */
void DisDotSet(uint8_t lX, uint8_t lY)
{
	UC1701_CorCvt(&lX, &lY);
	UC1701_DrawDotSet(lX, lY);
}

/**
 * @brief   清除点
 *
 * @param   lX
 * @param   lY
 */
void DisDotClr(uint8_t lX, uint8_t lY)
{
	UC1701_CorCvt(&lX, &lY);
	UC1701_DrawDotClr(lX, lY);
}

/**
 * @brief   画水平线
 *
 * @param   lX1
 * @param   lY
 * @param   lX2
 */
void DisHorLinSet(uint8_t lX1, uint8_t lY, uint8_t lX2)
{
	uint8_t lTmp;

	UC1701_CorCvt(&lX1, &lY);
	UC1701_CorCvt(&lX2, &lTmp);
	UC1701_DrawHorLinSet(lX1, lY, lX2);
}

/**
 * @brief   清除水平线
 *
 * @param   lX1
 * @param   lY
 * @param   lX2
 */
void DisHorLinClr(uint8_t lX1, uint8_t lY, uint8_t lX2)
{
	uint8_t lTmp;

	UC1701_CorCvt(&lX1, &lY);
	UC1701_CorCvt(&lX2, &lTmp);
	UC1701_DrawHorLinClr(lX1, lY, lX2);
}

/**
 * @brief   画斜线
 *
 * @param   lX
 * @param   lY
 * @param   lQuad
 * @param   lLen
 */
void DisDiagSet(uint8_t lX, uint8_t lY, uint8_t lQuad, uint8_t lLen)
{
	UC1701_CorCvt(&lX, &lY);
	UC1701_DrawDiagSet(lX, lY, lQuad, lLen);
}

/**
 * @brief   清除斜线
 *
 * @param   lX
 * @param   lY
 * @param   lQuad
 * @param   lLen
 */
void DisDiagClr(uint8_t lX, uint8_t lY, uint8_t lQuad, uint8_t lLen)
{
	UC1701_CorCvt(&lX, &lY);
	UC1701_DrawDiagClr(lX, lY, lQuad, lLen);
}

/**
 * @brief   画矩形
 *
 * @param   lX1
 * @param   lY1
 * @param   lX2
 * @param   lY2
 */
void DisRecSet(uint8_t lX1, uint8_t lY1, uint8_t lX2, uint8_t lY2)
{
	UC1701_CorCvt(&lX1, &lY1);
	UC1701_CorCvt(&lX2, &lY2);
	UC1701_DrawRecSet(lX1, lY1, lX2, lY2);
}

/**
 * @brief   清除矩形
 *
 * @param   lX1
 * @param   lY1
 * @param   lX2
 * @param   lY2
 */
void DisRecClr(uint8_t lX1, uint8_t lY1, uint8_t lX2, uint8_t lY2)
{
	UC1701_CorCvt(&lX1, &lY1);
	UC1701_CorCvt(&lX2, &lY2);
	UC1701_DrawRecClr(lX1, lY1, lX2, lY2);
}

/**
 * @brief   画矩形区域
 *
 * @param   lX1
 * @param   lY1
 * @param   lX2
 * @param   lY2
 */
void DisRecFillSet(uint8_t lX1, uint8_t lY1, uint8_t lX2, uint8_t lY2)
{
	UC1701_CorCvt(&lX1, &lY1);
	UC1701_CorCvt(&lX2, &lY2);
	UC1701_FillRecSet(lX1, lY1, lX2, lY2);
}

/**
 * @brief   清除矩形区域
 *
 * @param   lX1
 * @param   lY1
 * @param   lX2
 * @param   lY2
 */
void DisRecFillClr(uint8_t lX1, uint8_t lY1, uint8_t lX2, uint8_t lY2)
{
	UC1701_CorCvt(&lX1, &lY1);
	UC1701_CorCvt(&lX2, &lY2);
	UC1701_FillRecClr(lX1, lY1, lX2, lY2);
}

/**
 * @brief   反转矩形区域
 *
 * @param   lX1
 * @param   lY1
 * @param   lX2
 * @param   lY2
 */
void DisRecRev(uint8_t lX1, uint8_t lY1, uint8_t lX2, uint8_t lY2)
{
	UC1701_CorCvt(&lX1, &lY1);
	UC1701_CorCvt(&lX2, &lY2);
	UC1701_RevRec(lX1, lY1, lX2, lY2);
}

/**
 * @brief   普通画圆
 *
 * @param   lXc
 * @param   lYc
 * @param   lRad
 */
void DisCycSet(uint8_t lXc, uint8_t lYc, uint8_t lRad)
{
	UC1701_CorCvt(&lXc, &lYc);
	UC1701_DrawCycSet(lXc, lYc, lRad);
}

/**
 * @brief   普通清除圆
 *
 * @param   lXc
 * @param   lYc
 * @param   lRad
 */
void DisCycClr(uint8_t lXc, uint8_t lYc, uint8_t lRad)
{
	UC1701_CorCvt(&lXc, &lYc);
	UC1701_DrawCycClr(lXc, lYc, lRad);
}

/**
 * @brief   快速画圆
 *
 * @param   lXc
 * @param   lYc
 * @param   lRad
 */
void DisCycFastSet(uint8_t lXc, uint8_t lYc, uint8_t lRad)
{
	UC1701_CorCvt(&lXc, &lYc);
	UC1701_DrawCycFastSet(lXc, lYc, lRad);
}

/**
 * @brief   快速清除圆
 *
 * @param   lXc
 * @param   lYc
 * @param   lRad
 */
void DisCycFastClr(uint8_t lXc, uint8_t lYc, uint8_t lRad)
{
	UC1701_CorCvt(&lXc, &lYc);
	UC1701_DrawCycFastClr(lXc, lYc, lRad);
}

/**
 * @brief   画矩形带阴影外框
 *
 * @param   lX1
 * @param   lY1
 * @param   lX2
 * @param   lY2
 */
void DisRecFramSet(uint8_t lX1, uint8_t lY1, uint8_t lX2, uint8_t lY2)
{
	UC1701_CorCvt(&lX1, &lY1);
	UC1701_CorCvt(&lX2, &lY2);
	UC1701_DrawRecFramSet(lX1, lY1, lX2, lY2);
}

/**
 * @brief   清除矩形带阴影外框
 *
 * @param   lX1
 * @param   lY1
 * @param   lX2
 * @param   lY2
 */
void DisRecFramClr(uint8_t lX1, uint8_t lY1, uint8_t lX2, uint8_t lY2)
{
	UC1701_CorCvt(&lX1, &lY1);
	UC1701_CorCvt(&lX2, &lY2);
	UC1701_DrawRecFramClr(lX1, lY1, lX2, lY2);
}

/**
 * @brief   画折边矩形
 *
 * @param   lX1
 * @param   lY1
 * @param   lX2
 * @param   lY2
 */
void DisRecDiagSet(uint8_t lX1, uint8_t lY1, uint8_t lX2, uint8_t lY2)
{
	UC1701_CorCvt(&lX1, &lY1);
	UC1701_CorCvt(&lX2, &lY2);
	UC1701_DrawRecDiagSet(lX1, lY1, lX2, lY2);
}

/**
 * @brief   清除折边矩形
 *
 * @param   lX1
 * @param   lY1
 * @param   lX2
 * @param   lY2
 */
void DisRecDiagClr(uint8_t lX1, uint8_t lY1, uint8_t lX2, uint8_t lY2)
{
	UC1701_CorCvt(&lX1, &lY1);
	UC1701_CorCvt(&lX2, &lY2);
	UC1701_DrawRecDiagClr(lX1, lY1, lX2, lY2);
}

/**
 * @brief   画折边矩形带阴影
 *
 * @param   lX1
 * @param   lY1
 * @param   lX2
 * @param   lY2
 */
void DisRecDiagFramSet(uint8_t lX1, uint8_t lY1, uint8_t lX2, uint8_t lY2)
{
	UC1701_CorCvt(&lX1, &lY1);
	UC1701_CorCvt(&lX2, &lY2);
	UC1701_DrawRecDiagFramSet(lX1, lY1, lX2, lY2);
}

/**
 * @brief   清除折边矩形带阴影
 *
 * @param   lX1
 * @param   lY1
 * @param   lX2
 * @param   lY2
 */
void DisRecDiagFramClr(uint8_t lX1, uint8_t lY1, uint8_t lX2, uint8_t lY2)
{
	UC1701_CorCvt(&lX1, &lY1);
	UC1701_CorCvt(&lX2, &lY2);
	UC1701_DrawRecDiagFramClr(lX1, lY1, lX2, lY2);
}

/**
 * @brief   显示字符
 *
 * @param   lX
 * @param   lY
 * @param   lpBuf
 * @param   lXSize
 * @param   lYSize
 */
void DisCharSet(uint8_t lX, uint8_t lY, const uint8_t *lpBuf, 
				uint8_t lXSize, uint8_t lYSize)
{
	UC1701_CorCvt(&lX, &lY);
	UC1701_CharSet(lX, lY, lpBuf, lXSize, lYSize);
}

/**
 * @brief   清除字符
 *
 * @param   lX
 * @param   lY
 * @param   lpBuf
 * @param   lXSize
 * @param   lYSize
 */
void DisCharClr(uint8_t lX, uint8_t lY, const uint8_t *lpBuf, 
				uint8_t lXSize, uint8_t lYSize)
{
	UC1701_CorCvt(&lX, &lY);
	UC1701_CharClr(lX, lY, lpBuf, lXSize, lYSize);
}

/**
 * @brief   全部显示
 */
void DisAll(void)
{
	UC1701_DisAll();
}

/**
 * @brief   清除所有
 */
void DisClr(void)
{
	UC1701_DisClr();
}

/**
 * @brief   反显所有
 */
void DisRev(void)
{
	UC1701_DisRev();
}

/**
 * @brief   正常显示
 */
void DisMirUp(void)
{
	UC1701_MirUp();
}

/**
 * @brief   倒着显示
 */
void DisMirDown(void)
{
	UC1701_MirDown();
}

/**
 * @brief   显示初始化
 */
void DisInit(void)
{
	UC1701_Init();
}

/**
 * @brief   显示断电
 */
void DisPwrDown(void)
{
	UC1701_PwrDown();
}
