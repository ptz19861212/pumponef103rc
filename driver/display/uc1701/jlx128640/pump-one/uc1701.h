/**
 * @file    uc1701.h
 * @brief   UC1701驱动
 * @author  ptz
 * @email   ptz19861212@163.com
 * @version 0.0.1
 * @date    2013-08-08 14:22:23 星期四 
 * @history (1).2013-08-08 14:22:23 星期四 create
 */
/* Copyright (C)
 * 
 * My own license
 * All right reserved
 * 
 */

#ifndef __UC1701_H__
#define __UC1701_H__

#include <stdint.h>

/**
 * @brief    画点
 *
 * @param   lX
 * @param   lY
 */
void UC1701_DrawDotSet(uint8_t lX, uint8_t lY);

/**
 * @brief   点清除
 *
 * @param   lX
 * @param   lY
 */
void UC1701_DrawDotClr(uint8_t lX, uint8_t lY);

/**
 * @brief   画水平线
 *
 * @param   lX1
 * @param   lY
 * @param   lX2
 */
void UC1701_DrawHorLinSet(uint8_t lX1, uint8_t lY, uint8_t lX2);

/**
 * @brief   清除水平线
 *
 * @param   lX1
 * @param   lY
 * @param   lX2
 */
void UC1701_DrawHorLinClr(uint8_t lX1, uint8_t lY, uint8_t lX2);

/**
 * @brief   画垂直线
 *
 * @param   lX1
 * @param   lY1
 * @param   lY2
 */
void UC1701_DrawVerLinSet(uint8_t lX1, uint8_t lY1, uint8_t lY2);

/**
 * @brief   清除垂直线
 *
 * @param   lX1
 * @param   lY1
 * @param   lY2
 */
void UC1701_DrawVerLinClr(uint8_t lX1, uint8_t lY1, uint8_t lY2);

/**
 * @brief   画45度斜线
 *
 * @param   lX
 * @param   lY
 * @param   lQuad 第几象限
 * @param   lLen
 */
void UC1701_DrawDiagSet(uint8_t lX, uint8_t lY, uint8_t lQuad, 
						uint8_t lLen);

/**
 * @brief   清除45度线
 *
 * @param   lX
 * @param   lY
 * @param   lQuad
 * @param   lLen
 */
void UC1701_DrawDiagClr(uint8_t lX, uint8_t lY, uint8_t lQuad, 
						uint8_t lLen);

/**
 * @brief   画矩形
 *
 * @param   lX1
 * @param   lY1
 * @param   lX2
 * @param   lY2
 */
void UC1701_DrawRecSet(uint8_t lX1, uint8_t lY1, uint8_t lX2, uint8_t lY2);

/**
 * @brief   清除矩形
 *
 * @param   lX1
 * @param   lY1
 * @param   lX2
 * @param   lY2
 */
void UC1701_DrawRecClr(uint8_t lX1, uint8_t lY1, uint8_t lX2, uint8_t lY2);

/**
 * @brief   填充矩形
 *
 * @param   lX1
 * @param   lY1
 * @param   lX2
 * @param   lY2
 */
void UC1701_FillRecSet(uint8_t lX1, uint8_t lY1, uint8_t lX2, uint8_t lY2);

/**
 * @brief   清除矩形
 *
 * @param   lX1
 * @param   lY1
 * @param   lX2
 * @param   lY2
 */
void UC1701_FillRecClr(uint8_t lX1, uint8_t lY1, uint8_t lX2, uint8_t lY2);

/**
 * @brief   反转矩形
 *
 * @param   lX1
 * @param   lY1
 * @param   lX2
 * @param   lY2
 */
void UC1701_RevRec(uint8_t lX1, uint8_t lY1, uint8_t lX2, uint8_t lY2);

/**
 * @brief   普通画圆法
 *
 * @param   lX
 * @param   lY
 * @param   lRad
 */
void UC1701_DrawCycSet(uint8_t lX, uint8_t lY, uint8_t lRad);

/**
 * @brief   普通清除圆形法
 *
 * @param   lX
 * @param   lY
 * @param   lRad
 */
void UC1701_DrawCycClr(uint8_t lX, uint8_t lY, uint8_t lRad);

/**
 * @brief   快速画圆法
 *
 * @param   lXc
 * @param   lYc
 * @param   lRad
 */
void UC1701_DrawCycFastSet(uint8_t lXc, uint8_t lYc, uint8_t lRad);

/**
 * @brief   快速清除圆法
 *
 * @param   lXc
 * @param   lYc
 * @param   lRad
 */
void UC1701_DrawCycFastClr(uint8_t lXc, uint8_t lYc, uint8_t lRad);

/**
 * @brief   画矩形带阴影外框
 *
 * @param   lX1
 * @param   lY1
 * @param   lX2
 * @param   lY2
 */
void UC1701_DrawRecFramSet(uint8_t lX1, uint8_t lY1, uint8_t lX2, 
							uint8_t lY2);

/**
 * @brief   清除矩形阴影
 *
 * @param   lX1
 * @param   lY1
 * @param   lX2
 * @param   lY2
 */
void UC1701_DrawRecFramClr(uint8_t lX1, uint8_t lY1, uint8_t lX2, 
							uint8_t lY2);

/**
 * @brief   画折边矩形
 *
 * @param   lX1
 * @param   lY1
 * @param   lX2
 * @param   lY2
 */
void UC1701_DrawRecDiagSet(uint8_t lX1, uint8_t lY1, uint8_t lX2, 
							uint8_t lY2);

/**
 * @brief   清除折边矩形
 *
 * @param   lX1
 * @param   lY1
 * @param   lX2
 * @param   lY2
 */
void UC1701_DrawRecDiagClr(uint8_t lX1, uint8_t lY1, uint8_t lX2, 
							uint8_t lY2);

/**
 * @brief   画折边矩形带阴影
 *
 * @param   lX1
 * @param   lY1
 * @param   lX2
 * @param   lY2
 */
void UC1701_DrawRecDiagFramSet(uint8_t lX1, uint8_t lY1, uint8_t lX2, 
								uint8_t lY2);

/**
 * @brief   清除折边矩形阴影
 *
 * @param   lX1
 * @param   lY1
 * @param   lX2
 * @param   lY2
 */
void UC1701_DrawRecDiagFramClr(uint8_t lX1, uint8_t lY1, uint8_t lX2, 
								uint8_t lY2);

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
					uint8_t lXSize, uint8_t lYSize);

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
					uint8_t lXSize, uint8_t lYSize);

/**
 * @brief   uc1701 显示所有，注意没有改变DRAM数值
 */
void UC1701_DisAll(void);

/**
 * @brief   uc1701 反显当前内容
 */
void UC1701_DisRev(void);

/**
 * @brief   uc1701 清除所有内容
 */
void UC1701_DisClr(void);

/**
 * @brief   uc1701 软件坐标到硬件坐标的转换
 *
 * @param   lX
 * @param   lY
 */
void UC1701_CorCvt(uint8_t *lX, uint8_t *lY);

/**
 * @brief   uc1701 正常持有的显示方式
 */
void UC1701_MirUp(void);

/**
 * @brief   uc1701 倒着持有的显示方式
 */
void UC1701_MirDown(void);

/**
 * @brief   uc1701 初始化
 */
void UC1701_Init(void);

/**
 * @brief   uc1701 断电
 */
void UC1701_PwrDown(void);

#endif
