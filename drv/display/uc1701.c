/**
 * @file    uc1701.c
 * @brief   UC1701驱动
 * @author  ptz
 * @email   ptz19861212@163.com
 * @version 0.0.1
 * @date    2013-08-08 14:00:57 星期四 
 * @history (1).2013-08-08 14:00:57 星期四 create
 */
/* Copyright (C)
 * 
 * My own license
 * All right reserved
 * 
 */

#include "uc1701_in.h"

// 因为这个没有读引脚，所以只能用内存来模拟读
uint8_t sDisRam[UC1701_PAGE_NUM][UC1701_SEG_NUM];

// 模拟UC1701显存中的指针
uint8_t sDisPag = 0x00;
uint8_t sDisCol = 0x00;

// uc 1701 ram page
uint8_t sPage[UC1701_SEG_NUM];



/**
 * @brief   uc1701 模式传输字节
 *
 * @param   lByte 数据
 */
static void UC1701_Byte(uint8_t lByte)
{
	uint8_t lI = 0;
	uint8_t lTemp = lByte;

	for (lI = 0; lI < 8; lI++)
	{
		UC1701_SCK_LOW;
		UC1701_DELAY;

		if (lTemp & 0x80)
			UC1701_MOSI_HIGH;
		else
			UC1701_MOSI_LOW;

		lTemp = lTemp << 0x01;

		UC1701_DELAY;
		UC1701_SCK_HIGH;
		UC1701_DELAY;
	}
}

/**
 * @brief   uc1701 发送命令
 *
 * @param   lCmd
 */
static void UC1701_Cmd(uint8_t lCmd)
{
	UC1701_CD_LOW;
	UC1701_Byte(lCmd);
	UC1701_DELAY;
}

/**
 * @brief   纵坐标转为页和页偏移
 *
 * @param   lY
 * @param   lpPage
 */
static inline UC1701_PageGet(my_lcd_t lY, S_Lcd_Point_Page* lpPage)
{
	lpPage->Index = lY >> 3;
	lpPage->Offset = lY & 0x07;
}


/**
 * @brief   设定坐标
 *
 * @param   lPag
 * @param   lCol
 */
static void UC1701_CorSet(uint8_t lPag, uint8_t lCol)
{
	UC1701_Cmd(UC1701_CMD_PA | lPag);
	UC1701_Cmd(UC1701_CMD_CAM | ((lCol >> 4) & 0x0F));
	UC1701_Cmd(UC1701_CMD_CAL | (lCol & 0x0F));

	sDisPag = lPag;
	sDisCol = lCol;
}

/**
 * @brief   uc1701 传输数据
 *
 * @param   lByte
 */
static void UC1701_WriteByte(uint8_t lByte)
{
	UC1701_CD_HIGH;
	UC1701_Byte(lByte);
	UC1701_DELAY;

	sDisRam[sDisPag][sDisCol] = lByte;
	sDisCol++;
}

/**
 * @brief   读取字节数据
 *
 * @return  
 */
static uint8_t UC1701_ReadByte(void)
{
	return sDisRam[sDisPag][sDisCol];
}

/**
 * @brief   把显存中的数据读入页数组中去
 *
 * @param   lPag
 * @param   lCol
 * @param   lLen
 */
static void UC1701_Read(my_lcd_t lPag, my_lcd_t lCol, my_lcd_t lLen)
{
//	uint8_t lI;
	my_lcd_t lI;

	for (lI = 0; lI < lLen; lI++)
		sPage[lCol + lI] = sDisRam[lPag][lCol + lI];
}

/**
 * @brief   页数组数据写入显存
 *
 * @param   lPag
 * @param   lCol
 * @param   lLen
 */
static void UC1701_Write(my_lcd_t lPag, my_lcd_t lCol, my_lcd_t lLen)
{
//	uint8_t lI;
	my_lcd_t lI;

	UC1701_CS_LOW;

	UC1701_CorSet(lPag, lCol);
	
	//buffer have only one page, so be careful the length
	if ((lCol + lLen) > (UC1701_SEG_NUM))				
		lLen = UC1701_SEG_NUM - lCol;

	for (lI = 0; lI < lLen; lI++)
		UC1701_WriteByte(*(sPage + lCol + lI));

	UC1701_CS_HIGH;
}

/**
 * @brief    画点
 *
 * @param   lX
 * @param   lY
 */
//void UC1701_DrawDotSet(uint8_t lX, uint8_t lY)
void UC1701_DrawDotSet(S_Lcd_Point* lpPoint)
{
//	uint8_t lPag, lOfSet, lTemp;
	S_Lcd_Point_Ex lEx;
	uint8_t lTemp;

	lEx.Point = lpPoint;
	// 获得点对应的页
//	UC1701_PageGet(&lEx);
	UC1701_PageGet(lEx.Point->Y, &(lEx.Page));
	
	//lY / 8  page address
//	UC1701_PageGet(lY, &lPag, &lOfSet);

	UC1701_CS_LOW;

//	UC1701_CorSet(lPag, lX);

	UC1701_CorSet(lEx.Page.Index, lEx.Point->X);

	//data read
	lTemp = UC1701_ReadByte();

	//pin mode
//	lTemp |= BIT(lOfSet);
	lTemp |= BIT(lEx.Page.Offset);

	UC1701_WriteByte(lTemp);

	UC1701_CS_HIGH;
}

/**
 * @brief   点清除
 *
 * @param   lX
 * @param   lY
 */
void UC1701_DrawDotClr(S_Lcd_Point* lpPoint)
{
//	uint8_t lPag, lOfSet, lTemp;
	
	//lY / 8  page address
//	UC1701_PageGet(lY, &lPag, &lOfSet);

	S_Lcd_Point_Ex lEx;
	uint8_t lTemp;

	lEx.Point = lpPoint;
	// 获得点对应的页
//	UC1701_PageGet(&lEx);
	UC1701_PageGet(lEx.Point->Y, &(lEx.Page));

	UC1701_CS_LOW;

//	UC1701_CorSet(lPag, lX);
	UC1701_CorSet(lEx.Page.Index, lEx.Point->X);

	//data read
	lTemp = UC1701_ReadByte();

	//pin mode
//	lTemp &= ~BIT(lOfSet);
	lTemp &= ~BIT(lEx.Page.Offset);

	UC1701_WriteByte(lTemp);

	UC1701_CS_HIGH;
}


/**
 * @brief   画水平线
 *
 * @param   lpLin
 */
void UC1701_DrawHorLinSet(S_Lcd_Line_Horizon* lpLin)
{
	S_Lcd_Line_Horizon_Ex lEx;

	lEx.Line = lpLin;

	INCREASE(lEx.Line->XS, lEx.Line->XE);

	UC1701_PageGet(lEx.Line->Y, &(lEx.Page));

	lEx.Area.Len = lEx.Line->XE - lEx.Line->XS + 1;

	UC1701_Read(lEx.Page.Index, lEx.Line->XS, lEx.Area.Len);

	my_lcd_t lI;

	for (lI = 0; lI < lEx.Area.Len; lI++)
	{
		sPage[lEx.Line->XS + lI] |= BIT(lEx.Page.Offset);
	}

	UC1701_Write(lEx.Page.Index, lEx.Line->XS, lEx.Area.Len);
}

/**
 * @brief   清除水平线
 *
 * @param   lX1
 * @param   lY
 * @param   lX2
 */
void UC1701_DrawHorLinClr(S_Lcd_Line_Horizon* lpLin)
{
	S_Lcd_Line_Horizon_Ex lEx;

	lEx.Line = lpLin;

	INCREASE(lEx.Line->XS, lEx.Line->XE);

	UC1701_PageGet(lEx.Line->Y, &(lEx.Page));

	lEx.Area.Len = lEx.Line->XE - lEx.Line->XS + 1;

	UC1701_Read(lEx.Page.Index, lEx.Line->XS, lEx.Area.Len);

	my_lcd_t lI;

	for (lI = 0; lI < lEx.Area.Len; lI++)
	{
		sPage[lEx.Line->XS + lI] &= ~BIT(lEx.Page.Offset);
	}

	UC1701_Write(lEx.Page.Index, lEx.Line->XS, lEx.Area.Len);
}

/**
 * @brief   画水平虚线
 *
 * @param   lX1
 * @param   lY
 * @param   lX2
 */
void UC1701_DrawHorDotLinSet(S_Lcd_Line_Horizon* lpLin)
{
	S_Lcd_Line_Horizon_Ex lEx;

	lEx.Line = lpLin;

	INCREASE(lEx.Line->XS, lEx.Line->XE);

	UC1701_PageGet(lEx.Line->Y, &(lEx.Page));

	lEx.Area.Len = lEx.Line->XE - lEx.Line->XS + 1;

	UC1701_Read(lEx.Page.Index, lEx.Line->XS, lEx.Area.Len);

	my_lcd_t lI;

	for (lI = 0; lI < lEx.Area.Len; lI++)
	{
		// 除4,商为偶数就画线，商为奇数就不画
		if ((lI >> 2) & 0x01)
		{
			sPage[lEx.Line->XS + lI] &= ~BIT(lEx.Page.Offset);
		}
		else
		{
			sPage[lEx.Line->XS + lI] |= BIT(lEx.Page.Offset);
		}
	}

	UC1701_Write(lEx.Page.Index, lEx.Line->XS, lEx.Area.Len);
}

/**
 * @brief   清除水平虚线
 *
 * @param   lX1
 * @param   lY
 * @param   lX2
 */
void UC1701_DrawHorDotLinClr(S_Lcd_Line_Horizon* lpLin)
{
	S_Lcd_Line_Horizon_Ex lEx;

	lEx.Line = lpLin;

	INCREASE(lEx.Line->XS, lEx.Line->XE);

	UC1701_PageGet(lEx.Line->Y, &(lEx.Page));

	lEx.Area.Len = lEx.Line->XE - lEx.Line->XS + 1;

	UC1701_Read(lEx.Page.Index, lEx.Line->XS, lEx.Area.Len);

	my_lcd_t lI;

	for (lI = 0; lI < lEx.Area.Len; lI++)
	{
		// 除4,商为偶数就清除画线
		if (!((lI >> 2) & 0x01))
		{
			sPage[lEx.Line->XS + lI] &= ~BIT(lEx.Page.Offset);
		}
	}

	UC1701_Write(lEx.Page.Index, lEx.Line->XS, lEx.Area.Len);
}

/**
 * @brief   画垂直线
 *
 * @param   lX1
 * @param   lY1
 * @param   lY2
 */
