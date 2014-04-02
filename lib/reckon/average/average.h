/**
 * @file    average.h
 * @brief   求平均数
 * @author  ptz
 * @email   ptz19861212@163.com
 * @version 0.0.1
 * @date    2013-12-11 13:00:34 星期三 
 * @history (1).2013-12-11 13:00:34 星期三 create
 */
/* Copyright (C)
 * 
 * My own license
 * All right reserved
 * 
 */

#ifndef __AVERAGE_H__
#define __AVERAGE_H__

/**
 * @brief   数组求平均数，8位无符号数
 */
uint8_t AverageU8(uint8_t *lpBuf, uint16_t lNum);


/**
 * @brief   数组求平均数，16位无符号数
 */
uint16_t AverageU16(uint16_t *lpBuf, uint16_t lNum);


/**
 * @brief   数组求平均数，32位无符号数
 */
uint32_t AverageU32(uint32_t *lpBuf, uint16_t lNum);


/**
 * @brief   设置数组地址，位数求滑动平均数，16位无符号数值
 */
void AverageMoveSetU16(uint16_t *lpBuf, uint8_t lNum);


/**
 * @brief   数组求滑动平均数，16位无符号数
 */
uint16_t AverageMoveU16(uint16_t lData);

#endif
