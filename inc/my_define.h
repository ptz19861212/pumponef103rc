/**
 * @file    my_define.h
 * @brief   自定义的杂项
 * @author  ptz
 * @email   ptz19861212@163.com
 * @version 0.0.1
 * @date    2013-08-08 15:37:52 星期四
 * @history (1).2013-08-08 15:37:52 星期四 create
 */
/* Copyright (C)
 * 
 * My own license
 * All right reserved
 * 
 */


#ifndef __MY_DEFINE_H__
#define __MY_DEFINE_H__

#include <stdint.h>
// 为了处理 eclipse 红色警告，关于ENABLE，所以加上stm32的头文件
//#include "stm32f10x.h"

// 根据芯片的不同，最基本的指针所占有的空间
//typedef uint16_t 	size_me;
//typedef uint32_t 	size_me;
typedef int32_t			my_base_t;
typedef uint32_t		my_ubase_t;
typedef my_base_t		my_err_t;


typedef void (*MY_FUNC)(void);
//typedef void (*MY_FUN1)(uint8_t l1, uint8_t l2, uint8_t l3);
// 定义函数 void func1(uint8_t a, uint8_t b, uint8_t c);
// 定义结构体中的函数指针使用 MY_FUN vfunc;
// 初始化结构体的时候使用 (MY_FUN)func1;
// 调用函数的时候使用 (*(MY_FUN1)lp)(1, 2, 3);
// 注意定义函数的时候和调用函数的时候类型必须一致，定义函数指针和初始化指针的时候必须一致，
// 可以使用强制转换来调用不同数目参数的函数。
// 函数指针可以使用简短模式和完整模式，也可以两种混用
// 简短模式是 赋值是 lp = func1, 调用是 func1()
// 完整模式是 赋值是 lp = &func1, 调用是 (*func1)()


#define BIT(n)					(0x01 << (n))

//#ifndef __STM32F10x_H
//	typedef enum {DISABLE = 0, ENABLE = !DISABLE} FunctionalState;
//#endif

typedef enum {TURN_OFF = 0, TURN_ON = !TURN_OFF} E_TurnState;

// 是那些类型的二值数值
typedef enum {BINARY_ONOFF= 0, BINARY_YESNO} E_BinaryState;

//typedef enum {ONOFF_ON = 0, ONOFF_OFF = 1} E_OnOffState;

// 是否
typedef enum {E_FALSE = 0, E_TRUE = !E_FALSE} E_TrueState;

// 是否闪烁
typedef enum {BLINK_OFF = 0, BLINK_ON = !BLINK_OFF} E_BlinkState;

// 是否锁定
typedef enum {LOCK_OFF = 0, LOCK_ON = !LOCK_OFF} E_LockState;

// flash 未保存位 1, 保存为 0
typedef enum {FLASH_SAVE_FALSE = 1, FLASH_SAVE_TRUE = 0} E_FlashSaveState;

//#define CONTROL_ON				0x01
//#define CONTROL_OFF				0x00
//#define TRUE					1
//#define FALSE					0

typedef uint32_t my_time_t;
typedef uint32_t my_second_t;
typedef uint32_t my_minute_t;
typedef uint16_t my_hour_t;
typedef uint16_t my_day_t;

typedef int8_t my_return_t;

typedef enum	{
					RETURN_ERR = -1,
					RETURN_OK = 0,
					RETURN_WAIT = 1,
					RETURN_EXIT = 2,
					//RETURN_STATE_3 = 3,
					//RETURN_STATE_4 = 4,
				} ReturnState;
//#define RETURN_OK				0
//#define RETURN_ERROR			-1
//#define RETURN_STATUS_1			1
//#define RETURN_STATUS_2			2
//#define RETURN_STATUS_3			3
//#define RETURN_STATUS_4			4

//#define TYPE_U8_LEN				3
//#define TYPE_U16_LEN			5
//#define TYPE_U32_LEN			10

#ifndef NULL
	#define NULL 				0
#endif

#ifndef PNULL
	#define PNULL 				((void *)0)
#endif



// point
//typedef enum {POINT_HHHHH= 0, \
//				POINT_HHHHXH,\
//				POINT_HHHXHH,\
//				POINT_HHXHHH,\
//				POINT_HXHHHH,} PointState;

//#define POINT_HHHHH                             0
//#define POINT_HHHHXH                            1
//#define POINT_HHHXHH                            2
//#define POINT_HHXHHH                            3
//#define POINT_HXHHHH                            4

#define SWAP(a, b)	\
		do{typeof(a) lTemp; lTemp = a; a = b; b = lTemp;}while(0)



// 连接 (123, 456) 123456
//#define CONNECT(x,y)		x##y

// 生成字符  (a)  'a'
//#define TO_CHAR(x)			#@x

// 生成字符串 (abc) "abc"
//#define TO_STRING(x)		#x


/* stdarg.h standard header */

/* type definitions */
//typedef u8					*va_list_me;
/* macros */
//���ͷ�ļ��е��ڲ��궨��_Bnd(X, bnd)�����ͻ����X�ĳ��ȶ��뵽bnd+1�ֽڵ���������_Bnd(char, 3U)��ֵ��4��_Bnd(int, 3U)Ҳ��4
//http://learn.akae.cn/media/ch24s06.html
//#define va_arg_me(ap, T) 			(* (T *)(((ap) += _Bnd(T, 3U)) - _Bnd(T, 3U)))
//#define va_end_me(ap) 				(void)0
//#define va_start_me(ap, A) 			(void)((ap) = (char *)&(A) + _Bnd(A, 3U))
//#define _Bnd(X, bnd) 				(sizeof (X) + (bnd) & ~(bnd))


// 用来求出结构体中的某个元素的偏移量
#define offsetof(TYPE, MEMBER) 			((size_me) &((TYPE *) 0)->MEMBER)

/** 

 * container_of - cast a member of a structure out to the containing structure 

 * @ptr:        the pointer to the member. 

 * @type:       the type of the container struct this is embedded in. 

 * @member:     the name of the member within the struct. 

 * 

 */ 

#define container_of(ptr, type, member) 	({			\
		const typeof(((type *)0)->member) *__mptr = (ptr);	\
		(type *)((char *)__mptr - offsetof(type, member));})

#endif