void UC1701_DrawVerLinSet(S_Lcd_Line_Vertical* lpLin)
{
	S_Lcd_Line_Vertical_Ex lEx;

	lEx.Line = lpLin;

	INCREASE(lEx.Line->YS, lEx.Line->YE);

	UC1701_PageGet(lEx.Line->YS, &(lEx.PS));
	UC1701_PageGet(lEx.Line->YE, &(lEx.PE));

	lEx.Area.PagNum = lEx.PE.Index - lEx.PS.Index;

	UC1701_CS_LOW;

	UC1701_CorSet(lEx.PS.Index, lEx.Line->X);

	uint8_t lTmp;

	lTmp = UC1701_ReadByte();

	if (lEx.Area.PagNum == 0)
	{
		lTmp |= (0xFF << lEx.PS.Offset) &
					(~(0xFF << (lEx.PE.Offset + 1)));

		UC1701_WriteByte(lTmp);
	}
	else
	{
		lTmp |= 0xFF << lEx.PS.Offset;

		UC1701_WriteByte(lTmp);
		
		my_lcd_t lI;

		for (lI = 0; lI < (lEx.Area.PagNum - 1); lI++)
		{
			UC1701_CorSet(lEx.PS.Index + lI + 1, lEx.Line->X);
			UC1701_WriteByte(0xFF);
		}

		UC1701_CorSet(lEx.PE.Index, lEx.Line->X);

		//data read
		lTmp = UC1701_ReadByte();

		lTmp |= ~(0xFF << (lEx.PE.Offset + 1));

		UC1701_WriteByte(lTmp);
	}

	UC1701_CS_HIGH;

}

/**
 * @brief   清除垂直线
 *
 * @param   lX1
 * @param   lY1
 * @param   lY2
 */
void UC1701_DrawVerLinClr(S_Lcd_Line_Vertical* lpLin)
{
	S_Lcd_Line_Vertical_Ex lEx;

	lEx.Line = lpLin;

	INCREASE(lEx.Line->YS, lEx.Line->YE);

	UC1701_PageGet(lEx.Line->YS, &(lEx.PS));
	UC1701_PageGet(lEx.Line->YE, &(lEx.PE));

	lEx.Area.PagNum = lEx.PE.Index - lEx.PS.Index;

	UC1701_CS_LOW;

	UC1701_CorSet(lEx.PS.Index, lEx.Line->X);

	uint8_t lTmp;

	lTmp = UC1701_ReadByte();

	if (lEx.Area.PagNum == 0)
	{
		lTmp &= ~((0xFF << lEx.PS.Offset) &
					(~(0xFF << (lEx.PE.Offset + 1))));

		UC1701_WriteByte(lTmp);
	}
	else
	{
		lTmp &= ~(0xFF << lEx.PS.Offset);

		UC1701_WriteByte(lTmp);

		
		my_lcd_t lI;

		for (lI = 0; lI < (lEx.Area.PagNum - 1); lI++)
		{
			UC1701_CorSet(lEx.PS.Index + lI + 1, lEx.Line->X);
			UC1701_WriteByte(0x00);
		}

		UC1701_CorSet(lEx.PE.Index, lEx.Line->X);

		//data read
		lTmp = UC1701_ReadByte();

		lTmp &= (0xFF << (lEx.PE.Offset + 1));

		UC1701_WriteByte(lTmp);
	}

	UC1701_CS_HIGH;

}

/**
 * @brief   画垂直虚线，所有页的低四位画线，纵坐标为例如 0～3就可以画出，4～7就不画
 *
 * @param   lX1
 * @param   lY1
 * @param   lY2
 */
void UC1701_DrawVerDotLinSet(S_Lcd_Line_Vertical* lpLin)
{
	S_Lcd_Line_Vertical_Ex lEx;

	lEx.Line = lpLin;

	INCREASE(lEx.Line->YS, lEx.Line->YE);

	UC1701_PageGet(lEx.Line->YS, &(lEx.PS));
	UC1701_PageGet(lEx.Line->YE, &(lEx.PE));

	lEx.Area.PagNum = lEx.PE.Index - lEx.PS.Index;

	UC1701_CS_LOW;

	UC1701_CorSet(lEx.PS.Index, lEx.Line->X);

	uint8_t lTmp;

	lTmp = UC1701_ReadByte();

	if (lEx.Area.PagNum == 0)
	{
		lTmp |= (0xFF << lEx.PS.Offset) &
					(~(0xFF << (lEx.PE.Offset + 1)));

		// 画虚线
		lTmp &= 0x0F;

		UC1701_WriteByte(lTmp);
	}
	else
	{
		lTmp |= 0xFF << lEx.PS.Offset;

		// 画虚线
		lTmp &= 0x0F;

		UC1701_WriteByte(lTmp);

		my_lcd_t lI;

		for (lI = 0; lI < (lEx.Area.PagNum - 1); lI++)
		{
			UC1701_CorSet(lEx.PS.Index + lI + 1, lEx.Line->X);

			// 画虚线
			UC1701_WriteByte(0x0F);
		}

		UC1701_CorSet(lEx.PE.Index, lEx.Line->X);

		//data read
		lTmp = UC1701_ReadByte();

		lTmp |= ~(0xFF << (lEx.PE.Offset + 1));

		// 画虚线
		lTmp &= 0x0F;

		UC1701_WriteByte(lTmp);
	}

	UC1701_CS_HIGH;
}

/**
 * @brief   清除垂直虚线，清除每页的低四位，例如清除纵坐标为 0~3 8~11等等
 *
 * @param   lX1
 * @param   lY1
 * @param   lY2
 */
void UC1701_DrawVerDotLinClr(S_Lcd_Line_Vertical* lpLin)
{
	S_Lcd_Line_Vertical_Ex lEx;

	lEx.Line = lpLin;

	INCREASE(lEx.Line->YS, lEx.Line->YE);

	UC1701_PageGet(lEx.Line->YS, &(lEx.PS));
	UC1701_PageGet(lEx.Line->YE, &(lEx.PE));

	lEx.Area.PagNum = lEx.PE.Index - lEx.PS.Index;

	UC1701_CS_LOW;

	UC1701_CorSet(lEx.PS.Index, lEx.Line->X);

	uint8_t lTmp;

	lTmp = UC1701_ReadByte();

	if (lEx.Area.PagNum == 0)
	{
		// 清除虚线
		lTmp &= (~((0xFF << lEx.PS.Offset) &
					(~(0xFF << (lEx.PE.Offset + 1))))) | 0xF0;


		UC1701_WriteByte(lTmp);
	}
	else
	{
		lTmp &= (~(0xFF << lEx.PS.Offset)) | 0xF0;

		UC1701_WriteByte(lTmp);


		my_lcd_t lI;

		for (lI = 0; lI < (lEx.Area.PagNum - 1); lI++)
		{
			UC1701_CorSet(lEx.PS.Index + lI + 1, lEx.Line->X);
			//画虚线
			UC1701_WriteByte(0xF0);
		}

		UC1701_CorSet(lEx.PE.Index, lEx.Line->X);

		//data read
		lTmp = UC1701_ReadByte();

		// 画虚线
		lTmp &= (0xFF << (lEx.PE.Offset + 1)) | 0xF0;

		UC1701_WriteByte(lTmp);
	}

	UC1701_CS_HIGH;
}

/**
 * @brief   画45度斜线
 *
 * @param   lX
 * @param   lY
 * @param   lQuad 第几象限
 * @param   lLen
 */
//void UC1701_DrawDiagSet(uint8_t lX, uint8_t lY, uint8_t lQuad,
//						uint8_t lLen)
void UC1701_DrawDiagSet(S_Lcd_Line_Diagonal* lLin)
{
	int8_t lXm, lYm;
	my_lcd_t lI;

	switch (lLin->Quad)
	{
		case 1:
			lXm = 1;
			lYm = 1;
			break;

		case 2:
			lXm = -1;
			lYm = 1;
			break;

		case 3:
			lXm = -1;
			lYm = -1;
			break;

		case 4:
			lXm = 1;
			lYm = -1;
			break;

		default:
			lXm = 1;
			lYm = 1;
			break;
	}

	for (lI = 0; lI < lLin->Len; lI++)
	{
		UC1701_DrawDotSet(&(lLin->Point));
		lLin->Point.X += lXm;
		lLin->Point.Y += lYm;
	}
}

/**
 * @brief   清除45度线
 *
 * @param   lX
 * @param   lY
 * @param   lQuad
 * @param   lLen
 */
void UC1701_DrawDiagClr(S_Lcd_Line_Diagonal* lLin)
{
	int8_t lXm, lYm;
	uint8_t lI;

	switch (lLin->Quad)
	{
		case 1:
			lXm = 1;
			lYm = 1;
			break;

		case 2:
			lXm = -1;
			lYm = 1;
			break;

		case 3:
			lXm = -1;
			lYm = -1;
			break;

		case 4:
			lXm = 1;
			lYm = -1;
			break;

		default:
			lXm = 1;
			lYm = 1;
			break;
	}

	for (lI = 0; lI < lLin->Len; lI++)
	{
		UC1701_DrawDotClr(&(lLin->Point));
		lLin->Point.X += lXm;
		lLin->Point.Y += lYm;
	}
}

/**
 * @brief   画矩形
 *
 * @param   lX1
 * @param   lY1
 * @param   lX2
 * @param   lY2
 */
void UC1701_DrawRecSet(S_Lcd_Area_Rectangle* lRec)
{
	S_Lcd_Line_Horizon lHor;

	lHor.XS = lRec->PS.X;
	lHor.XE = lRec->PE.X;
	lHor.Y = lRec->PS.Y;
	UC1701_DrawHorLinSet(&lHor);

	lHor.Y = lRec->PE.Y;
	UC1701_DrawHorLinSet(&lHor);

	S_Lcd_Line_Vertical lVer;

	lVer.X = lRec->PS.X;
	lVer.YS = lRec->PS.Y;
	lVer.YE = lRec->PE.Y;
	UC1701_DrawVerLinSet(&lVer);

	lVer.X = lRec->PE.X;
	UC1701_DrawVerLinSet(&lVer);
}

/**
 * @brief   清除矩形
 *
 * @param   lX1
 * @param   lY1
 * @param   lX2
 * @param   lY2
 */
void UC1701_DrawRecClr(S_Lcd_Area_Rectangle* lRec)
{
	S_Lcd_Line_Horizon lHor;

	lHor.XS = lRec->PS.X;
	lHor.XE = lRec->PE.X;
	lHor.Y = lRec->PS.Y;
	UC1701_DrawHorLinClr(&lHor);

	lHor.Y = lRec->PE.Y;
	UC1701_DrawHorLinClr(&lHor);

	S_Lcd_Line_Vertical lVer;

	lVer.X = lRec->PS.X;
	lVer.YS = lRec->PS.Y;
	lVer.YE = lRec->PE.Y;
	UC1701_DrawVerLinClr(&lVer);

	lVer.X = lRec->PE.X;
	UC1701_DrawVerLinClr(&lVer);
}

/**
 * @brief   填充矩形
 *
 * @param   lX1
 * @param   lY1
 * @param   lX2
 * @param   lY2
 */
