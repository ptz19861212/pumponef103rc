
/**
 * @file my_num.h
 * @brief: my int define 
 * @author ptz, ptz19861212@163.com
 * @version 0.0.1
 * @date 2012-10-14
 */

/* Copyright(C)
 * My own license
 * All right reserved
 * 
 */

#ifndef __MY_NUM_H__
#define __MY_NUM_H__

#include <stdint.h>


// point
typedef enum {POINT_HHHHH= 0, \
				POINT_HHHHXH,\
				POINT_HHHXHH,\
				POINT_HHXHHH,\
				POINT_HXHHHH,} PointState;

#define TYPE_U8_LEN				3
#define TYPE_U16_LEN			5
#define TYPE_U32_LEN			10

typedef struct
{
	// 数值 不含小数点
	uint8_t Num;
	// 小数点的位置，从右向左数
	uint8_t Point;
}S_Value_U8;

typedef struct
{
	// 数值 不含小数点
	uint16_t Num;
	// 小数点的位置，从右向左数
	uint8_t Point;
}S_Value_U16;

typedef struct
{
	// 数值 不含小数点
	uint32_t Num;
	// 小数点的位置，从右向左数
	uint8_t Point;
}S_Value_U32;

typedef struct
{
	// 字符数组
//	char Char[5];
	char* Char;
	// 数值 不含小数点
//	uint8_t Num;
	// 小数点的位置，从右向左数
//	uint8_t Point;
	S_Value_U8 Value;
}S_Value_Array_U8;

typedef struct
{
	// 字符数组
//	char Char[7];
	char* Char;
	// 数值 不含小数点
//	uint16_t Num;
	// 小数点的位置，从右向左数
//	uint8_t Point;
	S_Value_U16 Value;
}S_Value_Array_U16;

typedef struct
{
	// 字符数组
//	char Char[12];
	char* Char;
	// 数值 不含小数点
//	uint32_t Num;
	// 小数点的位置，从右向左数
//	uint8_t Point;
	S_Value_U32 Value;
}S_Value_Array_U32;


typedef struct
{
	// 数值 不含小数点
	uint8_t Num;
	// 小数点的位置，从右向左数
	uint8_t Point;
	// 靠右显示的位数
	uint8_t Len;
}S_Value_Right_U8;

typedef struct
{
	// 数值 不含小数点
	uint16_t Num;
	// 小数点的位置，从右向左数
	uint8_t Point;
	// 靠右显示的位数
	uint8_t Len;
}S_Value_Right_U16;

typedef struct
{
	// 数值 不含小数点
	uint32_t Num;
	// 小数点的位置，从右向左数
	uint8_t Point;
	// 靠右显示的位数
	uint8_t Len;
}S_Value_Right_U32;

typedef struct
{
	// 字符数组
//	char Char[5];
	char* Char;
	// 数值 不含小数点
//	uint8_t Num;
	// 小数点的位置，从右向左数
//	uint8_t Point;
	S_Value_Right_U8 Value;
}S_Value_Right_Array_U8;

typedef struct
{
	// 字符数组
//	char Char[7];
	char* Char;
	// 数值 不含小数点
//	uint16_t Num;
	// 小数点的位置，从右向左数
//	uint8_t Point;
	S_Value_Right_U16 Value;
}S_Value_Right_Array_U16;

typedef struct
{
	// 字符数组
//	char Char[12];
	char* Char;
	// 数值 不含小数点
//	uint32_t Num;
	// 小数点的位置，从右向左数
//	uint8_t Point;
	S_Value_Right_U32 Value;
}S_Value_Right_Array_U32;

//typedef void(*FUN_P)(void);//(int Data)		point of function
//typedef void(*FUN_P_V_V)(void);//(int Data)		point of function
//typedef void(*FUN_P_V_U8)(uint8_t lData);		//point of function

#endif
