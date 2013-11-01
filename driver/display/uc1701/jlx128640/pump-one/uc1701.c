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
 * @param   lPag
 * @param   lOfSet
 */
static inline UC1701_PageGet(uint8_t lY, uint8_t *lpPag, uint8_t *lpOfSet)
{
	*lpPag = lY >> 3;
	*lpOfSet = lY & 0x07;
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
static void UC1701_Read(uint8_t lPag, uint8_t lCol, uint8_t lLen)
{
	uint8_t lI;

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
static void UC1701_Write(uint8_t lPag, uint8_t lCol, uint8_t lLen)
{
	uint8_t lI;

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
void UC1701_DrawDotSet(uint8_t lX, uint8_t lY)
{
	uint8_t lPag, lOfSet, lTemp;
	
	//lY / 8  page address
	UC1701_PageGet(lY, &lPag, &lOfSet);

	UC1701_CS_LOW;

	UC1701_CorSet(lPag, lX);

	//data read
	lTemp = UC1701_ReadByte();

	//pin mode
	lTemp |= BIT(lOfSet);

	UC1701_WriteByte(lTemp);

	UC1701_CS_HIGH;
}

/**
 * @brief   点清除
 *
 * @param   lX
 * @param   lY
 */
void UC1701_DrawDotClr(uint8_t lX, uint8_t lY)
{
	uint8_t lPag, lOfSet, lTemp;
	
	//lY / 8  page address
	UC1701_PageGet(lY, &lPag, &lOfSet);

	UC1701_CS_LOW;

	UC1701_CorSet(lPag, lX);

	//data read
	lTemp = UC1701_ReadByte();

	//pin mode
	lTemp &= ~BIT(lOfSet);

	UC1701_WriteByte(lTemp);

	UC1701_CS_HIGH;
}

/**
 * @brief   画水平线
 *
 * @param   lX1
 * @param   lY
 * @param   lX2
 */
void UC1701_DrawHorLinSet(uint8_t lX1, uint8_t lY, uint8_t lX2)
{
	uint8_t lPag, lOfSet, lLen, lI;

	UC1701_PageGet(lY, &lPag, &lOfSet);

	if (lX2 < lX1)
		SWAP(lX1, lX2);

	lLen = lX2 - lX1 + 1;

	UC1701_Read(lPag, lX1, lLen);

	for (lI = 0; lI < lLen; lI++)
		sPage[lX1 + lI] |= BIT(lOfSet);

	UC1701_Write(lPag, lX1, lLen);
}

/**
 * @brief   清除水平线
 *
 * @param   lX1
 * @param   lY
 * @param   lX2
 */
void UC1701_DrawHorLinClr(uint8_t lX1, uint8_t lY, uint8_t lX2)
{
	uint8_t lPag, lOfSet, lLen, lI;

	UC1701_PageGet(lY, &lPag, &lOfSet);

	if (lX2 < lX1)
		SWAP(lX1, lX2);

	lLen = lX2 - lX1 + 1;

	UC1701_Read(lPag, lX1, lLen);

	for (lI = 0; lI < lLen; lI++)
		sPage[lX1 + lI] &= ~BIT(lOfSet);

	UC1701_Write(lPag, lX1, lLen);
}

/**
 * @brief   画垂直线
 *
 * @param   lX1
 * @param   lY1
 * @param   lY2
 */
void UC1701_DrawVerLinSet(uint8_t lX1, uint8_t lY1, uint8_t lY2)
{
	uint8_t lPag1, lPag2, lTmp, lOfSet1, lOfSet2, lI, lPagNum;

	if (lY2 < lY1)
		SWAP(lY1, lY2);

	UC1701_PageGet(lY1, &lPag1, &lOfSet1);
	UC1701_PageGet(lY2, &lPag2, &lOfSet2);
	lPagNum = lPag2 - lPag1;

	UC1701_CS_LOW;

	UC1701_CorSet(lPag1, lX1);
	lTmp = UC1701_ReadByte();

	if (lPagNum == 0)
	{
		lTmp |= (0xFF << lOfSet1) & (~(0xFF << (lOfSet2 + 1)));

		UC1701_WriteByte(lTmp);
	}
	else
	{
		lTmp |= 0xFF << lOfSet1;

		UC1701_WriteByte(lTmp);

		
		for (lI = 0; lI < (lPagNum - 1); lI++)
		{
			UC1701_CorSet(lPag1 + lI + 1, lX1);
            UC1701_WriteByte(0xFF);
		}

		UC1701_CorSet(lPag2, lX1);

		//data read
		lTmp = UC1701_ReadByte();

		lTmp |= ~(0xFF << (lOfSet2 + 1));

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
void UC1701_DrawVerLinClr(uint8_t lX1, uint8_t lY1, uint8_t lY2)
{
	uint8_t lPag1, lPag2, lTmp, lOfSet1, lOfSet2, lI, lPagNum;

	if (lY2 < lY1)
		SWAP(lY1, lY2);

	UC1701_PageGet(lY1, &lPag1, &lOfSet1);
	UC1701_PageGet(lY2, &lPag2, &lOfSet2);
	lPagNum = lPag2 - lPag1;

	UC1701_CS_LOW;

	UC1701_CorSet(lPag1, lX1);
	lTmp = UC1701_ReadByte();

	if (lPagNum == 0)
	{
		lTmp &= ~((0xFF << lOfSet1) & (~(0xFF << (lOfSet2 + 1))));

		UC1701_WriteByte(lTmp);
	}
	else
	{
		lTmp &= ~(0xFF << lOfSet1);

		UC1701_WriteByte(lTmp);

		
		for (lI = 0; lI < (lPagNum - 1); lI++)
		{
			UC1701_CorSet(lPag1 + lI + 1, lX1);
            UC1701_WriteByte(0x00);
		}

		UC1701_CorSet(lPag2, lX1);

		//data read
		lTmp = UC1701_ReadByte();

		lTmp &= 0xFF << (lOfSet2 + 1);

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
void UC1701_DrawDiagSet(uint8_t lX, uint8_t lY, uint8_t lQuad, 
						uint8_t lLen)
{
	int8_t lXm, lYm;
	uint8_t lI;

	switch (lQuad)
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

	for (lI = 0; lI < lLen; lI++)
	{
		UC1701_DrawDotSet(lX, lY);
		lX += lXm;
		lY += lYm;
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
void UC1701_DrawDiagClr(uint8_t lX, uint8_t lY, uint8_t lQuad, 
						uint8_t lLen)
{
	int8_t lXm, lYm;
	uint8_t lI;

	switch (lQuad)
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

	for (lI = 0; lI < lLen; lI++)
	{
		UC1701_DrawDotClr(lX, lY);
		lX += lXm;
		lY += lYm;
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
void UC1701_DrawRecSet(uint8_t lX1, uint8_t lY1, uint8_t lX2, uint8_t lY2)
{
	UC1701_DrawHorLinSet(lX1, lY1, lX2);
	UC1701_DrawHorLinSet(lX1, lY2, lX2);
	UC1701_DrawVerLinSet(lX1, lY1, lY2);
	UC1701_DrawVerLinSet(lX2, lY1, lY2);
}

/**
 * @brief   清除矩形
 *
 * @param   lX1
 * @param   lY1
 * @param   lX2
 * @param   lY2
 */
void UC1701_DrawRecClr(uint8_t lX1, uint8_t lY1, uint8_t lX2, uint8_t lY2)
{
	UC1701_DrawHorLinClr(lX1, lY1, lX2);
	UC1701_DrawHorLinClr(lX1, lY2, lX2);
	UC1701_DrawVerLinClr(lX1, lY1, lY2);
	UC1701_DrawVerLinClr(lX2, lY1, lY2);
}

/**
 * @brief   填充矩形
 *
 * @param   lX1
 * @param   lY1
 * @param   lX2
 * @param   lY2
 */
void UC1701_FillRecSet(uint8_t lX1, uint8_t lY1, uint8_t lX2, uint8_t lY2)
{
	uint8_t lPag1, lPag2, lOfSet1, lOfSet2, lI, lJ, lPagNum, lColNum;

	if (lX2 < lX1)
		SWAP(lX1, lX2);

	lColNum = lX2 - lX1 + 1;

	if (lY2 < lY1)
		SWAP(lY1, lY2);

	UC1701_PageGet(lY1, &lPag1, &lOfSet1);
	UC1701_PageGet(lY2, &lPag2, &lOfSet2);

	lPagNum = lPag2 - lPag1;

	if (lPagNum == 0)
	{
		UC1701_Read(lPag1, lX1, lColNum);
		for (lI = 0; lI < lColNum; lI++)
		{
			sPage[lX1 + lI] |= ((0xFF << lOfSet1) 
							& (~(0xFF << (lOfSet2 + 1))));
		}
		UC1701_Write(lPag1, lX1, lColNum);
	}
	else
	{
		UC1701_Read(lPag1, lX1, lColNum);
		for (lI = 0; lI < lColNum; lI++)
			sPage[lX1 + lI] |= 0xFF << lOfSet1;

		UC1701_Write(lPag1, lX1, lColNum);

		for (lI = 0; lI < (lPagNum - 1); lI++)
		{
			UC1701_Read(lPag1 + lI + 1, lX1, lColNum);
			for (lJ = 0; lJ < lColNum; lJ++)
			{
				sPage[lX1 + lJ] = 0xFF;
			}
			UC1701_Write(lPag1 + lI + 1, lX1, lColNum);
		}

		UC1701_Read(lPag2, lX1, lColNum);
		for (lI = 0; lI < lColNum; lI++)
			sPage[lX1 + lI] |= ~(0xFF << (lOfSet2 + 1));

		UC1701_Write(lPag2, lX1, lColNum);
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
void UC1701_FillRecClr(uint8_t lX1, uint8_t lY1, uint8_t lX2, uint8_t lY2)
{
	uint8_t lPag1, lPag2, lOfSet1, lOfSet2, lI, lJ, lPagNum, lColNum;

	if (lX2 < lX1)
		SWAP(lX1, lX2);

	lColNum = lX2 - lX1 + 1;

	if (lY2 < lY1)
		SWAP(lY1, lY2);

	UC1701_PageGet(lY1, &lPag1, &lOfSet1);
	UC1701_PageGet(lY2, &lPag2, &lOfSet2);

	lPagNum = lPag2 - lPag1;

	if (lPagNum == 0)
	{
		UC1701_Read(lPag1, lX1, lColNum);
		for (lI = 0; lI < lColNum; lI++)
		{
			sPage[lX1 + lI] &= ~((0xFF << lOfSet1) 
							& (~(0xFF << (lOfSet2 + 1))));
		}
		UC1701_Write(lPag1, lX1, lColNum);
	}
	else
	{
		UC1701_Read(lPag1, lX1, lColNum);
		for (lI = 0; lI < lColNum; lI++)
			sPage[lX1 + lI] &= ~(0xFF << lOfSet1);

		UC1701_Write(lPag1, lX1, lColNum);

		for (lI = 0; lI < (lPagNum - 1); lI++)
		{
			UC1701_Read(lPag1 + lI + 1, lX1, lColNum);
			for (lJ = 0; lJ < lColNum; lJ++)
			{
				sPage[lX1 + lJ] = 0x00;
			}
			UC1701_Write(lPag1 + lI + 1, lX1, lColNum);
		}

		UC1701_Read(lPag2, lX1, lColNum);
		for (lI = 0; lI < lColNum; lI++)
			sPage[lX1 + lI] &= 0xFF << (lOfSet2 + 1);

		UC1701_Write(lPag2, lX1, lColNum);
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
void UC1701_RevRec(uint8_t lX1, uint8_t lY1, uint8_t lX2, uint8_t lY2)
{
	uint8_t lPag1, lPag2, lOfSet1, lOfSet2, lI, lJ, lPagNum, lColNum;

	if (lX2 < lX1)
		SWAP(lX1, lX2);

	lColNum = lX2 - lX1 + 1;

	if (lY2 < lY1)
		SWAP(lY1, lY2);

	UC1701_PageGet(lY1, &lPag1, &lOfSet1);
	UC1701_PageGet(lY2, &lPag2, &lOfSet2);
	lPagNum = lPag2 - lPag1;

	if (lPagNum == 0)
	{
		UC1701_Read(lPag1, lX1, lColNum);
		for (lI = 0; lI < lColNum; lI++)
		{
			sPage[lX1 + lI] ^= (0xFF << lOfSet1) 
							& (~(0xFF << (lOfSet2 + 1)));
		}
		UC1701_Write(lPag1, lX1, lColNum);
	}
	else
	{
		UC1701_Read(lPag1, lX1, lColNum);
		for (lI = 0; lI < lColNum; lI++)
		{
			sPage[lX1 + lI] ^= 0xFF << lOfSet1;
		}
		UC1701_Write(lPag1, lX1, lColNum);

		for (lI = 0; lI < (lPagNum - 1); lI++)
		{
			UC1701_Read(lPag1 + lI + 1, lX1, lColNum);
			for (lJ = 0; lJ < lColNum; lJ++)
			{
				sPage[lX1 + lJ] ^= 0xFF;
			}
			UC1701_Write(lPag1 + lI + 1, lX1, lColNum);
		}

		UC1701_Read(lPag2, lX1, lColNum);
		for (lI = 0; lI < lColNum; lI++)
		{
			sPage[lX1 + lI] ^= ~(0xFF << (lOfSet2 + 1));
		}
		UC1701_Write(lPag2, lX1, lColNum);
	}
}

/**
 * @brief   普通画圆法
 *
 * @param   lX
 * @param   lY
 * @param   lRad
 */
void UC1701_DrawCycSet(uint8_t lX, uint8_t lY, uint8_t lRad)
{
	int16_t lDi;
	int8_t lA, lB;

	lA = 0;
	lB = lRad;

	//flag of next point
	lDi = 3 - (lRad << 1);				
   	
	while (lA <= lB)
	{
		UC1701_DrawDotSet(lX - lB, lY - lA);
		UC1701_DrawDotSet(lX + lB, lY - lA);
		UC1701_DrawDotSet(lX - lB, lY + lA);
		UC1701_DrawDotSet(lX + lB, lY + lA);
		UC1701_DrawDotSet(lX - lA, lY - lB);
		UC1701_DrawDotSet(lX + lA, lY - lB);
		UC1701_DrawDotSet(lX - lA, lY + lB);
		UC1701_DrawDotSet(lX + lA, lY + lB);

		//draw cycle by Bresenham arithmetic
		if (lDi < 0)
			lDi += lA * 4 + 6;
		else
		{
			lDi += 10 + (lA - lB) * 4;
			lB--;
		}
		lA++;
		UC1701_DrawDotSet(lX + lA, lY + lB);
	}	
}

/**
 * @brief   普通清除圆形法
 *
 * @param   lX
 * @param   lY
 * @param   lRad
 */
void UC1701_DrawCycClr(uint8_t lX, uint8_t lY, uint8_t lRad)
{
	int16_t lDi;
	int8_t lA, lB;

	lA = 0;
	lB = lRad;

	//flag of next point
	lDi = 3 - (lRad << 1);				
   	
	while (lA <= lB)
	{
		UC1701_DrawDotClr(lX - lB, lY - lA);
		UC1701_DrawDotClr(lX + lB, lY - lA);
		UC1701_DrawDotClr(lX - lB, lY + lA);
		UC1701_DrawDotClr(lX + lB, lY + lA);
		UC1701_DrawDotClr(lX - lA, lY - lB);
		UC1701_DrawDotClr(lX + lA, lY - lB);
		UC1701_DrawDotClr(lX - lA, lY + lB);
		UC1701_DrawDotClr(lX + lA, lY + lB);

		//draw cycle by Bresenham arithmetic
		if (lDi < 0)
			lDi += lA * 4 + 6;
		else
		{
			lDi += 10 + (lA - lB) * 4;
			lB--;
		}
		lA++;
		UC1701_DrawDotClr(lX + lA, lY + lB);
	}	
}

/**
 * @brief   快速画圆法
 *
 * @param   lXc
 * @param   lYc
 * @param   lRad
 */
void UC1701_DrawCycFastSet(uint8_t lXc, uint8_t lYc, uint8_t lRad)
{
	int8_t lX, lY;
	int16_t lDi;

	lX = 0;
	lY = lRad;
	lDi = -(lRad / 2);

	/*if (lRad % 2 == 0)*/
	if (lRad & 0x01 == 0)
	{
		while (lX < lY)
		{
			UC1701_DrawDotSet(lXc - lY, lYc - lX);
			UC1701_DrawDotSet(lXc + lY, lYc - lX);
			UC1701_DrawDotSet(lXc - lY, lYc + lX);
			UC1701_DrawDotSet(lXc + lY, lYc + lX);
			UC1701_DrawDotSet(lXc - lX, lYc - lY);
			UC1701_DrawDotSet(lXc + lX, lYc - lY);
			UC1701_DrawDotSet(lXc - lX, lYc + lY);
			UC1701_DrawDotSet(lXc + lX, lYc + lY);

			lX++;
			if (lDi < 0)
				lDi += lX;
			else
			{
				lY--;
				lDi += lX - lY;
			}
			UC1701_DrawDotSet(lXc + lX, lYc + lY);
		}
	}
	else
	{
		while (lX < lY)
		{
			UC1701_DrawDotSet(lXc - lY, lYc - lX);
			UC1701_DrawDotSet(lXc + lY, lYc - lX);
			UC1701_DrawDotSet(lXc - lY, lYc + lX);
			UC1701_DrawDotSet(lXc + lY, lYc + lX);
			UC1701_DrawDotSet(lXc - lX, lYc - lY);
			UC1701_DrawDotSet(lXc + lX, lYc - lY);
			UC1701_DrawDotSet(lXc - lX, lYc + lY);
			UC1701_DrawDotSet(lXc + lX, lYc + lY);

			lX++;
			if (lDi < 0)
				lDi += lX + 1;
			else
			{
				lY--;
				lDi += lX - lY + 1;
			}
			UC1701_DrawDotSet(lXc + lX, lYc + lY);
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
void UC1701_DrawCycFastClr(uint8_t lXc, uint8_t lYc, uint8_t lRad)
{
	int8_t lX, lY;
	int16_t lDi;

	lX = 0;
	lY = lRad;
	lDi = -(lRad / 2);

	/*if (lRad % 2 == 0)*/
	if (lRad & 0x01 == 0)
	{
		while (lX < lY)
		{
			UC1701_DrawDotClr(lXc - lY, lYc - lX);
			UC1701_DrawDotClr(lXc + lY, lYc - lX);
			UC1701_DrawDotClr(lXc - lY, lYc + lX);
			UC1701_DrawDotClr(lXc + lY, lYc + lX);
			UC1701_DrawDotClr(lXc - lX, lYc - lY);
			UC1701_DrawDotClr(lXc + lX, lYc - lY);
			UC1701_DrawDotClr(lXc - lX, lYc + lY);
			UC1701_DrawDotClr(lXc + lX, lYc + lY);

			lX++;
			if (lDi < 0)
				lDi += lX;
			else
			{
				lY--;
				lDi += lX - lY;
			}
			UC1701_DrawDotClr(lXc + lX, lYc + lY);
		}
	}
	else
	{
		while (lX < lY)
		{
			UC1701_DrawDotClr(lXc - lY, lYc - lX);
			UC1701_DrawDotClr(lXc + lY, lYc - lX);
			UC1701_DrawDotClr(lXc - lY, lYc + lX);
			UC1701_DrawDotClr(lXc + lY, lYc + lX);
			UC1701_DrawDotClr(lXc - lX, lYc - lY);
			UC1701_DrawDotClr(lXc + lX, lYc - lY);
			UC1701_DrawDotClr(lXc - lX, lYc + lY);
			UC1701_DrawDotClr(lXc + lX, lYc + lY);

			lX++;
			if (lDi < 0)
				lDi += lX + 1;
			else
			{
				lY--;
				lDi += lX - lY + 1;
			}
			UC1701_DrawDotClr(lXc + lX, lYc + lY);
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
void UC1701_DrawRecFramSet(uint8_t lX1, uint8_t lY1, uint8_t lX2, 
							uint8_t lY2)
{
	if (lX1 > lX2)
		SWAP(lX1, lX2);

	if (lY1 > lY2)
		SWAP(lY1, lY2);

	UC1701_DrawHorLinSet(lX1, lY1, lX2 - 3);
	UC1701_DrawVerLinSet(lX1, lY1, lY2 - 3);
	UC1701_FillRecSet(lX1 + 3, lY2 - 3, lX2, lY2);
	UC1701_FillRecSet(lX2 - 3, lY1 + 3, lX2, lY2 - 3);
	UC1701_DrawDotSet(lX1 + 1, lY2 - 3);
	UC1701_DrawDotSet(lX1 + 2, lY2 - 3);
	UC1701_DrawDotSet(lX2 - 3, lY1 + 1);
	UC1701_DrawDotSet(lX2 - 3, lY1 + 2);

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
void UC1701_DrawRecFramClr(uint8_t lX1, uint8_t lY1, uint8_t lX2, 
							uint8_t lY2)
{
	if (lX1 > lX2)
		SWAP(lX1, lX2);

	if (lY1 > lY2)
		SWAP(lY1, lY2);

	UC1701_DrawHorLinClr(lX1, lY1, lX2 - 3);
	UC1701_DrawVerLinClr(lX1, lY1, lY2 - 3);
	UC1701_FillRecClr(lX1 + 3, lY2 - 3, lX2, lY2);
	UC1701_FillRecClr(lX2 - 3, lY1 + 3, lX2, lY2 - 3);
	UC1701_DrawDotClr(lX1 + 1, lY2 - 3);
	UC1701_DrawDotClr(lX1 + 2, lY2 - 3);
	UC1701_DrawDotClr(lX2 - 3, lY1 + 1);
	UC1701_DrawDotClr(lX2 - 3, lY1 + 2);
}

/**
 * @brief   画折边矩形
 *
 * @param   lX1
 * @param   lY1
 * @param   lX2
 * @param   lY2
 */
void UC1701_DrawRecDiagSet(uint8_t lX1, uint8_t lY1, uint8_t lX2, 
							uint8_t lY2)
{
	if (lX1 > lX2)
		SWAP(lX1, lX2);

	if (lY1 > lY2)
		SWAP(lY1, lY2);

	UC1701_DrawHorLinSet(lX1 + 6, lY1, lX2 - 6);
	UC1701_DrawHorLinSet(lX1 + 6, lY2, lX2 - 6);
	UC1701_DrawVerLinSet(lX1, lY1 + 6, lY2 - 6);
	UC1701_DrawVerLinSet(lX2, lY1 + 6, lY2 - 6);
	UC1701_DrawDiagSet(lX1, lY1 + 6, 4, 6);
	UC1701_DrawDiagSet(lX2 - 6, lY1, 1, 6);
	UC1701_DrawDiagSet(lX1, lY2 - 6, 1, 6);
	UC1701_DrawDiagSet(lX2 - 6, lY2, 4, 6);
}

/**
 * @brief   清除折边矩形
 *
 * @param   lX1
 * @param   lY1
 * @param   lX2
 * @param   lY2
 */
void UC1701_DrawRecDiagClr(uint8_t lX1, uint8_t lY1, uint8_t lX2, 
							uint8_t lY2)
{
	if (lX1 > lX2)
		SWAP(lX1, lX2);

	if (lY1 > lY2)
		SWAP(lY1, lY2);

	UC1701_DrawHorLinClr(lX1 + 6, lY1, lX2 - 6);
	UC1701_DrawHorLinClr(lX1 + 6, lY2, lX2 - 6);
	UC1701_DrawVerLinClr(lX1, lY1 + 6, lY2 - 6);
	UC1701_DrawVerLinClr(lX2, lY1 + 6, lY2 - 6);
	UC1701_DrawDiagClr(lX1, lY1 + 6, 4, 6);
	UC1701_DrawDiagClr(lX2 - 6, lY1, 1, 6);
	UC1701_DrawDiagClr(lX1, lY2 - 6, 1, 6);
	UC1701_DrawDiagClr(lX2 - 6, lY2, 4, 6);
}

/**
 * @brief   画折边矩形带阴影
 *
 * @param   lX1
 * @param   lY1
 * @param   lX2
 * @param   lY2
 */
void UC1701_DrawRecDiagFramSet(uint8_t lX1, uint8_t lY1, uint8_t lX2, 
								uint8_t lY2)
{
	if (lX1 > lX2)
		SWAP(lX1, lX2);

	if (lY1 > lY2)
		SWAP(lY1, lY2);

	UC1701_DrawHorLinSet(lX1 + 6, lY1, lX2 - 9);
	UC1701_DrawVerLinSet(lX1, lY1 + 6, lY2 - 9);
	UC1701_DrawDiagSet(lX1, lY1 + 6, 4, 6);
	UC1701_DrawDiagSet(lX2 - 9, lY1, 1, 9);
	UC1701_DrawDiagSet(lX1, lY2 - 9, 1, 9);
	UC1701_DrawDiagSet(lX2 - 9, lY2 - 3, 4, 6);
	UC1701_DrawDiagSet(lX2 - 6, lY2, 4, 6);
	UC1701_FillRecSet(lX1 + 9, lY2 - 3, lX2 - 6, lY2);
	UC1701_FillRecSet(lX2 - 3, lY1 + 9, lX2, lY2 - 6);
	UC1701_DrawDotSet(lX1 + 7, lY2 - 3);
	UC1701_DrawDotSet(lX1 + 8, lY2 - 3);
	UC1701_DrawDotSet(lX1 + 8, lY2 - 2);
	UC1701_FillRecSet(lX2 - 6, lY2 - 6, lX2 - 3, lY2 - 3);
	UC1701_DrawDotSet(lX2 - 7, lY2 - 4);
	UC1701_DrawDotSet(lX2 - 4, lY2 - 7);
	UC1701_DrawDotSet(lX2 - 5, lY2 - 2);
	UC1701_DrawDotSet(lX2 - 2, lY2 - 5);
	UC1701_DrawDotSet(lX2 - 3, lY1 + 8);
	UC1701_DrawDotSet(lX2 - 3, lY1 + 7);
	UC1701_DrawDotSet(lX2 - 2, lY1 + 8);
}

/**
 * @brief   清除折边矩形阴影
 *
 * @param   lX1
 * @param   lY1
 * @param   lX2
 * @param   lY2
 */
void UC1701_DrawRecDiagFramClr(uint8_t lX1, uint8_t lY1, uint8_t lX2, 
								uint8_t lY2)
{
	if (lX1 > lX2)
		SWAP(lX1, lX2);

	if (lY1 > lY2)
		SWAP(lY1, lY2);

	UC1701_DrawHorLinClr(lX1 + 6, lY1, lX2 - 9);
	UC1701_DrawVerLinClr(lX1, lY1 + 6, lY2 - 9);
	UC1701_DrawDiagClr(lX1, lY1 + 6, 4, 6);
	UC1701_DrawDiagClr(lX2 - 9, lY1, 1, 9);
	UC1701_DrawDiagClr(lX1, lY2 - 9, 1, 9);
	UC1701_DrawDiagClr(lX2 - 9, lY2 - 3, 4, 6);
	UC1701_DrawDiagClr(lX2 - 6, lY2, 4, 6);
	UC1701_FillRecClr(lX1 + 9, lY2 - 3, lX2 - 6, lY2);
	UC1701_FillRecClr(lX2 - 3, lY1 + 9, lX2, lY2 - 6);
	UC1701_DrawDotClr(lX1 + 7, lY2 - 3);
	UC1701_DrawDotClr(lX1 + 8, lY2 - 3);
	UC1701_DrawDotClr(lX1 + 8, lY2 - 2);
	UC1701_FillRecClr(lX2 - 6, lY2 - 6, lX2 - 3, lY2 - 3);
	UC1701_DrawDotClr(lX2 - 7, lY2 - 4);
	UC1701_DrawDotClr(lX2 - 4, lY2 - 7);
	UC1701_DrawDotClr(lX2 - 5, lY2 - 2);
	UC1701_DrawDotClr(lX2 - 2, lY2 - 5);
	UC1701_DrawDotClr(lX2 - 3, lY1 + 8);
	UC1701_DrawDotClr(lX2 - 3, lY1 + 7);
	UC1701_DrawDotClr(lX2 - 2, lY1 + 8);
}

/**
 * @brief   显示字符
 *
 * @param   lX
 * @param   lY
 * @param   lpBuffer
 * @param   lXSize
 * @param   lYSize
 */
void UC1701_CharSet(uint8_t lX, uint8_t lY, const uint8_t *lpBuffer, 
					uint8_t lXSize, uint8_t lYSize)
{
	uint8_t lOfSet, lOfSetEn, lPag, lPagEnd, lI, lJ, lPagNum;
	uint8_t lXQuot, lXRem, lCol, lLin, lYBase;

	lPagNum = 0;

	UC1701_PageGet(lY, &lPag, &lOfSet);
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
	UC1701_PageGet((lY + lYSize), &lPagEnd, &lOfSetEn);
	//lPagNum = (lYSize >> 3) - 1;
	// be care if lYSize < 8
	if (lPagEnd > lPag)
		lPagNum = lPagEnd - lPag - 1;

	// 横向取模，所以涉及到字节存储数据
	// 一行占有几个字节
	lXRem = lXSize & 0x07;
	lXQuot = lXSize >> 3;
	if (lXRem)
		lXQuot += 1;

	// 用来作为一个字库在显示的时候的Y轴的偏移量
	lYBase = 0;

	uint8_t lTmp;

	if (lOfSet)
	{
		if (lPagEnd > lPag)
		{
			UC1701_Read(lPag, lX, lXSize);

			for (lI = 0; lI < lXQuot; lI++)
			{
				for (lCol = 0; lCol < 8; lCol++)
				{
					if (lXRem > 0)
					{
						if (((lI + 1) == lXQuot) && (lCol == lXRem))
							break;
					}
					lTmp = 0;
					for (lLin = lOfSet; lLin < 8; lLin++)
					{
						if ((*(lpBuffer + lXQuot * (lLin - lOfSet) + lI)) 
								& (1 << (7 - lCol)))
							lTmp |= 1 << lLin;
					}
					sPage[lX + lI * 8 + lCol] &= ~(0xFF << lOfSet);
					sPage[lX + lI * 8 + lCol] |= lTmp;
				}
			}

			UC1701_Write(lPag, lX, lXSize);
		}// end of if (lPagEnd > lPag)
		else
		{
			UC1701_Read(lPag, lX, lXSize);

			for (lI = 0; lI < lXQuot; lI++)
			{
				for (lCol = 0; lCol < 8; lCol++)
				{
					if (lXRem > 0)
					{
						if (((lI + 1) == lXQuot) && (lCol == lXRem))
							break;
					}
					lTmp = 0;
					for (lLin = lOfSet; lLin < lOfSetEn; lLin++)
					{
						if ((*(lpBuffer + lXQuot * (lLin - lOfSet) + lI)) 
								& (1 << (7 - lCol)))
							lTmp |= 1 << lLin;
					}
					sPage[lX + lI * 8 + lCol] &= (~(0xFF << lOfSet))
												| (0xFF << lOfSetEn);
					sPage[lX + lI * 8 + lCol] |= lTmp;
				}
			}

			UC1701_Write(lPag, lX, lXSize);
		}// end of else of if (lPagEnd > lPag)
		lYBase = 8 - lOfSet;
	}// end of if (lOfSet)
	else
	{
		if (lPagEnd > lPag)
		{
			for (lI = 0; lI < lXQuot; lI++)
			{
				for (lCol = 0; lCol < 8; lCol++)
				{
					if (lXRem > 0)
					{
						if (((lI + 1) == lXQuot) && (lCol == lXRem))
							break;
					}
					lTmp = 0;
					for (lLin = 0; lLin < 8; lLin++)
					{
						if ((*(lpBuffer + lXQuot * lLin + lI)) 
								& (1 << (7 - lCol)))
							lTmp |= 1 << lLin;
					}
					sPage[lX + lI * 8 + lCol] = lTmp;
				}
			}

			UC1701_Write(lPag, lX, lXSize);
		}// end of if (lPagEnd > lPag)
		else 
		{
			UC1701_Read(lPag, lX, lXSize);

			for (lI = 0; lI < lXQuot; lI++)
			{
				for (lCol = 0; lCol < 8; lCol++)
				{
					if (lXRem > 0)
					{
						if (((lI + 1) == lXQuot) && (lCol == lXRem))
							break;
					}
					lTmp = 0;
					for (lLin = 0; lLin < lOfSetEn; lLin++)
					{
						if ((*(lpBuffer + lXQuot * lLin + lI)) 
								& (1 << (7 - lCol)))
							lTmp |= 1 << lLin;
					}
					sPage[lX + lI * 8 + lCol] &= 0xFF << lOfSetEn;
					sPage[lX + lI * 8 + lCol] |= lTmp;
				}
			}

			UC1701_Write(lPag, lX, lXSize);
		}// end of else of if (lPagEnd > lPag)
		lYBase = 8;
	}// end of else of if (lOfSet)

	if (lPagNum)
	{
		for (lJ = 0; lJ < lPagNum; lJ++)
		{
			for (lI = 0; lI < lXQuot; lI++)
			{
				for (lCol = 0; lCol < 8; lCol++)
				{
					if (lXRem > 0)
					{
						if (((lI + 1) == lXQuot) && (lCol == lXRem))
							break;
					}
					lTmp = 0;
					for (lLin = 0; lLin < 8; lLin++)
					{
						if ((*(lpBuffer + lXQuot * (lLin + lYBase) + lI)) 
							& (1 << (7 - lCol)))
							lTmp |= 1 << lLin;
					}
					sPage[lX + lI * 8 + lCol] = lTmp;
				}
			}
			lYBase += 8;

			UC1701_Write((lPag + lJ + 1), lX, lXSize);
		}
	}// end of if (lPagNum)

	if ((lPagEnd > lPag) && (lOfSetEn))
	{
		UC1701_Read((lPag + lPagNum + 1), lX, lXSize);

		for (lI = 0; lI < lXQuot; lI++)
		{
			for (lCol = 0; lCol < 8; lCol++)
			{
				if (lXRem > 0)
				{
					if (((lI + 1) == lXQuot) && (lCol == lXRem))
						break;
				}
				lTmp = 0;
				for (lLin = 0; lLin < lOfSetEn; lLin++)
				{
					if ((*(lpBuffer + lXQuot * (lLin +lYBase) + lI)) 
							& (1 << (7 - lCol)))
						lTmp |= 1 << lLin;
				}
				sPage[lX + lI * 8 + lCol] &= 0xFF << lOfSetEn;
				sPage[lX + lI * 8 + lCol] |= lTmp;
			}
		}

		UC1701_Write((lPag + lPagNum + 1), lX, lXSize);
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
void UC1701_CharClr(uint8_t lX, uint8_t lY, const uint8_t *lpBuffer, 
					uint8_t lXSize, uint8_t lYSize)
{
	uint8_t lOfSet, lOfSetEn, lPag, lPagEnd, lI, lJ, lPagNum;

	lPagNum = 0;

	UC1701_PageGet(lY, &lPag, &lOfSet);
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
	UC1701_PageGet((lY + lYSize), &lPagEnd, &lOfSetEn);
	//lPagNum = (lYSize >> 3) - 1;
	// be care if lYSize < 8
	if (lPagEnd > lPag)
		lPagNum = lPagEnd - lPag - 1;

	if (lOfSet)
	{
		if (lPagEnd > lPag)
		{
			UC1701_Read(lPag, lX, lXSize);

			for (lI = 0; lI < lXSize; lI++)
			{
				sPage[lX + lI] = (sPage[lX + lI] & (~(0xFF << lOfSet)))
						| (((*(lpBuffer + lI + lPagNum * lXSize)) 
						^ UC1701_CHARACTER_DOT_CLEAR) << lOfSet);
			}

			UC1701_Write(lPag, lX, lXSize);
		}// end of if (lPagEnd > lPag)
		else
		{
			UC1701_Read(lPag, lX, lXSize);

			for (lI = 0; lI < lXSize; lI++)
			{
				sPage[lX + lI] = (sPage[lX + lI] & ((~(0xFF << lOfSet))
						| (0xFF << lOfSetEn)))
						| (((*(lpBuffer + lI + lPagNum * lXSize)) 
						^ UC1701_CHARACTER_DOT_CLEAR) << lOfSet);
			}

			UC1701_Write(lPag, lX, lXSize);
		}// end of else of if (lPagEnd > lPag)
	}// end of if (lOfSet)
	else
	{
		if (lPagEnd > lPag)
		{
			for (lI = 0; lI < lXSize; lI++)
			{
				sPage[lX + lI] = (*(lpBuffer + lI + lPagNum * lXSize)) 
						^ UC1701_CHARACTER_DOT_CLEAR;
			}

			UC1701_Write(lPag, lX, lXSize);
		}// end of if (lPagEnd > lPag)
		else 
		{
			UC1701_Read(lPag, lX, lXSize);

			for (lI = 0; lI < lXSize; lI++)
			{
				sPage[lX + lI] = (sPage[lX + lI] & (0xFF << lOfSetEn))
						| ((*(lpBuffer + lI + lPagNum * lXSize)) 
						^ UC1701_CHARACTER_DOT_CLEAR);
			}

			UC1701_Write(lPag, lX, lXSize);
		}// end of else of if (lPagEnd > lPag)
	}// end of else of if (lOfSet)

	if (lPagNum)
	{
		for (lJ = 0; lJ < lPagNum; lJ++)
		{
			for (lI = 0; lI < lXSize; lI++)
			{
				sPage[lX + lI] = (((*(lpBuffer + lI + (lPagNum - lJ) 
						* lXSize)) ^ UC1701_CHARACTER_DOT_CLEAR) 
						>> (8 - lOfSet)) & (~(0xFF << lOfSet));
				sPage[lX + lI] |= ((*(lpBuffer + lI + (lPagNum - lJ - 1) 
						* lXSize)) ^ UC1701_CHARACTER_DOT_CLEAR) << lOfSet;
			}
			UC1701_Write((lPag + lJ + 1), lX, lXSize);
		}
	}// end of if (lPagNum)

	if ((lPagEnd > lPag) && (lOfSetEn))
	{
		UC1701_Read((lPag + lPagNum + 1), lX, lXSize);

		for (lI = 0; lI < lXSize; lI++)
		{
			sPage[lX + lI] = (sPage[lX + lI] & (0xFF << lOfSetEn))
					| ((((*(lpBuffer + lI)) ^ UC1701_CHARACTER_DOT_CLEAR) 
					>> (8 - lOfSet)) & (~(0xFF << lOfSetEn)));
		}

		UC1701_Write((lPag + lPagNum + 1), lX, lXSize);
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
	lX1 = 0;
	lY1 = 0;
	lX2 = UC1701_SEG_END;
	lY2 = UC1701_LINE_END;
	UC1701_FillRecClr(lX1, lY1, lX2, lY2);

	UC1701_CS_HIGH;
	UC1701_DELAY;
}

/**
 * @brief   uc1701 软件坐标到硬件坐标的转换
 *
 * @param   lX
 * @param   lY
 */
void UC1701_CorCvt(uint8_t *lX, uint8_t *lY)
{
	*lX += 4;
	*lY = *lY;

	if (*lX > UC1701_SEG_END)
		*lX = UC1701_SEG_END;

	if (*lY > UC1701_LINE_END)
		*lY = UC1701_LINE_END;
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
	#ifdef CONFIG_UC1701_PIN_RST
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
	UC1701_Cmd(UC1701_CMD_PM | BIT(4) | BIT(3) | BIT(2) | BIT(1) | BIT(0));
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

	#ifdef CONFIG_UC1701_PIN_RST
	// RST Pin Init
	RCC_APB2PeriphClockCmd(UC1701_RST_RCC, ENABLE);

	GPIO_InitStructure.GPIO_Pin   = UC1701_RST_PIN;

	GPIO_Init(UC1701_RST_GPIO, &GPIO_InitStructure);
	#endif	//#ifdef CONFIG_UC1701_PIN_RST

	#ifdef CONFIG_UC1701_PIN_PWR
	// PWR Pin Init
	RCC_APB2PeriphClockCmd(UC1701_PWR_RCC, ENABLE);

	GPIO_InitStructure.GPIO_Pin   = UC1701_PWR_PIN;

	GPIO_Init(UC1701_PWR_GPIO, &GPIO_InitStructure);
	// power up
	UC1701_PWR_UP;
	#endif	//#ifdef CONFIG_UC1701_PIN_PWR

	// BG Pin Init
	RCC_APB2PeriphClockCmd(UC1701_BG_RCC, ENABLE);

	GPIO_InitStructure.GPIO_Pin   = UC1701_BG_PIN;

	GPIO_Init(UC1701_BG_GPIO, &GPIO_InitStructure);
	// bg on
	UC1701_BG_ON;
}

/**
 * @brief   uc1701 初始化
 */
void UC1701_Init(void)
{
	UC1701_PinInit();
	// 为了等待硬件复位完成
	rt_thread_delay(RT_TICK_PER_SECOND / 10);
	UC1701_RegInit();

	UC1701_DisClr();
}

/**
 * @brief   uc1701 断电
 */
void UC1701_PwrDown(void)
{
	#ifdef CONFIG_UC1701_PIN_PWR
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

	#endif
}