void UC1701_FillRecSet(S_Lcd_Area_Rectangle* lpRec)
{
	S_Lcd_Area_Rectangle_Ex lEx;

	lEx.Rec = lpRec;

	INCREASE(lEx.Rec->PS.X, lEx.Rec->PE.X);
	INCREASE(lEx.Rec->PS.Y, lEx.Rec->PE.Y);

	lEx.Area.Len = lEx.Rec->PE.X - lEx.Rec->PS.X + 1;

	// 获得点对应的页
	UC1701_PageGet(lEx.Rec->PS.Y, &(lEx.PS));
	UC1701_PageGet(lEx.Rec->PE.Y, &(lEx.PE));

	lEx.Area.PagNum = lEx.PE.Index - lEx.PS.Index;

	if (lEx.Area.PagNum == 0)
	{
		UC1701_Read(lEx.PS.Index, lEx.Rec->PS.X, lEx.Area.Len);

		my_lcd_t lI;

		for (lI = 0; lI < lEx.Area.Len; lI++)
		{
			sPage[lEx.Rec->PS.X + lI] |= ((0xFF << lEx.PS.Offset)
									& (~(0xFF << (lEx.PE.Offset + 1))));
		}
		UC1701_Write(lEx.PS.Index, lEx.Rec->PS.X, lEx.Area.Len);
	}
	else
	{
		UC1701_Read(lEx.PS.Index, lEx.Rec->PS.X, lEx.Area.Len);

		my_lcd_t lI;

		for (lI = 0; lI < lEx.Area.Len; lI++)
		{
			sPage[lEx.Rec->PS.X + lI] |= 0xFF << lEx.PS.Offset;
		}

		UC1701_Write(lEx.PS.Index, lEx.Rec->PS.X, lEx.Area.Len);

		for (lI = 0; lI < (lEx.Area.PagNum - 1); lI++)
		{
			UC1701_Read(lEx.PS.Index + lI + 1, lEx.Rec->PS.X , lEx.Area.Len);

			my_lcd_t lJ;

			for (lJ = 0; lJ < lEx.Area.Len; lJ++)
			{
				sPage[lEx.Rec->PS.X + lJ] = 0xFF;
			}
			UC1701_Write(lEx.PS.Index + lI + 1, lEx.Rec->PS.X, lEx.Area.Len);
		}

		UC1701_Read(lEx.PE.Index, lEx.Rec->PS.X, lEx.Area.Len);

		for (lI = 0; lI < lEx.Area.Len; lI++)
		{
			sPage[lEx.Rec->PS.X + lI] |= ~(0xFF << (lEx.PE.Offset + 1));
		}

		UC1701_Write(lEx.PE.Index, lEx.Rec->PS.X, lEx.Area.Len);
	}
}

/**
 * @brief   清除矩形
 *
 * @param   lX1
 * @param   lY1
 * @param   lX2
 * @param   lY2
 */
void UC1701_FillRecClr(S_Lcd_Area_Rectangle* lpRec)
{
	S_Lcd_Area_Rectangle_Ex lEx;

	lEx.Rec = lpRec;

	INCREASE(lEx.Rec->PS.X, lEx.Rec->PE.X);
	INCREASE(lEx.Rec->PS.Y, lEx.Rec->PE.Y);

	lEx.Area.Len = lEx.Rec->PE.X - lEx.Rec->PS.X + 1;

	// 获得点对应的页
	UC1701_PageGet(lEx.Rec->PS.Y, &(lEx.PS));
	UC1701_PageGet(lEx.Rec->PE.Y, &(lEx.PE));

	lEx.Area.PagNum = lEx.PE.Index - lEx.PS.Index;

	if (lEx.Area.PagNum == 0)
	{
		UC1701_Read(lEx.PS.Index, lEx.Rec->PS.X, lEx.Area.Len);

		my_lcd_t lI;

		for (lI = 0; lI < lEx.Area.Len; lI++)
		{
			sPage[lEx.Rec->PS.X + lI] &= ~((0xFF << lEx.PS.Offset)
							& (~(0xFF << (lEx.PE.Offset + 1))));
		}
		UC1701_Write(lEx.PS.Index, lEx.Rec->PS.X, lEx.Area.Len);
	}
	else
	{
		UC1701_Read(lEx.PS.Index, lEx.Rec->PS.X, lEx.Area.Len);

		my_lcd_t lI;

		for (lI = 0; lI < lEx.Area.Len; lI++)
		{
			sPage[lEx.Rec->PS.X + lI] &= ~(0xFF << lEx.PS.Offset);
		}

		UC1701_Write(lEx.PS.Index, lEx.Rec->PS.X, lEx.Area.Len);

		for (lI = 0; lI < (lEx.Area.PagNum - 1); lI++)
		{
			UC1701_Read(lEx.PS.Index + lI + 1, lEx.Rec->PS.X , lEx.Area.Len);

			my_lcd_t lJ;

			for (lJ = 0; lJ < lEx.Area.Len; lJ++)
			{
				sPage[lEx.Rec->PS.X + lJ] = 0x00;
			}

			UC1701_Write(lEx.PS.Index + lI + 1, lEx.Rec->PS.X, lEx.Area.Len);
		}

		UC1701_Read(lEx.PE.Index, lEx.Rec->PS.X, lEx.Area.Len);

		for (lI = 0; lI < lEx.Area.Len; lI++)
		{
			sPage[lEx.Rec->PS.X + lI] &= (0xFF << (lEx.PE.Offset + 1));
		}

		UC1701_Write(lEx.PE.Index, lEx.Rec->PS.X, lEx.Area.Len);
	}
}

/**
 * @brief   反转矩形
 *
 * @param   lX1
 * @param   lY1
 * @param   lX2
 * @param   lY2
 */
void UC1701_RevRec(S_Lcd_Area_Rectangle* lpRec)
{
	S_Lcd_Area_Rectangle_Ex lEx;

	lEx.Rec = lpRec;

	INCREASE(lEx.Rec->PS.X, lEx.Rec->PE.X);
	INCREASE(lEx.Rec->PS.Y, lEx.Rec->PE.Y);

	lEx.Area.Len = lEx.Rec->PE.X - lEx.Rec->PS.X + 1;

	// 获得点对应的页
	UC1701_PageGet(lEx.Rec->PS.Y, &(lEx.PS));
	UC1701_PageGet(lEx.Rec->PE.Y, &(lEx.PE));

	lEx.Area.PagNum = lEx.PE.Index - lEx.PS.Index;

	if (lEx.Area.PagNum == 0)
	{
		UC1701_Read(lEx.PS.Index, lEx.Rec->PS.X, lEx.Area.Len);

		my_lcd_t lI;

		for (lI = 0; lI < lEx.Area.Len; lI++)
		{
			sPage[lEx.Rec->PS.X + lI] ^= (0xFF << lEx.PS.Offset)
							& (~(0xFF << (lEx.PE.Offset + 1)));
		}
		UC1701_Write(lEx.PS.Index, lEx.Rec->PS.X, lEx.Area.Len);
	}
	else
	{
		UC1701_Read(lEx.PS.Index, lEx.Rec->PS.X, lEx.Area.Len);

		my_lcd_t lI;

		for (lI = 0; lI < lEx.Area.Len; lI++)
		{
			sPage[lEx.Rec->PS.X + lI] ^= 0xFF << lEx.PS.Offset;
		}

		UC1701_Write(lEx.PS.Index, lEx.Rec->PS.X, lEx.Area.Len);

		for (lI = 0; lI < (lEx.Area.PagNum - 1); lI++)
		{
			UC1701_Read(lEx.PS.Index + lI + 1, lEx.Rec->PS.X , lEx.Area.Len);

			my_lcd_t lJ;

			for (lJ = 0; lJ < lEx.Area.Len; lJ++)
			{
				sPage[lEx.Rec->PS.X + lJ] ^= 0xFF;
			}

			UC1701_Write(lEx.PS.Index + lI + 1, lEx.Rec->PS.X, lEx.Area.Len);
		}

		UC1701_Read(lEx.PE.Index, lEx.Rec->PS.X, lEx.Area.Len);

		for (lI = 0; lI < lEx.Area.Len; lI++)
		{
			sPage[lEx.Rec->PS.X + lI] ^= ~(0xFF << (lEx.PE.Offset + 1));
		}

		UC1701_Write(lEx.PE.Index, lEx.Rec->PS.X, lEx.Area.Len);
	}
}


/**
 * @brief   画滚动条
 *
 * @param   lLen 滚动条滑块的长度
 * @param   lEx 滚动条一边比线多出来的宽度
 * @param   lX1 滚动条长线的起始X
 * @param   lY1 滚动条长线的起始y
 * @param   lY2 滚动条长线的结束y
 * @param   lY3 滚动条滑块的起始y
 */
void UC1701_ScrollBar(S_Lcd_Bar_Scroll* lpBar)
{
	// 为了保证下面的lY2在控制范围内
//	if (lY1 > lY2)
//	{
//		SWAP(lY1, lY2);
//	}

	INCREASE(lpBar->YS, lpBar->YE);

	// 保证长线纵坐标不会超出
//	if (lY2 > UC1701_LINE_END)
//	{
//		lY2 = UC1701_LINE_END;
//	}
	if (lpBar->YE > UC1701_LINE_END)
	{
		lpBar->YE = UC1701_LINE_END;
	}

	// 保证长线横坐标不会超出
//	if (lX1 > UC1701_SEG_END)
//	{
//		lX1 = UC1701_SEG_END;
//	}
	if (lpBar->X > UC1701_SEG_END)
	{
		lpBar->X = UC1701_SEG_END;
	}

	// 保证滑块的单边多出长度不超出一个屏幕的宽度
//	if (lEx > UC1701_SEG_END)
//	{
//		lEx = UC1701_SEG_END;
//	}
	if (lpBar->SXEx > UC1701_SEG_END)
	{
		lpBar->SXEx = UC1701_SEG_END;
	}

	// 保证长线右边多出来的也能显示，就必须左移长线
//	if ((lX1 + lEx) > UC1701_SEG_END)
//	{
//		lX1 = UC1701_SEG_END - lEx;
//	}
	if ((lpBar->X + lpBar->SXEx) > UC1701_SEG_END)
	{
		lpBar->X = UC1701_SEG_END - lpBar->SXEx;
	}

	// 保证长线左边的宽度够显示单边的滑块宽度
//	if (lX1 < lEx)
//	{
//		lEx = lX1;
//	}
	if (lpBar->X < lpBar->SXEx)
	{
		lpBar->SXEx = lpBar->X;
	}

	// 保证滑块的开始纵向不超出
//	if (lY3 > UC1701_LINE_END)
//	{
//		lY3 = UC1701_LINE_END;
//	}
	if (lpBar->SYS > UC1701_LINE_END)
	{
		lpBar->SYS = UC1701_LINE_END;
	}

	// 保证滑块的结束纵向不超出
//	if ((lY3 + lLen) > UC1701_LINE_END)
//	{
//		lLen = UC1701_LINE_END - lY3;
//	}
	if ((lpBar->SYS + lpBar->SYLen) > UC1701_LINE_END)
	{
		lpBar->SYLen = UC1701_LINE_END - lpBar->SYS;
	}

	// 画长线
//	UC1701_DrawVerLinSet(lX1, lY1, lY2);
//	UC1701_DrawVerLinSet(lX1, lY1, lY2);
	S_Lcd_Line_Vertical lVer;

	lVer.X = lpBar->X;
	lVer.YS = lpBar->YS;
	lVer.YE = lpBar->YE;

	UC1701_DrawVerLinSet(&lVer);
	// 画滑块
//	UC1701_FillRecSet(lX1 - lEx, lY3, lX1 + lEx, lY3 + lLen);
	S_Lcd_Area_Rectangle lRec;

	lRec.PS.X = lpBar->X - lpBar->SXEx;
	lRec.PS.Y = lpBar->SYS;
	lRec.PE.X = lpBar->X + lpBar->SXEx;
	lRec.PE.Y = lpBar->SYS + lpBar->SYLen;

	UC1701_FillRecSet(&lRec);
}


/**
 * @brief   普通画圆法
 *
 * @param   lX
 * @param   lY
 * @param   lRad
 */
