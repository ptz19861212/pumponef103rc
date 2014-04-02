/**
 * @file    bit_get.h
 * @brief   求被置位的位
 * @author  ptz
 * @email   ptz19861212@163.com
 * @version 0.0.1
 * @date    2013-12-17 21:21:03 星期二 
 * @history (1).2013-12-17 21:21:03 星期二 create
 */
/* Copyright (C)
 * 
 * My own license
 * All right reserved
 * 
 */

#ifndef __BIT_GET_H__
#define __BIT_GET_H__

#include <stdint.h>

/**
 * @brief   求数字的最右边的被置位的位
 *
 * @param   lpData 数字的地址
 * @param   lpBit 置位的位的地址
 * @param   lBitNum 数字的位数，如果是字节那么就是8,其他以此类推
 *
 * @return  是否出错
 */
int8_t BitGet(uint8_t* lpData, uint8_t* lpBit, uint8_t lBitNum);

#endif
