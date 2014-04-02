/**
 * @file    num_limit.h
 * @brief   
 * @author  ptz
 * @email   ptz19861212@163.com
 * @version 0.0.1
 * @date    2014-01-16 10:25:25 星期四 
 * @history (1).2014-01-16 10:25:25 星期四 create
 */
/* Copyright (C)
 * 
 * My own license
 * All right reserved
 * 
 */

#ifndef __NUM_LIMIT_H__
#define __NUM_LIMIT_H__

/**
 * @brief   两个16位数字组成的字符串进行上限的限制，注意因为是字符串
 * 				所以有可能溢出，所以才有了这个函数，函数内部作为32位数
 * 				进行处理
 *
 * @param   lpNow
 * @param   lpUp
 */
void DecStrLimitUpperU16(char* lpNow, char* lpUp);


/**
 * @brief   两个16位数字组成的字符串进行上限的限制，注意因为是字符串
 * 				所以有可能溢出，所以才有了这个函数，函数内部作为32位数
 * 				进行处理
 *
 * @param   lpNow
 * @param   lpUp
 */
void DecStrLimitLowerU16(char* lpNow, char* lpLow);


#endif