void UC1701_DrawCycSet(S_Lcd_Area_Cycle* lCyc)
{
	int16_t lDi;
	int8_t lA, lB;

	lA = 0;
	lB = lCyc->Radius;

	//flag of next point
	lDi = 3 - (lCyc->Radius << 1);

	S_Lcd_Point lPoint;

	while (lA <= lB)
	{
		lPoint.X = lCyc->PC.X - lB;
		lPoint.Y = lCyc->PC.Y - lA;
		UC1701_DrawDotSet(&lPoint);
		lPoint.X = lCyc->PC.X + lB;
		lPoint.Y = lCyc->PC.Y - lA;
		UC1701_DrawDotSet(&lPoint);
		lPoint.X = lCyc->PC.X - lB;
		lPoint.Y = lCyc->PC.Y + lA;
		UC1701_DrawDotSet(&lPoint);
		lPoint.X = lCyc->PC.X + lB;
		lPoint.Y = lCyc->PC.Y + lA;
		UC1701_DrawDotSet(&lPoint);
		lPoint.X = lCyc->PC.X - lA;
		lPoint.Y = lCyc->PC.Y - lB;
		UC1701_DrawDotSet(&lPoint);
		lPoint.X = lCyc->PC.X + lA;
		lPoint.Y = lCyc->PC.Y - lB;
		UC1701_DrawDotSet(&lPoint);
		lPoint.X = lCyc->PC.X - lA;
		lPoint.Y = lCyc->PC.Y + lB;
		UC1701_DrawDotSet(&lPoint);
		lPoint.X = lCyc->PC.X + lA;
		lPoint.Y = lCyc->PC.Y + lB;
		UC1701_DrawDotSet(&lPoint);

		//draw cycle by Bresenham arithmetic
		if (lDi < 0)
			lDi += lA * 4 + 6;
		else
		{
			lDi += 10 + (lA - lB) * 4;
			lB--;
		}
		lA++;

		lPoint.X = lCyc->PC.X + lA;
		lPoint.Y = lCyc->PC.Y + lB;
		UC1701_DrawDotSet(&lPoint);
	}	
}

/**
 * @brief   普通清除圆形法
 *
 * @param   lX
 * @param   lY
 * @param   lRad
 */
void UC1701_DrawCycClr(S_Lcd_Area_Cycle* lCyc)
{
	int16_t lDi;
	int8_t lA, lB;

	lA = 0;
	lB = lCyc->Radius;

	//flag of next point
	lDi = 3 - (lCyc->Radius << 1);

	S_Lcd_Point lPoint;

	while (lA <= lB)
	{
		lPoint.X = lCyc->PC.X - lB;
		lPoint.Y = lCyc->PC.Y - lA;
		UC1701_DrawDotClr(&lPoint);
		lPoint.X = lCyc->PC.X + lB;
		lPoint.Y = lCyc->PC.Y - lA;
		UC1701_DrawDotClr(&lPoint);
		lPoint.X = lCyc->PC.X - lB;
		lPoint.Y = lCyc->PC.Y + lA;
		UC1701_DrawDotClr(&lPoint);
		lPoint.X = lCyc->PC.X + lB;
		lPoint.Y = lCyc->PC.Y + lA;
		UC1701_DrawDotClr(&lPoint);
		lPoint.X = lCyc->PC.X - lA;
		lPoint.Y = lCyc->PC.Y - lB;
		UC1701_DrawDotClr(&lPoint);
		lPoint.X = lCyc->PC.X + lA;
		lPoint.Y = lCyc->PC.Y - lB;
		UC1701_DrawDotClr(&lPoint);
		lPoint.X = lCyc->PC.X - lA;
		lPoint.Y = lCyc->PC.Y + lB;
		UC1701_DrawDotClr(&lPoint);
		lPoint.X = lCyc->PC.X + lA;
		lPoint.Y = lCyc->PC.Y + lB;
		UC1701_DrawDotClr(&lPoint);

		//draw cycle by Bresenham arithmetic
		if (lDi < 0)
			lDi += lA * 4 + 6;
		else
		{
			lDi += 10 + (lA - lB) * 4;
			lB--;
		}
		lA++;

		lPoint.X = lCyc->PC.X + lA;
		lPoint.Y = lCyc->PC.Y + lB;
		UC1701_DrawDotClr(&lPoint);
	}	
}

/**
 * @brief   快速画圆法
 *
 * @param   lXc
 * @param   lYc
 * @param   lRad
 */
void UC1701_DrawCycFastSet(S_Lcd_Area_Cycle* lCyc)
{
	int8_t lX, lY;
	int16_t lDi;

	lX = 0;
	lY = lCyc->Radius;
	lDi = -(lCyc->Radius / 2);

	S_Lcd_Point lPoint;

	/*if (lRad % 2 == 0)*/
	if (lCyc->Radius & 0x01 == 0)
	{
		while (lX < lY)
		{
			lPoint.X = lCyc->PC.X - lY;
			lPoint.Y = lCyc->PC.Y - lX;
			UC1701_DrawDotSet(&lPoint);
			lPoint.X = lCyc->PC.X + lY;
			lPoint.Y = lCyc->PC.Y - lX;
			UC1701_DrawDotSet(&lPoint);
			lPoint.X = lCyc->PC.X - lY;
			lPoint.Y = lCyc->PC.Y + lX;
			UC1701_DrawDotSet(&lPoint);
			lPoint.X = lCyc->PC.X + lY;
			lPoint.Y = lCyc->PC.Y + lX;
			UC1701_DrawDotSet(&lPoint);
			lPoint.X = lCyc->PC.X - lX;
			lPoint.Y = lCyc->PC.Y - lY;
			UC1701_DrawDotSet(&lPoint);
			lPoint.X = lCyc->PC.X + lX;
			lPoint.Y = lCyc->PC.Y - lY;
			UC1701_DrawDotSet(&lPoint);
			lPoint.X = lCyc->PC.X - lX;
			lPoint.Y = lCyc->PC.Y + lY;
			UC1701_DrawDotSet(&lPoint);
			lPoint.X = lCyc->PC.X + lX;
			lPoint.Y = lCyc->PC.Y + lY;
			UC1701_DrawDotSet(&lPoint);

			lX++;
			if (lDi < 0)
				lDi += lX;
			else
			{
				lY--;
				lDi += lX - lY;
			}

			lPoint.X = lCyc->PC.X + lX;
			lPoint.Y = lCyc->PC.Y + lY;
			UC1701_DrawDotSet(&lPoint);
		}
	}
	else
	{
		while (lX < lY)
		{
			lPoint.X = lCyc->PC.X - lY;
			lPoint.Y = lCyc->PC.Y - lX;
			UC1701_DrawDotSet(&lPoint);
			lPoint.X = lCyc->PC.X + lY;
			lPoint.Y = lCyc->PC.Y - lX;
			UC1701_DrawDotSet(&lPoint);
			lPoint.X = lCyc->PC.X - lY;
			lPoint.Y = lCyc->PC.Y + lX;
			UC1701_DrawDotSet(&lPoint);
			lPoint.X = lCyc->PC.X + lY;
			lPoint.Y = lCyc->PC.Y + lX;
			UC1701_DrawDotSet(&lPoint);
			lPoint.X = lCyc->PC.X - lX;
			lPoint.Y = lCyc->PC.Y - lY;
			UC1701_DrawDotSet(&lPoint);
			lPoint.X = lCyc->PC.X + lX;
			lPoint.Y = lCyc->PC.Y - lY;
			UC1701_DrawDotSet(&lPoint);
			lPoint.X = lCyc->PC.X - lX;
			lPoint.Y = lCyc->PC.Y + lY;
			UC1701_DrawDotSet(&lPoint);
			lPoint.X = lCyc->PC.X + lX;
			lPoint.Y = lCyc->PC.Y + lY;
			UC1701_DrawDotSet(&lPoint);

			lX++;
			if (lDi < 0)
				lDi += lX + 1;
			else
			{
				lY--;
				lDi += lX - lY + 1;
			}

			lPoint.X = lCyc->PC.X + lX;
			lPoint.Y = lCyc->PC.Y + lY;
			UC1701_DrawDotSet(&lPoint);
		}
	}
}

/**
 * @brief   快速清除圆法
 *
 * @param   lXc
 * @param   lYc
 * @param   lRad
 */
void UC1701_DrawCycFastClr(S_Lcd_Area_Cycle* lCyc)
{
	int8_t lX, lY;
	int16_t lDi;

	lX = 0;
	lY = lCyc->Radius;
	lDi = -(lCyc->Radius / 2);


	S_Lcd_Point lPoint;

	/*if (lRad % 2 == 0)*/
	if (lCyc->Radius & 0x01 == 0)
	{
		while (lX < lY)
		{
			lPoint.X = lCyc->PC.X - lY;
			lPoint.Y = lCyc->PC.Y - lX;
			UC1701_DrawDotClr(&lPoint);
			lPoint.X = lCyc->PC.X + lY;
			lPoint.Y = lCyc->PC.Y - lX;
			UC1701_DrawDotClr(&lPoint);
			lPoint.X = lCyc->PC.X - lY;
			lPoint.Y = lCyc->PC.Y + lX;
			UC1701_DrawDotClr(&lPoint);
			lPoint.X = lCyc->PC.X + lY;
			lPoint.Y = lCyc->PC.Y + lX;
			UC1701_DrawDotClr(&lPoint);
			lPoint.X = lCyc->PC.X - lX;
			lPoint.Y = lCyc->PC.Y - lY;
			UC1701_DrawDotClr(&lPoint);
			lPoint.X = lCyc->PC.X + lX;
			lPoint.Y = lCyc->PC.Y - lY;
			UC1701_DrawDotClr(&lPoint);
			lPoint.X = lCyc->PC.X - lX;
			lPoint.Y = lCyc->PC.Y + lY;
			UC1701_DrawDotClr(&lPoint);
			lPoint.X = lCyc->PC.X + lX;
			lPoint.Y = lCyc->PC.Y + lY;
			UC1701_DrawDotClr(&lPoint);

			lX++;
			if (lDi < 0)
				lDi += lX;
			else
			{
				lY--;
				lDi += lX - lY;
			}

			lPoint.X = lCyc->PC.X + lX;
			lPoint.Y = lCyc->PC.Y + lY;
			UC1701_DrawDotClr(&lPoint);
		}
	}
	else
	{
		while (lX < lY)
		{
			lPoint.X = lCyc->PC.X - lY;
			lPoint.Y = lCyc->PC.Y - lX;
			UC1701_DrawDotClr(&lPoint);
			lPoint.X = lCyc->PC.X + lY;
			lPoint.Y = lCyc->PC.Y - lX;
			UC1701_DrawDotClr(&lPoint);
			lPoint.X = lCyc->PC.X - lY;
			lPoint.Y = lCyc->PC.Y + lX;
			UC1701_DrawDotClr(&lPoint);
			lPoint.X = lCyc->PC.X + lY;
			lPoint.Y = lCyc->PC.Y + lX;
			UC1701_DrawDotClr(&lPoint);
			lPoint.X = lCyc->PC.X - lX;
			lPoint.Y = lCyc->PC.Y - lY;
			UC1701_DrawDotClr(&lPoint);
			lPoint.X = lCyc->PC.X + lX;
			lPoint.Y = lCyc->PC.Y - lY;
			UC1701_DrawDotClr(&lPoint);
			lPoint.X = lCyc->PC.X - lX;
			lPoint.Y = lCyc->PC.Y + lY;
			UC1701_DrawDotClr(&lPoint);
			lPoint.X = lCyc->PC.X + lX;
			lPoint.Y = lCyc->PC.Y + lY;
			UC1701_DrawDotClr(&lPoint);

			lX++;
			if (lDi < 0)
				lDi += lX + 1;
			else
			{
				lY--;
				lDi += lX - lY + 1;
			}

			lPoint.X = lCyc->PC.X + lX;
			lPoint.Y = lCyc->PC.Y + lY;
			UC1701_DrawDotClr(&lPoint);
		}
	}
}

