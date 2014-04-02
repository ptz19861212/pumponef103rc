/**
 * @file    num_to_str.h
 * @brief   数字转换字符串
 * @author  ptz
 * @email   ptz19861212@163.com
 * @version 0.0.1
 * @date    2013-12-06 15:02:15 星期五 
 * @history (1).2013-12-06 15:02:15 星期五 create
 */
/* Copyright (C)
 * 
 * My own license
 * All right reserved
 * 
 */

#ifndef __NUM_TO_STR_H__
#define __NUM_TO_STR_H__


/**
 * @brief   8位数字转换为字符串
 * 				例如：3.2， 那么lNum = 32，lPoint = POINT_HHHHXH
 *
 * @param   lpData 十进制数字字符数组的首地址
 * @param   lNum 需要转换的数字（不含小数点）
 * @param   lPoint 需要添加的小数点所在的位置
 */
//void DecToStrU8(uint8_t *lpData, uint8_t lNum, uint8_t lPoint);
void DecToStrU8(S_Value_Array_U8* lpValue);


/**
 * @brief   16位数字转换为字符串
 * 				例如：1234.2， 那么lNum = 12342，lPoint = POINT_HHHHXH
 *
 * @param   lpData 十进制数字字符数组的首地址
 * @param   lNum 需要转换的数字（不含小数点）
 * @param   lPoint 需要添加的小数点所在的位置
 */
//void DecToStrU16(uint8_t *lpData, uint16_t lNum, uint8_t lPoint);
void DecToStrU16(S_Value_Array_U16* lpValue);


/**
 * @brief   32位数字转换为字符串
 * 				例如：654321.2， 那么lNum = 6543212，lPoint = POINT_HHHHXH
 *
 * @param   lpData 十进制数字字符数组的首地址
 * @param   lNum 需要转换的数字（不含小数点）
 * @param   lPoint 需要添加的小数点所在的位置
 */
//void DecToStrU32(uint8_t *lpData, uint32_t lNum, uint8_t lPoint);
void DecToStrU32(S_Value_Array_U32* lpValue);

#endif
