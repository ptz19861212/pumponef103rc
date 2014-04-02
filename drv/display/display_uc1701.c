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


// 屏幕大小
const S_Lcd_Screen gLcdScreen =
{
		.PS.X = 0,
		.PS.Y = 0,
		.PE.X = 127,
		.PE.Y = 63,
};


/**
 * @brief   显示大小一致的字符串 英文
 *
 * @param   lpStr
 */
static void DisStrEn(S_Lcd_String* lpStr)
{
	uint8_t lTemp, lI;
	S_Lcd_Char lChar;
	my_lcd_t lX;

	lI = 0;
	lX = lpStr->PS.X;

	while (*(lpStr->Char + lI))
	{

		lTemp = *(lpStr->Char + lI) - FONT_ASCII_OMIT;

		lChar.Font = lpStr->Txt->Font +
							lTemp * lpStr->Txt->Size;
//			lChar.PS.X = lpStr->PS.X + lI * lpStr->Txt->Pixel.X;
		lChar.PS.X = lX;
//		lX += lpStr->Txt->Pixel.X;
		lX += lpStr->Txt->Own.X;
		lI++;

		lChar.PS.Y = lpStr->PS.Y;
		lChar.Pixel.X = lpStr->Txt->Pixel.X;
		lChar.Pixel.Y = lpStr->Txt->Pixel.Y;

		DisCharSet(&lChar);
	}
}


/**
 * @brief   显示大小一致的字符串 中文
 *
 * @param   lpStr
 */
static void DisStrCn(S_Lcd_String* lpStr)
{
	uint8_t lTemp, lI;
	S_Lcd_Char lChar;
	my_lcd_t lX;

	lI = 0;
	lX = lpStr->PS.X;

	while (*(lpStr->Char + lI))
	{

		uint16_t lLen;
		uint16_t lJ;

		lLen = FontChineseSizeGet();

		for (lJ = 0; lJ < lLen; lJ++)
		{
			// 因为是UTF-8，所以中文是3个字节
			if ((*(lpStr->Txt->Font +
					lJ * lpStr->Txt->Size  + 0) ==
						*(lpStr->Char + lI))
					&& (*(lpStr->Txt->Font +
							lJ * lpStr->Txt->Size + 1) ==
						*(lpStr->Char + lI + 1))
					&& (*(lpStr->Txt->Font +
							lJ * lpStr->Txt->Size + 2) ==
						*(lpStr->Char + lI + 2)))
			{
				lChar.Font = lpStr->Txt->Font +
								lJ * lpStr->Txt->Size + 3;
				lChar.PS.X = lX;
//				lX += lpStr->Txt->Pixel.X;
				lX += lpStr->Txt->Own.X;
				break;
			}
		}
//		rt_kprintf("1 = %x\t2 = %x\t3 = %x\n",
//				*(lpStr->Char + lI + 0),
//				*(lpStr->Char + lI + 1),
//				*(lpStr->Char + lI + 2));
		// 这个必须放在for外面，因为在里面的话如果要输出的汉字在字库中
		// 可能造成在前面的不显示出来，除非在for循环中加上break;
		lI += 3;

		lChar.PS.Y = lpStr->PS.Y;
		lChar.Pixel.X = lpStr->Txt->Pixel.X;
		lChar.Pixel.Y = lpStr->Txt->Pixel.Y;

		DisCharSet(&lChar);
	}
}




/**
 * @brief   显示大小一致的字符串，显示中英文
 *
 * @param   lpStr
 */
void DisStr(S_Lcd_String* lpStr)
{
	if (*(lpStr->Char) < 0x80)
	{
		DisStrEn(lpStr);
	}
	else
	{
		DisStrCn(lpStr);
	}
}


/**
 * @brief   显示大小一致的字符串，靠右显示
 *
 * @param   lpStr
 */