/**
 * @brief   画矩形带阴影外框
 *
 * @param   lX1
 * @param   lY1
 * @param   lX2
 * @param   lY2
 */
void UC1701_DrawRecFramSet(S_Lcd_Area_RectangleShade* lpFrame)
{
//	if (lX1 > lX2)
//		SWAP(lX1, lX2);
//
//	if (lY1 > lY2)
//		SWAP(lY1, lY2);

	// 坐标原点在左下角
//	UC1701_DrawHorLinSet(lX1, lY1, lX2 - 3);
//	UC1701_DrawVerLinSet(lX1, lY1, lY2 - 3);
//	UC1701_FillRecSet(lX1 + 3, lY2 - 3, lX2, lY2);
//	UC1701_FillRecSet(lX2 - 3, lY1 + 3, lX2, lY2 - 3);
//	UC1701_DrawDotSet(lX1 + 1, lY2 - 3);
//	UC1701_DrawDotSet(lX1 + 2, lY2 - 3);
//	UC1701_DrawDotSet(lX2 - 3, lY1 + 1);
//	UC1701_DrawDotSet(lX2 - 3, lY1 + 2);

	INCREASE(lpFrame->PS.X, lpFrame->PE.X);
	INCREASE(lpFrame->PS.Y, lpFrame->PE.Y);

	S_Lcd_Line_Horizon lHor;

	lHor.XS = lpFrame->PS.X;
	lHor.Y = lpFrame->PE.Y;
	lHor.XE = lpFrame->PE.X - lpFrame->Ex.X;
	UC1701_DrawHorLinSet(&lHor);

	S_Lcd_Line_Vertical lVer;

	lVer.X = lpFrame->PS.X;
	lVer.YS = lpFrame->PS.Y + lpFrame->Ex.Y;
	lVer.YE = lpFrame->PE.Y;
	UC1701_DrawVerLinSet(&lVer);

	S_Lcd_Area_Rectangle lRec;

	lRec.PS.X = lpFrame->PS.X + lpFrame->Ex.X;
	lRec.PS.Y = lpFrame->PS.Y;
	lRec.PE.X = lpFrame->PE.X;
	lRec.PE.Y = lRec.PS.Y + lpFrame->Ex.Y;
	UC1701_FillRecSet(&lRec);

	lRec.PS.X = lpFrame->PE.X - lpFrame->Ex.X;
	lRec.PS.Y = lpFrame->PS.Y + lpFrame->Ex.Y;
	lRec.PE.X = lpFrame->PE.X;
	lRec.PE.Y = lpFrame->PE.Y - lpFrame->Ex.Y;
	UC1701_FillRecSet(&lRec);

	lHor.XS = lpFrame->PS.X + 1;
	lHor.Y = lpFrame->PS.Y + lpFrame->Ex.Y;
	lHor.XE = lpFrame->PS.X + lpFrame->Ex.X - 1;
	UC1701_DrawHorLinSet(&lHor);

	lVer.X = lpFrame->PE.X - lpFrame->Ex.X;
	lVer.YS = lpFrame->PE.Y - 1;
	lVer.YE = lpFrame->PE.Y - lpFrame->Ex.Y + 1;
	UC1701_DrawVerLinSet(&lVer);

	// 上斜边
	/*UC1701_DrawDotSet(lX1 + 1, lY2 - 2);*/
	/*UC1701_DrawDotSet(lX1 + 2, lY2 - 2);*/
	/*UC1701_DrawDotSet(lX1 + 2, lY2 - 1);*/

	// 右斜边
	/*UC1701_DrawDotSet(lX2 - 2, lY1 + 1);*/
	/*UC1701_DrawDotSet(lX2 - 2, lY1 + 2);*/
	/*UC1701_DrawDotSet(lX2 - 1, lY1 + 2);*/
}

/**
 * @brief   清除矩形阴影
 *
 * @param   lX1
 * @param   lY1
 * @param   lX2
 * @param   lY2
 */
void UC1701_DrawRecFramClr(S_Lcd_Area_RectangleShade* lpFrame)
{
//	if (lX1 > lX2)
//		SWAP(lX1, lX2);
//
//	if (lY1 > lY2)
//		SWAP(lY1, lY2);

	// 坐标原点在左下角
//	UC1701_DrawHorLinClr(lX1, lY1, lX2 - 3);
//	UC1701_DrawVerLinClr(lX1, lY1, lY2 - 3);
//	UC1701_FillRecClr(lX1 + 3, lY2 - 3, lX2, lY2);
//	UC1701_FillRecClr(lX2 - 3, lY1 + 3, lX2, lY2 - 3);
//	UC1701_DrawDotClr(lX1 + 1, lY2 - 3);
//	UC1701_DrawDotClr(lX1 + 2, lY2 - 3);
//	UC1701_DrawDotClr(lX2 - 3, lY1 + 1);
//	UC1701_DrawDotClr(lX2 - 3, lY1 + 2);

	// 坐标原点在左上角
	INCREASE(lpFrame->PS.X, lpFrame->PE.X);
	INCREASE(lpFrame->PS.Y, lpFrame->PE.Y);

	S_Lcd_Line_Horizon lHor;

	lHor.XS = lpFrame->PS.X;
	lHor.Y = lpFrame->PE.Y;
	lHor.XE = lpFrame->PE.X - lpFrame->Ex.X;
	UC1701_DrawHorLinClr(&lHor);

	S_Lcd_Line_Vertical lVer;

	lVer.X = lpFrame->PS.X;
	lVer.YS = lpFrame->PS.Y + lpFrame->Ex.Y;
	lVer.YE = lpFrame->PE.Y;
	UC1701_DrawVerLinClr(&lVer);

	S_Lcd_Area_Rectangle lRec;

	lRec.PS.X = lpFrame->PS.X + lpFrame->Ex.X;
	lRec.PS.Y = lpFrame->PS.Y;
	lRec.PE.X = lpFrame->PE.X;
	lRec.PE.Y = lRec.PS.Y + lpFrame->Ex.Y;
	UC1701_FillRecClr(&lRec);

	lRec.PS.X = lpFrame->PE.X - lpFrame->Ex.X;
	lRec.PS.Y = lpFrame->PS.Y + lpFrame->Ex.Y;
	lRec.PE.X = lpFrame->PE.X;
	lRec.PE.Y = lpFrame->PE.Y - lpFrame->Ex.Y;
	UC1701_FillRecClr(&lRec);

	lHor.XS = lpFrame->PS.X + 1;
	lHor.Y = lpFrame->PS.Y + lpFrame->Ex.Y;
	lHor.XE = lpFrame->PS.X + lpFrame->Ex.X - 1;
	UC1701_DrawHorLinClr(&lHor);

	lVer.X = lpFrame->PE.X - lpFrame->Ex.X;
	lVer.YS = lpFrame->PE.Y - 1;
	lVer.YE = lpFrame->PE.Y - lpFrame->Ex.Y + 1;
	UC1701_DrawVerLinClr(&lVer);
}

/**
 * @brief   画折边矩形
 *
 * @param   lX1
 * @param   lY1
 * @param   lX2
 * @param   lY2
 */
//void UC1701_DrawRecDiagSet(uint8_t lX1, uint8_t lY1, uint8_t lX2,
//							uint8_t lY2)
//{
//	if (lX1 > lX2)
//		SWAP(lX1, lX2);
//
//	if (lY1 > lY2)
//		SWAP(lY1, lY2);
//
//	UC1701_DrawHorLinSet(lX1 + 6, lY1, lX2 - 6);
//	UC1701_DrawHorLinSet(lX1 + 6, lY2, lX2 - 6);
//	UC1701_DrawVerLinSet(lX1, lY1 + 6, lY2 - 6);
//	UC1701_DrawVerLinSet(lX2, lY1 + 6, lY2 - 6);
//	UC1701_DrawDiagSet(lX1, lY1 + 6, 4, 6);
//	UC1701_DrawDiagSet(lX2 - 6, lY1, 1, 6);
//	UC1701_DrawDiagSet(lX1, lY2 - 6, 1, 6);
//	UC1701_DrawDiagSet(lX2 - 6, lY2, 4, 6);
//}

/**
 * @brief   清除折边矩形
 *
 * @param   lX1
 * @param   lY1
 * @param   lX2
 * @param   lY2
 */
//void UC1701_DrawRecDiagClr(uint8_t lX1, uint8_t lY1, uint8_t lX2,
//							uint8_t lY2)
//{
//	if (lX1 > lX2)
//		SWAP(lX1, lX2);
//
//	if (lY1 > lY2)
//		SWAP(lY1, lY2);
//
//	UC1701_DrawHorLinClr(lX1 + 6, lY1, lX2 - 6);
//	UC1701_DrawHorLinClr(lX1 + 6, lY2, lX2 - 6);
//	UC1701_DrawVerLinClr(lX1, lY1 + 6, lY2 - 6);
//	UC1701_DrawVerLinClr(lX2, lY1 + 6, lY2 - 6);
//	UC1701_DrawDiagClr(lX1, lY1 + 6, 4, 6);
//	UC1701_DrawDiagClr(lX2 - 6, lY1, 1, 6);
//	UC1701_DrawDiagClr(lX1, lY2 - 6, 1, 6);
//	UC1701_DrawDiagClr(lX2 - 6, lY2, 4, 6);
//}

/**
 * @brief   画折边矩形带阴影
 *
 * @param   lX1
 * @param   lY1
 * @param   lX2
 * @param   lY2
 */
//void UC1701_DrawRecDiagFramSet(uint8_t lX1, uint8_t lY1, uint8_t lX2,
//								uint8_t lY2)
//{
//	if (lX1 > lX2)
//		SWAP(lX1, lX2);
//
//	if (lY1 > lY2)
//		SWAP(lY1, lY2);
//
//	UC1701_DrawHorLinSet(lX1 + 6, lY1, lX2 - 9);
//	UC1701_DrawVerLinSet(lX1, lY1 + 6, lY2 - 9);
//	UC1701_DrawDiagSet(lX1, lY1 + 6, 4, 6);
//	UC1701_DrawDiagSet(lX2 - 9, lY1, 1, 9);
//	UC1701_DrawDiagSet(lX1, lY2 - 9, 1, 9);
//	UC1701_DrawDiagSet(lX2 - 9, lY2 - 3, 4, 6);
//	UC1701_DrawDiagSet(lX2 - 6, lY2, 4, 6);
//	UC1701_FillRecSet(lX1 + 9, lY2 - 3, lX2 - 6, lY2);
//	UC1701_FillRecSet(lX2 - 3, lY1 + 9, lX2, lY2 - 6);
//	UC1701_DrawDotSet(lX1 + 7, lY2 - 3);
//	UC1701_DrawDotSet(lX1 + 8, lY2 - 3);
//	UC1701_DrawDotSet(lX1 + 8, lY2 - 2);
//	UC1701_FillRecSet(lX2 - 6, lY2 - 6, lX2 - 3, lY2 - 3);
//	UC1701_DrawDotSet(lX2 - 7, lY2 - 4);
//	UC1701_DrawDotSet(lX2 - 4, lY2 - 7);
//	UC1701_DrawDotSet(lX2 - 5, lY2 - 2);
//	UC1701_DrawDotSet(lX2 - 2, lY2 - 5);
//	UC1701_DrawDotSet(lX2 - 3, lY1 + 8);
//	UC1701_DrawDotSet(lX2 - 3, lY1 + 7);
//	UC1701_DrawDotSet(lX2 - 2, lY1 + 8);
//}

