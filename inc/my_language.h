/**
 * @file    my_language.h
 * @brief   language
 * @author  ptz
 * @email   ptz19861212@163.com
 * @version 0.0.1
 * @date    2013-12-02 16:39:20 星期一 
 * @history (1).2013-12-02 16:39:20 星期一 create
 */
/* Copyright (C)
 * 
 * My own license
 * All right reserved
 * 
 */

#ifndef __MY_LANGUAGE_H__
#define __MY_LANGUAGE_H__

#include <stdint.h>

typedef enum {
					LANGUAGE_EN = 0,
					LANGUAGE_CN = 1,
} E_Language;


//typedef struct
//{
//	// 汉字内码 utf-8
////	uint8_t Code[2];
//	// 汉字作为字符串保存，这样就不需要考虑是哪种内码
//	uint8_t Char[3];
//	// 汉字点阵数据
//	uint8_t Font[32];
//}S_Dual_Byte_Character_16x16;


typedef struct
{
	// 汉字内码 utf-8
//	uint8_t Code[2];
	// 汉字作为字符串保存，这样就不需要考虑是哪种内码
	uint8_t Char[3];
	// 汉字点阵数据 实际上是 14x14
	uint8_t Font[28];
}S_Dual_Byte_Character_16x16;



//#define LANGUAGE_EN					0
//#define LANGUAGE_CN					1

#endif