void DisStrRight(S_Lcd_String_Right* lpStr)
{
	uint8_t lLength;

	// 计算实际数值字符串长度
	if (*(lpStr->Str.Char) < 0x80)
	{
		lLength = strlen(lpStr->Str.Char);
	}
	else
	{
		// 因为utf-8中文要3个字节
		lLength = strlen(lpStr->Str.Char) / 3;
		lpStr->Len /= 2;
	}

	if (lpStr->Len > lLength)
	{
		S_Lcd_Area_Rectangle lRec;

		lRec.PS.X = lpStr->Str.PS.X;
		lRec.PS.Y = lpStr->Str.PS.Y;
		lRec.PE.X = lpStr->Str.PS.X +
						(lpStr->Len - lLength) *
//							lpStr->Str.Txt->Pixel.X - 1;
							lpStr->Str.Txt->Own.X - 1;
		lRec.PE.Y = lpStr->Str.PS.Y +
//						lpStr->Str.Txt->Pixel.Y - 1;
						lpStr->Str.Txt->Own.Y - 1;

		DisRecFillClr(&lRec);
	}
	// 计算实际的横向坐标
//	lpStr->Str.PS.X = (lpStr->Len - lIn) * lpStr->Str.Txt->Pixel.X;
	lpStr->Str.PS.X += (lpStr->Len - lLength) *
//							lpStr->Str.Txt->Pixel.X;
							lpStr->Str.Txt->Own.X;
	DisStr((S_Lcd_String*)lpStr);
}


/**
 * @brief   显示大小一致的字符串，居中显示
 *
 * @param   lpStr
 */