/**
 * @brief   清除折边矩形阴影
 *
 * @param   lX1
 * @param   lY1
 * @param   lX2
 * @param   lY2
 */
//void UC1701_DrawRecDiagFramClr(uint8_t lX1, uint8_t lY1, uint8_t lX2,
//								uint8_t lY2)
//{
//	if (lX1 > lX2)
//		SWAP(lX1, lX2);
//
//	if (lY1 > lY2)
//		SWAP(lY1, lY2);
//
//	UC1701_DrawHorLinClr(lX1 + 6, lY1, lX2 - 9);
//	UC1701_DrawVerLinClr(lX1, lY1 + 6, lY2 - 9);
//	UC1701_DrawDiagClr(lX1, lY1 + 6, 4, 6);
//	UC1701_DrawDiagClr(lX2 - 9, lY1, 1, 9);
//	UC1701_DrawDiagClr(lX1, lY2 - 9, 1, 9);
//	UC1701_DrawDiagClr(lX2 - 9, lY2 - 3, 4, 6);
//	UC1701_DrawDiagClr(lX2 - 6, lY2, 4, 6);
//	UC1701_FillRecClr(lX1 + 9, lY2 - 3, lX2 - 6, lY2);
//	UC1701_FillRecClr(lX2 - 3, lY1 + 9, lX2, lY2 - 6);
//	UC1701_DrawDotClr(lX1 + 7, lY2 - 3);
//	UC1701_DrawDotClr(lX1 + 8, lY2 - 3);
//	UC1701_DrawDotClr(lX1 + 8, lY2 - 2);
//	UC1701_FillRecClr(lX2 - 6, lY2 - 6, lX2 - 3, lY2 - 3);
//	UC1701_DrawDotClr(lX2 - 7, lY2 - 4);
//	UC1701_DrawDotClr(lX2 - 4, lY2 - 7);
//	UC1701_DrawDotClr(lX2 - 5, lY2 - 2);
//	UC1701_DrawDotClr(lX2 - 2, lY2 - 5);
//	UC1701_DrawDotClr(lX2 - 3, lY1 + 8);
//	UC1701_DrawDotClr(lX2 - 3, lY1 + 7);
//	UC1701_DrawDotClr(lX2 - 2, lY1 + 8);
//}

/**
 * @brief   显示字符
 *
 * @param   lX
 * @param   lY
 * @param   lpBuffer
 * @param   lXSize
 * @param   lYSize
 */
void UC1701_CharSet(S_Lcd_Char* lpChar)
{
	uint8_t lCol, lLin;
	my_lcd_t lI, lJ;
	S_Lcd_Char_Ex lEx;

	lEx.Char = lpChar;

	lEx.Area.PagNum = 0;

	UC1701_PageGet(lEx.Char->PS.Y, &(lEx.PS));

	// be careful lPagEnd and lOfSetEn
	// for example: lY = 7; lYSize = 9;
	// so lYEnd is 15,in page 1
	// but all of the page1 will be overwrited
	// if lPagEnd = (lY + lYSize - 1) >> 3 and then lPagNum = 0 
	// this is wrong ,so lPagEnd = (lY + lYSize) >> 3
	// lOfSetEn = (lY + lYSize) & 0x07 = 0
	/*lPagEnd = (lY + lYSize) >> 3;*/
	// if lY = 7, lYSize = 10;
	// lOfSetEn = (lY + lYSize - 1) & 0x07 = 0
	// look at the function, 
	// lOfSetEn = (lY + lYSize) & 0x07 = 1 will be better.
	/*lOfSetEn = (lY + lYSize) & 0x07;*/

	UC1701_PageGet(lEx.Char->PS.Y + lEx.Char->Pixel.Y, &(lEx.PE));

	//lPagNum = (lYSize >> 3) - 1;
	// be care if lYSize < 8

	if (lEx.PE.Index > lEx.PS.Index)
	{
		lEx.Area.PagNum = lEx.PE.Index - lEx.PS.Index - 1;
	}

	// 横向取模，所以涉及到字节存储数据
	// 一行占有几个字节
	lEx.XRem = lEx.Char->Pixel.X & 0x07;
	lEx.XQuot = lEx.Char->Pixel.X >> 3;

	if (lEx.XRem)
	{
		lEx.XQuot += 1;
	}

	// 用来作为一个字库在显示的时候的Y轴的偏移量
	lEx.YBase = 0;

	uint8_t lTmp;

	if (lEx.PS.Offset)
	{
		if (lEx.PE.Index > lEx.PS.Index)
		{
			UC1701_Read(lEx.PS.Index, lEx.Char->PS.X, lEx.Char->Pixel.X);

			for (lI = 0; lI < lEx.XQuot; lI++)
			{
				for (lCol = 0; lCol < 8; lCol++)
				{
					if (lEx.XRem > 0)
					{
						if (((lI + 1) == lEx.XQuot) && (lCol == lEx.XRem))
							break;
					}
					lTmp = 0;

					for (lLin = lEx.PS.Offset; lLin < 8; lLin++)
					{
						if ((*(lEx.Char->Font +
								lEx.XQuot * (lLin - lEx.PS.Offset) + lI))
								& (1 << (7 - lCol)))
							lTmp |= 1 << lLin;
					}
					sPage[lEx.Char->PS.X + lI * 8 + lCol] &=
											~(0xFF << lEx.PS.Offset);
					sPage[lEx.Char->PS.X + lI * 8 + lCol] |= lTmp;
				}
			}

			UC1701_Write(lEx.PS.Index, lEx.Char->PS.X, lEx.Char->Pixel.X);
		}// end of if (lPagEnd > lPag)
		else
		{
			UC1701_Read(lEx.PS.Index, lEx.Char->PS.X, lEx.Char->Pixel.X);

			for (lI = 0; lI < lEx.XQuot; lI++)
			{
				for (lCol = 0; lCol < 8; lCol++)
				{
//					if (lXRem > 0)
					if (lEx.XRem > 0)
					{
						if (((lI + 1) == lEx.XQuot) && (lCol == lEx.XRem))
							break;
					}
					lTmp = 0;

					for (lLin = lEx.PS.Offset; lLin < lEx.PE.Offset; lLin++)
					{
						if ((*(lEx.Char->Font +
								lEx.XQuot * (lLin - lEx.PS.Offset) + lI))
								& (1 << (7 - lCol)))
							lTmp |= 1 << lLin;
					}
					sPage[lEx.Char->PS.X + lI * 8 + lCol] &=
						(~(0xFF << lEx.PS.Offset)) | (0xFF << lEx.PE.Offset);
					sPage[lEx.Char->PS.X + lI * 8 + lCol] |= lTmp;
				}
			}

			UC1701_Write(lEx.PS.Index, lEx.Char->PS.X, lEx.Char->Pixel.X);
		}// end of else of if (lPagEnd > lPag)
		lEx.YBase = 8 - lEx.PS.Offset;
	}// end of if (lOfSet)
	else
	{
		if (lEx.PE.Index > lEx.PS.Index)
		{
			for (lI = 0; lI < lEx.XQuot; lI++)
			{
				for (lCol = 0; lCol < 8; lCol++)
				{
					if (lEx.XRem > 0)
					{
						if (((lI + 1) == lEx.XQuot) && (lCol == lEx.XRem))
							break;
					}
					lTmp = 0;
					for (lLin = 0; lLin < 8; lLin++)
					{
						if ((*(lEx.Char->Font + lEx.XQuot * lLin + lI))
								& (1 << (7 - lCol)))
							lTmp |= 1 << lLin;
					}
					sPage[lEx.Char->PS.X + lI * 8 + lCol] = lTmp;
				}
			}

			UC1701_Write(lEx.PS.Index, lEx.Char->PS.X, lEx.Char->Pixel.X);
		}// end of if (lPagEnd > lPag)
		else 
		{
			UC1701_Read(lEx.PS.Index, lEx.Char->PS.X, lEx.Char->Pixel.X);

			for (lI = 0; lI < lEx.XQuot; lI++)
			{
				for (lCol = 0; lCol < 8; lCol++)
				{
					if (lEx.XRem > 0)
					{
						if (((lI + 1) == lEx.XQuot) && (lCol == lEx.XRem))
							break;
					}
					lTmp = 0;

					for (lLin = 0; lLin < lEx.PE.Offset; lLin++)
					{
						if ((*(lEx.Char->Font + lEx.XQuot * lLin + lI))
								& (1 << (7 - lCol)))
							lTmp |= 1 << lLin;
					}
					sPage[lEx.Char->PS.X + lI * 8 + lCol] &=
												(0xFF << lEx.PE.Offset);
					sPage[lEx.Char->PS.X + lI * 8 + lCol] |= lTmp;
				}
			}
			UC1701_Write(lEx.PS.Index, lEx.Char->PS.X, lEx.Char->Pixel.X);
		}// end of else of if (lPagEnd > lPag)
		lEx.YBase = 8;
	}// end of else of if (lOfSet)

	if (lEx.Area.PagNum)
	{
		for (lJ = 0; lJ < lEx.Area.PagNum; lJ++)
		{
			for (lI = 0; lI < lEx.XQuot; lI++)
			{
				for (lCol = 0; lCol < 8; lCol++)
				{
					if (lEx.XRem > 0)
					{
						if (((lI + 1) == lEx.XQuot) && (lCol == lEx.XRem))
							break;
					}
					lTmp = 0;
					for (lLin = 0; lLin < 8; lLin++)
					{
						if ((*(lEx.Char->Font + lEx.XQuot * (lLin + lEx.YBase)
								+ lI)) & (1 << (7 - lCol)))
							lTmp |= 1 << lLin;
					}
					sPage[lEx.Char->PS.X + lI * 8 + lCol] = lTmp;
				}
			}
			lEx.YBase += 8;

			UC1701_Write(lEx.PS.Index + lJ + 1, lEx.Char->PS.X,
									lEx.Char->Pixel.X);
		}
	}// end of if (lPagNum)

	if ((lEx.PE.Index > lEx.PS.Index) && (lEx.PE.Offset))
	{
		UC1701_Read(lEx.PS.Index + lEx.Area.PagNum + 1, lEx.Char->PS.X,
						lEx.Char->Pixel.X);

		for (lI = 0; lI < lEx.XQuot; lI++)
		{
			for (lCol = 0; lCol < 8; lCol++)
			{
				if (lEx.XRem > 0)
				{
					if (((lI + 1) == lEx.XQuot) && (lCol == lEx.XRem))
						break;
				}
				lTmp = 0;

				for (lLin = 0; lLin < lEx.PE.Offset; lLin++)
				{
					if ((*(lEx.Char->Font + lEx.XQuot * (lLin + lEx.YBase)
								+ lI)) & (1 << (7 - lCol)))
						lTmp |= 1 << lLin;
				}
				sPage[lEx.Char->PS.X + lI * 8 + lCol] &=
												(0xFF << lEx.PE.Offset);
				sPage[lEx.Char->PS.X + lI * 8 + lCol] |= lTmp;
			}
		}

		UC1701_Write(lEx.PS.Index + lEx.Area.PagNum + 1, lEx.Char->PS.X,
									lEx.Char->Pixel.X);
	}// end of if ((lPagEnd > lPag) && (lOfSetEn))
}

