/**
 * @file    flush_right.h
 * @brief   右移
 * @author  ptz
 * @email   ptz19861212@163.com
 * @version 0.0.1
 * @date    2013-08-13 17:27:37 星期二 
 * @history (1).2013-08-13 17:27:37 星期二 create
 */
/* Copyright (C)
 * 
 * My own license
 * All right reserved
 * 
 */

#ifndef __FLUSH_RIGHT_H__
#define __FLUSH_RIGHT_H__

#include <stdint.h>

/**
 * @brief   右移，主要用于字符数组的右移，移动指定的数组，把前面的标志性字符去除，
 * 				其他的右移，在后面在添加上标志性字符。
 * 				例如 原来[a][a][b][c][d]，那么lLength就是5,lFlag就是[a]，转换结束
 * 				就是[b][c][d][a][a]
 *
 * @param   lData[]
 * @param   lLength 只针对这个长度的数组进行操作
 * @param   lFlag 前面需要清除的标志性字符
 */
void FlushRight(uint8_t lData[], uint8_t lLength, uint8_t lFlag);


/**
 * @brief   右移，主要用于字符串的右移。移动指定字符数组，把前面的标志性字符去除，
 * 				其他的右移，在后面加上'\0'结束。
 * 				例如原来是[a][a][b][c][d][\0]，那么lLength就是5,lFlag就是[a]，转换结束
 * 				就是[b][c][d][\0]，这样的字符串。
 *
 * @param   lData[]
 * @param   lLength 只针对这个长度的数组进行操作，这个长度不包换'\0'，类似于 strlen 求出
 * 				的字符串长度，如果这个长度中的字符都是标志字符，那么将在[0]这个起始位置放入
 * 				'\0'
 * @param   lFlag 前面需要清除的标志性字符
 */
void FlushRightStr(uint8_t *lData, uint8_t lLength, uint8_t lFlag);

#endif