void DisStrMiddle(S_Lcd_String_Middle* lpStr)
{
	uint8_t lLength;

	// 计算实际数值字符串长度
//	lLength = strlen(lpStr->Str.Char);
	if (*(lpStr->Str.Char) < 0x80)
	{
		lLength = strlen(lpStr->Str.Char);
	}
	else
	{
		// 因为utf-8中文要3个字节
		lLength = strlen(lpStr->Str.Char) / 3;
		lpStr->Len /= 2;
	}

	if (lpStr->Len > lLength)
	{
		S_Lcd_Area_Rectangle lRec;

		lRec.PS.X = lpStr->Str.PS.X;
		lRec.PS.Y = lpStr->Str.PS.Y;
		lRec.PE.X = lpStr->Str.PS.X +
						(((lpStr->Len - lLength) *
//							lpStr->Str.Txt->Pixel.X) >> 1) - 1;
							lpStr->Str.Txt->Own.X) >> 1) - 1;
		lRec.PE.Y = lpStr->Str.PS.Y +
//						lpStr->Str.Txt->Pixel.Y - 1;
						lpStr->Str.Txt->Own.Y - 1;
		DisRecFillClr(&lRec);
//		DisRecSet(&lRec);

		lRec.PS.X = lRec.PE.X + 1;
//		lRec.PE.X += lLength * lpStr->Str.Txt->Pixel.X - 1;
		lRec.PE.X = lpStr->Str.PS.X +
//						lpStr->Len * lpStr->Str.Txt->Pixel.X - 1;
						lpStr->Len * lpStr->Str.Txt->Own.X - 1;

		DisRecFillClr(&lRec);
//		DisRecSet(&lRec);
	}
	// 计算实际的横向坐标
//	lpStr->Str.PS.X = (lpStr->Len - lIn) * lpStr->Str.Txt->Pixel.X;
//	lpStr->Str.PS.X += (lpStr->Len - lLength) * lpStr->Str.Txt->Pixel.X;
	lpStr->Str.PS.X += ((lpStr->Len - lLength) *
//							lpStr->Str.Txt->Pixel.X) >> 1;
							lpStr->Str.Txt->Own.X) >> 1;

	DisStr((S_Lcd_String*)lpStr);
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
//void DisStrEx(const uint8_t *lpStr, uint8_t lX, uint8_t lY,
//				const uint8_t *lpFont1, uint8_t lXSize1, uint8_t lYSize1,
//				uint8_t lFSize1, const uint8_t *lpFont2, uint8_t lXSize2,
//				uint8_t lYSize2, uint8_t lFSize2)
void DisStrDual(S_Lcd_String_Dual* lStr)
{
	uint8_t lTmp, lI;
	uint8_t lXTmp, lYEx;
	S_Lcd_Char lChar;

	lI = 0;
//	lXTmp = lX;
	lXTmp = lStr->PS.X;
//	lYEx = lY + (lYSize1 - lYSize2);

//	if (lStr->TxtLarge->Pixel.Y > lStr->TxtSmall->Pixel.Y)
//	{
//		lYEx = lStr->PS.Y + (lStr->TxtLarge->Pixel.Y -
//								lStr->TxtSmall->Pixel.Y);
//	}
//	else
//	{
//		lYEx = lStr->PS.Y + (lStr->TxtSmall->Pixel.Y -
//								lStr->TxtLarge->Pixel.Y);
//	}


	if (lStr->TxtLarge->Own.Y > lStr->TxtSmall->Own.Y)
	{
		lYEx = lStr->PS.Y + (lStr->TxtLarge->Own.Y -
								lStr->TxtSmall->Own.Y);
	}
	else
	{
		lYEx = lStr->PS.Y + (lStr->TxtSmall->Own.Y -
								lStr->TxtLarge->Own.Y);
	}


//	while (*(lpStr + lI))
	while (*(lStr->Char + lI))
	{
//		lTmp = *(lpStr + lI);
		lTmp = *(lStr->Char + lI);

		if ((lTmp <= '9') && (lTmp >= '0'))
		{
			lTmp -= FONT_ASCII_OMIT;

//			lChar.Font = lpFont2 + lTmp * lFSize2;
			lChar.Font = lStr->TxtSmall->Font +
								lTmp * lStr->TxtSmall->Size;
			lChar.PS.X = lXTmp;
			lChar.PS.Y = lYEx;
//			lChar.Size.X = lXSize2;
//			lChar.Size.Y = lYSize2;
			lChar.Pixel.X = lStr->TxtSmall->Pixel.X;
			lChar.Pixel.Y = lStr->TxtSmall->Pixel.Y;

			DisCharSet(&lChar);
//			lXTmp += lXSize2;
//			lXTmp += lStr->TxtSmall->Pixel.X;
			lXTmp += lStr->TxtSmall->Own.X;
		}
		else
		{
			lTmp -= FONT_ASCII_OMIT;

//			lChar.Font = lpFont1 + lTmp * lFSize1;
			lChar.Font = lStr->TxtLarge->Font +
								lTmp * lStr->TxtLarge->Size;
			lChar.PS.X = lXTmp;
//			lChar.PS.Y = lY;
			lChar.PS.Y = lStr->PS.Y;
//			lChar.Size.X = lXSize1;
//			lChar.Size.Y = lYSize1;
			lChar.Pixel.X = lStr->TxtLarge->Pixel.X;
			lChar.Pixel.Y = lStr->TxtLarge->Pixel.Y;

			DisCharSet(&lChar);
//			lXTmp += lXSize1;
//			lXTmp += lStr->TxtLarge->Pixel.X;
			lXTmp += lStr->TxtLarge->Own.X;
		}

		lI++;
	} //end of while (*(lpStr + lI))
}


/**
 * @brief   显示数字 数字区域都受影响，左对齐
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
//void DisNum(uint16_t lNum, uint8_t lPoint, uint8_t lX, uint8_t lY,
//			const uint8_t *lpFont, uint8_t lXSize, uint8_t lYSize,
//			uint8_t lFSize)
void DisNum(S_Lcd_Value_U16* lpValue)
{
//	uint8_t lI, lTemp;
//	uint8_t lData[7];

//	lpValue->Str.Char = lData;

//	NumTurn16(lData, lNum, lPoint);
//	NumToStr16(lData, lNum, lPoint);
//	NumToStr16(lData, lpValue->Value.Num, lpValue->Value.Point);
//	NumToStr16(lpValue->Str.Char, lpValue->Value.Num, lpValue->Value.Point);
	DecToStrU16(&(lpValue->Array));

//	DisStr(lData, lX, lY, lpFont, lXSize, lYSize, lFSize);
//	DisStr(lData, lpValue->Str.PS.X, lpValue->Str.PS.Y,
//			lpValue->Str.Txt->Font, lpValue->Str.Txt->X,
//			lpValue->Str.Txt->Y, lpValue->Str.Txt->Size);
	DisStr(&(lpValue->Str));
}


/**
 * @brief   显示数字 数字区域都受影响，右对齐
 *
 * @param   lNum
 * @param   lPoint
 * @param   lX
 * @param   lY
 * @param   lLen 右对齐的位数
 * @param   lpFont
 * @param   lXSize
 * @param   lYSize
 * @param   lFSize
 */
//void DisNumRight(uint16_t lNum, uint8_t lPoint, uint8_t lX, uint8_t lY,
//					uint8_t lLen, const uint8_t *lpFont,
//					uint8_t lXSize, uint8_t lYSize, uint8_t lFSize)
void DisNumRight(S_Lcd_Value_Right_U16* lpValue)
{
//	uint8_t lI, lTemp;
	uint8_t lIn;
//	uint8_t lData[7];
//	S_Value_Array_U16 lArray;

//	lpValue->Str.Str.Char = lData;

//	NumTurn16(lData, lNum, lPoint);
//	DecToStrU16(lData, lNum, lPoint);
//	lArray.Char = lpValue->Str.Str.Char;
//	lArray.Value.Num = lpValue->Value.Num;
//	lArray.Value.Point = lpValue->Value.Point;
	DecToStrU16(&(lpValue->Array));

//	DecToStrU16(lpValue->Str.Str.Char, lpValue->Value.Num,
//					lpValue->Value.Point);

	// 计算实际数值字符串长度
//	lIn = strlen(lData);
	// 计算实际的横向坐标
//	lX = (lLen - lIn) * lXSize;
//	lpValue->Str.PS.X = (lpValue->Value.Len - lIn) * lpValue->Str.Txt->X;

//	DisStr(lData, lX, lY, lpFont, lXSize, lYSize, lFSize);
//	DisStr(lData, lpValue->PS.X, lpValue->PS.Y, lpValue->Txt->Font,
//			lpValue->Txt->X, lpValue->Txt->Y, lpValue->Txt->Size);
//	DisStr(lData, lpValue->Str.PS.X, lpValue->Str.PS.Y,
//			lpValue->Str.Txt->Font, lpValue->Str.Txt->X,
//			lpValue->Str.Txt->Y, lpValue->Str.Txt->Size);
	DisStrRight(&(lpValue->Str));
}


/*********************************** 闪烁显示 ************************************/
// 让屏幕的某个区域保持闪烁，主要用于数值输入
static S_Lcd_Blink sLcdBlink;


/**
 * @brief   菜单区域闪烁设置
 *
 * @param   lStart 开始的点
 * @param   lEnd 结束的点
 */
//void DisBlinkSet(S_Lcd_Point* lStart, S_Lcd_Point* lEnd)
void DisBlinkSet(S_Lcd_Area_Rectangle* lpRec)
{
	sLcdBlink.Rec.PS.X = lpRec->PS.X;
	sLcdBlink.Rec.PS.Y = lpRec->PS.Y;
	sLcdBlink.Rec.PE.X = lpRec->PE.X;
	sLcdBlink.Rec.PE.Y = lpRec->PE.Y;
	sLcdBlink.State = TURN_ON;
}


/**
 * @brief   菜单区域闪烁
 */
//void MenuBlink(struct S_Device* lpDev)
void DisBlink(void)
{
	if (sLcdBlink.State == TURN_ON)
	{
//		S_Lcd_Area_Rectangle lRec;

//		lRec.PS.X = sMenuBlink.Start.X;
//		lRec.PS.Y = sMenuBlink.Start.Y;
//		lRec.PE.X = sMenuBlink.End.X;
//		lRec.PE.Y = sMenuBlink.End.Y;
//		DisRecRev(&lRec);
		S_Lcd_Area_Rectangle lRec;

		lRec.PS.X = sLcdBlink.Rec.PS.X;
		lRec.PS.Y = sLcdBlink.Rec.PS.Y;
		lRec.PE.X = sLcdBlink.Rec.PE.X;
		lRec.PE.Y = sLcdBlink.Rec.PE.Y;

		DisRecRev(&lRec);
//			DisRecRev(sMenuBlink.Start.X, sMenuBlink.Start.Y,
//						sMenuBlink.End.X, sMenuBlink.End.Y);
	}
}


/**
 * @brief   菜单区域闪烁停止
 */
void DisBlinkOff(void)
{
//	sMenuBlink.State = DISABLE;
	sLcdBlink.State = TURN_OFF;
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
//uint8_t DisGapGet(uint8_t lLenSum, uint8_t lLenChar, uint8_t lNum)
//{
//	return ((lLenSum - lLenChar * lNum) / (lNum + 1));
//}

/**
 * @brief   画点
 *
 * @param   lX
 * @param   lY
 */
void DisDotSet(S_Lcd_Point* lpPoint)
{
	UC1701_CorCvt(lpPoint);
	UC1701_DrawDotSet(lpPoint);
}

/**
 * @brief   清除点
 *
 * @param   lX
 * @param   lY
 */
void DisDotClr(S_Lcd_Point* lpPoint)
{
	UC1701_CorCvt(lpPoint);

	UC1701_DrawDotClr(lpPoint);
}

/**
 * @brief   画水平线
 *
 * @param   lX1
 * @param   lY
 * @param   lX2
 */
void DisHorLinSet(S_Lcd_Line_Horizon* lpHor)
{
	UC1701_CorCvt_X(&(lpHor->XS));
	UC1701_CorCvt_X(&(lpHor->XE));
	UC1701_CorCvt_Y(&(lpHor->Y));

	UC1701_DrawHorLinSet(lpHor);
}

/**
 * @brief   清除水平线
 *
 * @param   lX1
 * @param   lY
 * @param   lX2
 */
void DisHorLinClr(S_Lcd_Line_Horizon* lpHor)
{
	UC1701_CorCvt_X(&(lpHor->XS));
	UC1701_CorCvt_X(&(lpHor->XE));
	UC1701_CorCvt_Y(&(lpHor->Y));

	UC1701_DrawHorLinClr(lpHor);
}

/**
 * @brief   画水平虚线
 *
 * @param   lX1
 * @param   lY
 * @param   lX2
 */
void DisHorDotLinSet(S_Lcd_Line_Horizon* lpHor)
{
	UC1701_CorCvt_X(&(lpHor->XS));
	UC1701_CorCvt_X(&(lpHor->XE));
	UC1701_CorCvt_Y(&(lpHor->Y));

	UC1701_DrawHorDotLinSet(lpHor);
}

/**
 * @brief   清除水平虚线
 *
 * @param   lX1
 * @param   lY
 * @param   lX2
 */
void DisHorDotLinClr(S_Lcd_Line_Horizon* lpHor)
{
	UC1701_CorCvt_X(&(lpHor->XS));
	UC1701_CorCvt_X(&(lpHor->XE));
	UC1701_CorCvt_Y(&(lpHor->Y));

	UC1701_DrawHorDotLinClr(lpHor);
}

/**
 * @brief   画垂直线
 *
 * @param   lX1
 * @param   lY
 * @param   lX2
 */
void DisVerLinSet(S_Lcd_Line_Vertical* lpVer)
{
	UC1701_CorCvt_X(&(lpVer->X));
	UC1701_CorCvt_Y(&(lpVer->YS));
	UC1701_CorCvt_Y(&(lpVer->YE));

	UC1701_DrawVerLinSet(lpVer);
}

/**
 * @brief   清除垂直线
 *
 * @param   lX1
 * @param   lY
 * @param   lX2
 */
void DisVerLinClr(S_Lcd_Line_Vertical* lpVer)
{
	UC1701_CorCvt_X(&(lpVer->X));
	UC1701_CorCvt_Y(&(lpVer->YS));
	UC1701_CorCvt_Y(&(lpVer->YE));

	UC1701_DrawVerLinClr(lpVer);
}

/**
 * @brief   画垂直虚线
 *
 * @param   lX1
 * @param   lY
 * @param   lX2
 */
void DisVerDotLinSet(S_Lcd_Line_Vertical* lpVer)
{
	UC1701_CorCvt_X(&(lpVer->X));
	UC1701_CorCvt_Y(&(lpVer->YS));
	UC1701_CorCvt_Y(&(lpVer->YE));

	UC1701_DrawVerDotLinSet(lpVer);
}

/**
 * @brief   清除垂直虚线
 *
 * @param   lX1
 * @param   lY
 * @param   lX2
 */
void DisVerDotLinClr(S_Lcd_Line_Vertical* lpVer)
{
	UC1701_CorCvt_X(&(lpVer->X));
	UC1701_CorCvt_Y(&(lpVer->YS));
	UC1701_CorCvt_Y(&(lpVer->YE));

	UC1701_DrawVerDotLinClr(lpVer);
}

/**
 * @brief   画斜线
 *
 * @param   lX
 * @param   lY
 * @param   lQuad
 * @param   lLen
 */
void DisDiagSet(S_Lcd_Line_Diagonal* lpLin)
{
	UC1701_CorCvt_X(&(lpLin->Point.X));
	UC1701_CorCvt_Y(&(lpLin->Point.Y));

	UC1701_DrawDiagSet(lpLin);
}

/**
 * @brief   清除斜线
 *
 * @param   lX
 * @param   lY
 * @param   lQuad
 * @param   lLen
 */
void DisDiagClr(S_Lcd_Line_Diagonal* lpLin)
{
	UC1701_CorCvt_X(&(lpLin->Point.X));
	UC1701_CorCvt_Y(&(lpLin->Point.Y));

	UC1701_DrawDiagClr(lpLin);
}

/**
 * @brief   画矩形
 *
 * @param   lX1
 * @param   lY1
 * @param   lX2
 * @param   lY2
 */
void DisRecSet(S_Lcd_Area_Rectangle* lpRec)
{
	UC1701_CorCvt(&(lpRec->PS));
	UC1701_CorCvt(&(lpRec->PE));
	UC1701_DrawRecSet(lpRec);
}

/**
 * @brief   清除矩形
 *
 * @param   lX1
 * @param   lY1
 * @param   lX2
 * @param   lY2
 */
void DisRecClr(S_Lcd_Area_Rectangle* lpRec)
{
	UC1701_CorCvt(&(lpRec->PS));
	UC1701_CorCvt(&(lpRec->PE));
	UC1701_DrawRecClr(lpRec);
}

/**
 * @brief   画矩形区域
 *
 * @param   lX1
 * @param   lY1
 * @param   lX2
 * @param   lY2
 */
void DisRecFillSet(S_Lcd_Area_Rectangle* lpRec)
{
	UC1701_CorCvt(&(lpRec->PS));
	UC1701_CorCvt(&(lpRec->PE));
	UC1701_FillRecSet(lpRec);
}

/**
 * @brief   清除矩形区域
 *
 * @param   lX1
 * @param   lY1
 * @param   lX2
 * @param   lY2
 */
void DisRecFillClr(S_Lcd_Area_Rectangle* lpRec)
{
	UC1701_CorCvt(&(lpRec->PS));
	UC1701_CorCvt(&(lpRec->PE));
	UC1701_FillRecClr(lpRec);
}

/**
 * @brief   反转矩形区域
 *
 * @param   lX1
 * @param   lY1
 * @param   lX2
 * @param   lY2
 */
void DisRecRev(S_Lcd_Area_Rectangle* lpRec)
{
	UC1701_CorCvt(&(lpRec->PS));
	UC1701_CorCvt(&(lpRec->PE));
	UC1701_RevRec(lpRec);
}


/**
 * @brief   画滚动条
 *
 * @param   lLen 滚动条滑块的长度
 * @param   lEx 滚动条一边比线多出来的宽度
 * @param   lXLin 滚动条长线的起始X
 * @param   lYScr 滚动条滑块的起始y
 */
//void DisScrollBar(uint8_t lLen, uint8_t lEx, uint8_t lXLin, uint8_t lYScr)
void DisScrollBar(S_Lcd_Bar_Scroll* lpBar)
{
//	uint8_t lTmp;
//	uint8_t lY1 = 0;
//	uint8_t lY2 = DIS_Y_END - 16;
//
//	UC1701_CorCvt(&lXLin, &lY1);
//	UC1701_CorCvt(&lTmp, &lY2);
//	UC1701_CorCvt(&lTmp, &lYScr);
//	UC1701_ScrollBar(lLen, lEx, lXLin, lY1, lY2, lYScr);

//	S_Lcd_Bar_Scroll lBar;

//	lBar.YS = 0;
//	lBar.YE = gLcdScreen.PE.Y - 16;
//	lBar.SXEx = lEx;
//	lBar.SYLen = lLen;
//	lBar.SYS = lYScr;
//	lBar.X = lXLin;

	UC1701_CorCvt_X(&(lpBar->X));
	UC1701_CorCvt_Y(&(lpBar->YS));
	UC1701_CorCvt_Y(&(lpBar->YE));
	UC1701_CorCvt_Y(&(lpBar->SYS));

//	UC1701_ScrollBar(&lBar);
	UC1701_ScrollBar(lpBar);
}


/**
 * @brief   普通画圆
 *
 * @param   lXc
 * @param   lYc
 * @param   lRad
 */
void DisCycSet(S_Lcd_Area_Cycle* lpCyc)
{
	UC1701_CorCvt(&(lpCyc->PC));
	UC1701_DrawCycSet(lpCyc);
}

/**
 * @brief   普通清除圆
 *
 * @param   lXc
 * @param   lYc
 * @param   lRad
 */
void DisCycClr(S_Lcd_Area_Cycle* lpCyc)
{
	UC1701_CorCvt(&(lpCyc->PC));
	UC1701_DrawCycClr(lpCyc);
}

/**
 * @brief   快速画圆
 *
 * @param   lXc
 * @param   lYc
 * @param   lRad
 */
void DisCycFastSet(S_Lcd_Area_Cycle* lpCyc)
{
	UC1701_CorCvt(&(lpCyc->PC));
	UC1701_DrawCycFastSet(lpCyc);
}

/**
 * @brief   快速清除圆
 *
 * @param   lXc
 * @param   lYc
 * @param   lRad
 */
void DisCycFastClr(S_Lcd_Area_Cycle* lpCyc)
{
	UC1701_CorCvt(&(lpCyc->PC));
	UC1701_DrawCycFastClr(lpCyc);
}

/**
 * @brief   画矩形带阴影外框
 *
 * @param   lX1
 * @param   lY1
 * @param   lX2  包括阴影
 * @param   lY2  包括阴影
 */
void DisRecFramSet(S_Lcd_Area_RectangleShade* lpRec)
{
	UC1701_CorCvt(&(lpRec->PS));
	UC1701_CorCvt(&(lpRec->PE));

	UC1701_DrawRecFramSet(lpRec);
}

/**
 * @brief   清除矩形带阴影外框
 *
 * @param   lX1
 * @param   lY1
 * @param   lX2
 * @param   lY2
 */
void DisRecFramClr(S_Lcd_Area_RectangleShade* lpRec)
{
	UC1701_CorCvt(&(lpRec->PS));
	UC1701_CorCvt(&(lpRec->PE));

	UC1701_DrawRecFramClr(lpRec);
}

/**
 * @brief   画折边矩形
 *
 * @param   lX1
 * @param   lY1
 * @param   lX2
 * @param   lY2
 */
//void DisRecDiagSet(uint8_t lX1, uint8_t lY1, uint8_t lX2, uint8_t lY2)
//{
//	UC1701_CorCvt(&lX1, &lY1);
//	UC1701_CorCvt(&lX2, &lY2);
//	UC1701_DrawRecDiagSet(lX1, lY1, lX2, lY2);
//}

/**
 * @brief   清除折边矩形
 *
 * @param   lX1
 * @param   lY1
 * @param   lX2
 * @param   lY2
 */
//void DisRecDiagClr(uint8_t lX1, uint8_t lY1, uint8_t lX2, uint8_t lY2)
//{
//	UC1701_CorCvt(&lX1, &lY1);
//	UC1701_CorCvt(&lX2, &lY2);
//	UC1701_DrawRecDiagClr(lX1, lY1, lX2, lY2);
//}

/**
 * @brief   画折边矩形带阴影
 *
 * @param   lX1
 * @param   lY1
 * @param   lX2
 * @param   lY2
 */
//void DisRecDiagFramSet(uint8_t lX1, uint8_t lY1, uint8_t lX2, uint8_t lY2)
//{
//	UC1701_CorCvt(&lX1, &lY1);
//	UC1701_CorCvt(&lX2, &lY2);
//	UC1701_DrawRecDiagFramSet(lX1, lY1, lX2, lY2);
//}

/**
 * @brief   清除折边矩形带阴影
 *
 * @param   lX1
 * @param   lY1
 * @param   lX2
 * @param   lY2
 */
//void DisRecDiagFramClr(uint8_t lX1, uint8_t lY1, uint8_t lX2, uint8_t lY2)
//{
//	UC1701_CorCvt(&lX1, &lY1);
//	UC1701_CorCvt(&lX2, &lY2);
//	UC1701_DrawRecDiagFramClr(lX1, lY1, lX2, lY2);
//}

/**
 * @brief   显示字符
 *
 * @param   lX
 * @param   lY
 * @param   lpBuf
 * @param   lXSize
 * @param   lYSize
 */
void DisCharSet(S_Lcd_Char* lpChar)
{
	UC1701_CorCvt(&(lpChar->PS));
	UC1701_CharSet(lpChar);
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
void DisCharClr(S_Lcd_Char* lpChar)
{
	UC1701_CorCvt(&(lpChar->PS));
	UC1701_CharClr(lpChar);
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
 * @brief   打开背光
 */
void DisBgOn(void)
{
	UC1701_BgOn();
}


/**
 * @brief   关闭背光
 */
void DisBgOff(void)
{
	UC1701_BgOff();
}


/**
 * @brief   进入休眠模式
 */
void DisSleepIN(void)
{
	UC1701_SleepIN();
}


/**
 * @brief   退出休眠模式
 */
void DisSleepOut(void)
{
	UC1701_SleepOut();
}

/**
 * @brief   显示断电
 */
void DisPwrDown(void)
{
	UC1701_PwrDown();
}