/**
 * @brief   清除字符
 *
 * @param   lX
 * @param   lY
 * @param   lpBuffer
 * @param   lXSize
 * @param   lYSize
 */
void UC1701_CharClr(S_Lcd_Char* lpChar)
{
	uint8_t lCol, lLin;
	my_lcd_t lI, lJ;
	S_Lcd_Char_Ex lEx;

	lEx.Char = lpChar;

	lEx.Area.PagNum = 0;

	UC1701_PageGet(lEx.Char->PS.Y, &(lEx.PS));

	// be careful lPagEnd and lOfSetEn
	// for example: lY = 7; lYSize = 9;
	// so lYEnd is 15,in page 1
	// but all of the page1 will be overwrited
	// if lPagEnd = (lY + lYSize - 1) >> 3 and then lPagNum = 0
	// this is wrong ,so lPagEnd = (lY + lYSize) >> 3
	// lOfSetEn = (lY + lYSize) & 0x07 = 0
	/*lPagEnd = (lY + lYSize) >> 3;*/
	// if lY = 7, lYSize = 10;
	// lOfSetEn = (lY + lYSize - 1) & 0x07 = 0
	// look at the function,
	// lOfSetEn = (lY + lYSize) & 0x07 = 1 will be better.
	/*lOfSetEn = (lY + lYSize) & 0x07;*/

	UC1701_PageGet(lEx.Char->PS.Y + lEx.Char->Pixel.Y, &(lEx.PE));

	//lPagNum = (lYSize >> 3) - 1;
	// be care if lYSize < 8

	if (lEx.PE.Index > lEx.PS.Index)
	{
		lEx.Area.PagNum = lEx.PE.Index - lEx.PS.Index - 1;
	}

	// 横向取模，所以涉及到字节存储数据
	// 一行占有几个字节
	lEx.XRem = lEx.Char->Pixel.X & 0x07;
	lEx.XQuot = lEx.Char->Pixel.X >> 3;

	if (lEx.XRem)
	{
		lEx.XQuot += 1;
	}

	// 用来作为一个字库在显示的时候的Y轴的偏移量
	lEx.YBase = 0;

	uint8_t lTmp;

	if (lEx.PS.Offset)
	{
		if (lEx.PE.Index > lEx.PS.Index)
		{
			UC1701_Read(lEx.PS.Index, lEx.Char->PS.X, lEx.Char->Pixel.X);

			for (lI = 0; lI < lEx.XQuot; lI++)
			{
				for (lCol = 0; lCol < 8; lCol++)
				{
					if (lEx.XRem > 0)
					{
						if (((lI + 1) == lEx.XQuot) && (lCol == lEx.XRem))
							break;
					}
					lTmp = 0;

					for (lLin = lEx.PS.Offset; lLin < 8; lLin++)
					{
						if ((*(lEx.Char->Font +
								lEx.XQuot * (lLin - lEx.PS.Offset) + lI))
								& (1 << (7 - lCol)))
							lTmp |= 1 << lLin;
					}
//					sPage[lEx.Char->PS.X + lI * 8 + lCol] &=
//											~(0xFF << lEx.PS.Offset);
					// 取反
					lTmp ^= 0xFF;
//					sPage[lEx.Char->PS.X + lI * 8 + lCol] |= lTmp;
					sPage[lEx.Char->PS.X + lI * 8 + lCol] &= lTmp;
				}
			}

			UC1701_Write(lEx.PS.Index, lEx.Char->PS.X, lEx.Char->Pixel.X);
		}// end of if (lPagEnd > lPag)
		else
		{
			UC1701_Read(lEx.PS.Index, lEx.Char->PS.X, lEx.Char->Pixel.X);

			for (lI = 0; lI < lEx.XQuot; lI++)
			{
				for (lCol = 0; lCol < 8; lCol++)
				{
//					if (lXRem > 0)
					if (lEx.XRem > 0)
					{
						if (((lI + 1) == lEx.XQuot) && (lCol == lEx.XRem))
							break;
					}
					lTmp = 0;

					for (lLin = lEx.PS.Offset; lLin < lEx.PE.Offset; lLin++)
					{
						if ((*(lEx.Char->Font +
								lEx.XQuot * (lLin - lEx.PS.Offset) + lI))
								& (1 << (7 - lCol)))
							lTmp |= 1 << lLin;
					}
//					sPage[lEx.Char->PS.X + lI * 8 + lCol] &=
//						(~(0xFF << lEx.PS.Offset)) | (0xFF << lEx.PE.Offset);
					// 取反
					lTmp ^= 0xFF;
//					sPage[lEx.Char->PS.X + lI * 8 + lCol] |= lTmp;
					sPage[lEx.Char->PS.X + lI * 8 + lCol] &= lTmp;
				}
			}

			UC1701_Write(lEx.PS.Index, lEx.Char->PS.X, lEx.Char->Pixel.X);
		}// end of else of if (lPagEnd > lPag)
		lEx.YBase = 8 - lEx.PS.Offset;
	}// end of if (lOfSet)
	else
	{
		if (lEx.PE.Index > lEx.PS.Index)
		{
			for (lI = 0; lI < lEx.XQuot; lI++)
			{
				for (lCol = 0; lCol < 8; lCol++)
				{
					if (lEx.XRem > 0)
					{
						if (((lI + 1) == lEx.XQuot) && (lCol == lEx.XRem))
							break;
					}
					lTmp = 0;
					for (lLin = 0; lLin < 8; lLin++)
					{
						if ((*(lEx.Char->Font + lEx.XQuot * lLin + lI))
								& (1 << (7 - lCol)))
							lTmp |= 1 << lLin;
					}
					// 取反
					lTmp ^= 0xFF;
//					sPage[lEx.Char->PS.X + lI * 8 + lCol] = lTmp;
					sPage[lEx.Char->PS.X + lI * 8 + lCol] = lTmp;
				}
			}

			UC1701_Write(lEx.PS.Index, lEx.Char->PS.X, lEx.Char->Pixel.X);
		}// end of if (lPagEnd > lPag)
		else
		{
			UC1701_Read(lEx.PS.Index, lEx.Char->PS.X, lEx.Char->Pixel.X);

			for (lI = 0; lI < lEx.XQuot; lI++)
			{
				for (lCol = 0; lCol < 8; lCol++)
				{
					if (lEx.XRem > 0)
					{
						if (((lI + 1) == lEx.XQuot) && (lCol == lEx.XRem))
							break;
					}
					lTmp = 0;

					for (lLin = 0; lLin < lEx.PE.Offset; lLin++)
					{
						if ((*(lEx.Char->Font + lEx.XQuot * lLin + lI))
								& (1 << (7 - lCol)))
							lTmp |= 1 << lLin;
					}
//					sPage[lEx.Char->PS.X + lI * 8 + lCol] &=
//												(0xFF << lEx.PE.Offset);
					// 取反
					lTmp ^= 0xFF;
//					sPage[lEx.Char->PS.X + lI * 8 + lCol] |= lTmp;
					sPage[lEx.Char->PS.X + lI * 8 + lCol] &= lTmp;
				}
			}
			UC1701_Write(lEx.PS.Index, lEx.Char->PS.X, lEx.Char->Pixel.X);
		}// end of else of if (lPagEnd > lPag)
		lEx.YBase = 8;
	}// end of else of if (lOfSet)

	if (lEx.Area.PagNum)
	{
		for (lJ = 0; lJ < lEx.Area.PagNum; lJ++)
		{
			for (lI = 0; lI < lEx.XQuot; lI++)
			{
				for (lCol = 0; lCol < 8; lCol++)
				{
					if (lEx.XRem > 0)
					{
						if (((lI + 1) == lEx.XQuot) && (lCol == lEx.XRem))
							break;
					}
					lTmp = 0;
					for (lLin = 0; lLin < 8; lLin++)
					{
						if ((*(lEx.Char->Font + lEx.XQuot * (lLin + lEx.YBase)
								+ lI)) & (1 << (7 - lCol)))
							lTmp |= 1 << lLin;
					}
					// 取反
					lTmp ^= 0xFF;
//					sPage[lEx.Char->PS.X + lI * 8 + lCol] = lTmp;
					sPage[lEx.Char->PS.X + lI * 8 + lCol] = lTmp;
				}
			}
			lEx.YBase += 8;

			UC1701_Write(lEx.PS.Index + lJ + 1, lEx.Char->PS.X,
									lEx.Char->Pixel.X);
		}
	}// end of if (lPagNum)

	if ((lEx.PE.Index > lEx.PS.Index) && (lEx.PE.Offset))
	{
		UC1701_Read(lEx.PS.Index + lEx.Area.PagNum + 1, lEx.Char->PS.X,
						lEx.Char->Pixel.X);

		for (lI = 0; lI < lEx.XQuot; lI++)
		{
			for (lCol = 0; lCol < 8; lCol++)
			{
				if (lEx.XRem > 0)
				{
					if (((lI + 1) == lEx.XQuot) && (lCol == lEx.XRem))
						break;
				}
				lTmp = 0;

				for (lLin = 0; lLin < lEx.PE.Offset; lLin++)
				{
					if ((*(lEx.Char->Font + lEx.XQuot * (lLin + lEx.YBase)
								+ lI)) & (1 << (7 - lCol)))
						lTmp |= 1 << lLin;
				}
//				sPage[lEx.Char->PS.X + lI * 8 + lCol] &=
//												(0xFF << lEx.PE.Offset);
				// 取反
				lTmp ^= 0xFF;
//				sPage[lEx.Char->PS.X + lI * 8 + lCol] |= lTmp;
				sPage[lEx.Char->PS.X + lI * 8 + lCol] &= lTmp;
			}
		}

		UC1701_Write(lEx.PS.Index + lEx.Area.PagNum + 1, lEx.Char->PS.X,
									lEx.Char->Pixel.X);
	}// end of if ((lPagEnd > lPag) && (lOfSetEn))
}


/**
 * @brief   uc1701 显示所有，注意没有改变DRAM数值
 */
void UC1701_DisAll(void)
{
	UC1701_CS_LOW;
	UC1701_DELAY;

	// 全部显示 [0]
	UC1701_Cmd(UC1701_CMD_DC1 | BIT(0));

	UC1701_CS_HIGH;
	UC1701_DELAY;
}

/**
 * @brief   uc1701 反显当前内容
 */
