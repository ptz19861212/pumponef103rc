/**
 * @file    bubble_sort.h
 * @brief   冒泡排序
 * @author  ptz
 * @email   ptz19861212@163.com
 * @version 0.0.1
 * @date    2013-12-11 11:09:49 星期三 
 * @history (1).2013-12-11 11:09:49 星期三 create
 */
/* Copyright (C)
 * 
 * My own license
 * All right reserved
 * 
 */

#ifndef __BUBBLE_SORT_H__
#define __BUBBLE_SORT_H__


/**
 * @brief   冒泡排序 8位数值
 */
void BubbleSortU8(uint8_t lArray[], uint16_t lNumber);


/**
 * @brief   冒泡排序 16位数值
 */
void BubbleSortU16(uint16_t lArray[], uint16_t lNumber);


/**
 * @brief   冒泡排序 32位数值
 */
void BubbleSortU32(uint32_t lArray[], uint16_t lNumber);

#endif