void UC1701_DisRev(void)
{
	UC1701_CS_LOW;
	UC1701_DELAY;

	// 反转显示 [0]
	UC1701_Cmd(UC1701_CMD_DC0 | BIT(0));

	UC1701_CS_HIGH;
	UC1701_DELAY;
}

/**
 * @brief   uc1701 清除所有内容
 */
void UC1701_DisClr(void)
{
	/*uint8_t lI = 0;*/
	uint8_t lX1, lY1, lX2, lY2;

	UC1701_CS_LOW;
	UC1701_DELAY;

	/*for (lI = 0; lI < (UC1701_SEG_NUM); lI++)*/
		/*sPage[lI] = 0x00;*/

	/*for (lI = 0; lI < (UC1701_PAGE_NUM); lI++)*/
		/*UC1701_Write(lI, 0, UC1701_SEG_NUM);*/
//	lX1 = 0;
//	lY1 = 0;
//	lX2 = UC1701_SEG_END;
//	lY2 = UC1701_LINE_END;
//	UC1701_FillRecClr(lX1, lY1, lX2, lY2);

	S_Lcd_Area_Rectangle lRec;

	lRec.PS.X = 0;
	lRec.PS.Y = 0;
	lRec.PE.X = UC1701_SEG_END;
	lRec.PE.Y = UC1701_LINE_END;
	UC1701_FillRecClr(&lRec);

	UC1701_CS_HIGH;
	UC1701_DELAY;
}


/**
 * @brief   uc1701 软件坐标到硬件坐标的转换
 *
 * @param   lX
 */
inline void UC1701_CorCvt_X(my_lcd_t* lX)
{
	*lX += 4;
	//*lY = *lY;

	if (*lX > UC1701_SEG_END)
	{
		*lX = UC1701_SEG_END;
	}
}


/**
 * @brief   uc1701 软件坐标到硬件坐标的转换
 *
 * @param   lY
 */
inline void UC1701_CorCvt_Y(my_lcd_t* lY)
{
	if (*lY > UC1701_LINE_END)
		*lY = UC1701_LINE_END;
}

/**
 * @brief   uc1701 软件坐标到硬件坐标的转换
 *
 * @param   lpPoint
 */
inline void UC1701_CorCvt(S_Lcd_Point* lpPoint)
{
//	*lX += 4;
//	//*lY = *lY;
//
//	if (*lX > UC1701_SEG_END)
//		*lX = UC1701_SEG_END;
//
//	if (*lY > UC1701_LINE_END)
//		*lY = UC1701_LINE_END;

	UC1701_CorCvt_X(&(lpPoint->X));
	UC1701_CorCvt_Y(&(lpPoint->Y));
}

/**
 * @brief   uc1701 正常持有的显示方式
 */
void UC1701_MirUp(void)
{
	UC1701_CS_LOW;
	UC1701_DELAY;

	/*// 行扫描顺序 上->下 [3]*/
	/*UC1701_Cmd(UC1701_CMD_LC1 | BIT(3));*/
	// 行扫描顺序 下->上 [3]
	UC1701_Cmd(UC1701_CMD_LC1);
	// 列扫描顺序 右->左 [0]
	UC1701_Cmd(UC1701_CMD_LC0 | BIT(0));

	UC1701_CS_HIGH;
	UC1701_DELAY;
}

/**
 * @brief   uc1701 倒着持有的显示方式
 */
void UC1701_MirDown(void)
{
	UC1701_CS_LOW;
	UC1701_DELAY;

	/*// 行扫描顺序 下->上 [3]*/
	/*UC1701_Cmd(UC1701_CMD_LC1);*/
	// 行扫描顺序 上->下 [3]
	UC1701_Cmd(UC1701_CMD_LC1 | BIT(3));
	// 列扫描顺序 左->右 [0]
	UC1701_Cmd(UC1701_CMD_LC0);

	UC1701_CS_HIGH;
	UC1701_DELAY;
}

/**
 * @brief   uc1701 寄存器初始化
 */
static void UC1701_RegInit(void)
{
	#ifdef CONFIG_USING_UC1701_PIN_RST
	UC1701_RST_LOW;
	UC1701_DELAY_2MS;

	UC1701_RST_HIGH;
	UC1701_DELAY_6MS;
	#endif

	UC1701_CS_LOW;
	UC1701_DELAY;

	// UC1701 软件复位
	UC1701_Cmd(UC1701_CMD_SR);
	UC1701_DELAY_120MS;

	// UC1701 升压 [2:0]
	UC1701_Cmd(UC1701_CMD_PCL | BIT(2) | BIT(1) | BIT(0));
	UC1701_DELAY_6MS;

	// 粗调对比度 [2:0]
	UC1701_Cmd(UC1701_CMD_PCM | BIT(1) | BIT(0));
	// 微调对比度
	UC1701_Cmd(UC1701_CMD_PMS);
	// 微调对比度 [5:0]
	// 字灰色
//	UC1701_Cmd(UC1701_CMD_PM | BIT(4) | BIT(3) | BIT(2) | BIT(1) | BIT(0));
	// 字偏蓝，很显眼，但是底色有显示出来了。
//	UC1701_Cmd(UC1701_CMD_PM | BIT(5) | BIT(4));
	// 字显眼，底色也减少了
//	UC1701_Cmd(UC1701_CMD_PM | BIT(5) | BIT(3));// |
	// 这个感觉刚好.
	UC1701_Cmd(UC1701_CMD_PM | BIT(5) | BIT(2));// |
//	UC1701_Cmd(UC1701_CMD_PM | BIT(5) | BIT(4));// |
//						BIT(2) | BIT(1) | BIT(0));
	// 偏压
	UC1701_Cmd(UC1701_CMD_BR);
	/*// 行扫描顺序 上->下 [3]*/
	/*UC1701_Cmd(UC1701_CMD_LC1 | BIT(3));*/
	// 行扫描顺序 下->上 [3]
	UC1701_Cmd(UC1701_CMD_LC1);
	// 列扫描顺序 右->左 [0]
	UC1701_Cmd(UC1701_CMD_LC0 | BIT(0));
	// 起始行 [5:0]
	UC1701_Cmd(UC1701_CMD_SL);

	// 显示使能 [0]
	UC1701_Cmd(UC1701_CMD_DC2 | BIT(0));
	UC1701_CS_HIGH;
	UC1701_DELAY;
}

/**
 * @brief   uc1701 引脚初始化
 */
static void UC1701_PinInit(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

	// SCK Pin Init
	RCC_APB2PeriphClockCmd(UC1701_SCK_RCC, ENABLE);

	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Pin   = UC1701_SCK_PIN;

	GPIO_Init(UC1701_SCK_GPIO, &GPIO_InitStructure);
	// SCK Pin High
	UC1701_SCK_HIGH;

	// MOSI Pin Init
	RCC_APB2PeriphClockCmd(UC1701_MOSI_RCC, ENABLE);

	GPIO_InitStructure.GPIO_Pin   = UC1701_MOSI_PIN;

	GPIO_Init(UC1701_MOSI_GPIO, &GPIO_InitStructure);

	// CD Pin Init
	RCC_APB2PeriphClockCmd(UC1701_CD_RCC, ENABLE);

	GPIO_InitStructure.GPIO_Pin   = UC1701_CD_PIN;

	GPIO_Init(UC1701_CD_GPIO, &GPIO_InitStructure);

	// CS Pin Init
	RCC_APB2PeriphClockCmd(UC1701_CS_RCC, ENABLE);

	GPIO_InitStructure.GPIO_Pin   = UC1701_CS_PIN;

	GPIO_Init(UC1701_CS_GPIO, &GPIO_InitStructure);


	#ifdef CONFIG_USING_UC1701_PIN_PWR
	// PWR Pin Init
	RCC_APB2PeriphClockCmd(UC1701_PWR_RCC, ENABLE);

	GPIO_InitStructure.GPIO_Pin   = UC1701_PWR_PIN;

	GPIO_Init(UC1701_PWR_GPIO, &GPIO_InitStructure);
	// power up
	UC1701_PWR_UP;
	#endif	//#ifdef CONFIG_USING_UC1701_PIN_PWR

	// BG Pin Init
	RCC_APB2PeriphClockCmd(UC1701_BG_RCC, ENABLE);

	GPIO_InitStructure.GPIO_Pin   = UC1701_BG_PIN;

	GPIO_Init(UC1701_BG_GPIO, &GPIO_InitStructure);
	// bg on
	UC1701_BG_ON;

	#ifdef CONFIG_USING_UC1701_PIN_RST
	// RST Pin Init
	RCC_APB2PeriphClockCmd(UC1701_RST_RCC, ENABLE);

	GPIO_InitStructure.GPIO_Pin   = UC1701_RST_PIN;
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(UC1701_RST_GPIO, &GPIO_InitStructure);
	#endif	//#ifdef CONFIG_USING_UC1701_PIN_RST
}

/**
 * @brief   uc1701 初始化
 */
void UC1701_Init(void)
{
	UC1701_PinInit();
	// 为了等待硬件复位完成
//	rt_thread_delay(RT_TICK_PER_SECOND / 10);
	UC1701_RegInit();

	UC1701_DisClr();
}


/**
 * @brief   uc1701 打开背光
 */
inline void UC1701_BgOn(void)
{
	UC1701_BG_ON;
}


/**
 * @brief   uc1701 关闭背光
 */
inline void UC1701_BgOff(void)
{
	UC1701_BG_OFF;
}


/**
 * @brief   uc1701 进入休眠模式
 */
void UC1701_SleepIN(void)
{
	UC1701_CS_LOW;
	UC1701_DELAY;

	// display off
	UC1701_Cmd(UC1701_CMD_DC2);
	// all pixel on
	UC1701_Cmd(UC1701_CMD_DC1 | BIT(0));
}


/**
 * @brief   uc1701 退出休眠模式
 */
void UC1701_SleepOut(void)
{
	UC1701_CS_LOW;
	UC1701_DELAY;

	// all pixel off
	UC1701_Cmd(UC1701_CMD_DC1);
	// display on
	UC1701_Cmd(UC1701_CMD_DC2 | BIT(0));

	UC1701_BG_OFF;
}


/**
 * @brief   uc1701 断电
 */
void UC1701_PwrDown(void)
{
	#ifdef CONFIG_USING_UC1701_PIN_PWR
	UC1701_CS_LOW;
	UC1701_DELAY;

	// reset
	UC1701_Cmd(UC1701_CMD_SR);

	UC1701_CS_HIGH;
	UC1701_DELAY;

	UC1701_DELAY_2MS;

	// power off
	UC1701_PWR_DOWN;
	UC1701_BG_OFF;
	#else /* 无法控制电源的话，就让显示进入休眠，然后机器断电 */
//	UC1701_CS_LOW;
//	UC1701_DELAY;
//
//	// display off
//	UC1701_Cmd(UC1701_CMD_DC2);
//	// all pixel on
//	UC1701_Cmd(UC1701_CMD_DC1 | BIT(0));
//
//	UC1701_CS_HIGH;
////	UC1701_DELAY;
////
////	UC1701_DELAY_2MS;
////
////	// power off
////	UC1701_PWR_DOWN;
//	UC1701_BG_OFF;

	UC1701_SleepIN();
	UC1701_BgOff();

	#endif
}

