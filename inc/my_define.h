/**
 * @file    my_define.h
 * @brief   �����
 * @author  ptz
 * @email   ptz19861212@163.com
 * @version 0.0.1
 * @date    2013-08-08 15:37:52 ������ 
 * @history (1).2013-08-08 15:37:52 ������ create
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

#define BIT(n)					(0x01 << (n))
#define CONTROL_ON				0x01
#define CONTROL_OFF				0x00
#define TRUE					1
#define FALSE					0

#define RETURN_OK				0
#define RETURN_ERROR			-1
#define RETURN_STATUS_1			1
#define RETURN_STATUS_2			2
#define RETURN_STATUS_3			3
#define RETURN_STATUS_4			4

#ifndef NULL
	#define NULL 				0
#endif

#ifndef PNULL
	#define PNULL 				((void *)0)
#endif

#define SWAP(a, b)	\
		do{typeof(a) lTemp; lTemp = a; a = b; b = lTemp;}while(0)


/* stdarg.h standard header */

/* type definitions */
//typedef u8					*va_list_me;
/* macros */
//���ͷ�ļ��е��ڲ��궨��_Bnd(X, bnd)�����ͻ����X�ĳ��ȶ��뵽bnd+1�ֽڵ�������������_Bnd(char, 3U)��ֵ��4��_Bnd(int, 3U)Ҳ��4
//http://learn.akae.cn/media/ch24s06.html
//#define va_arg_me(ap, T) 			(* (T *)(((ap) += _Bnd(T, 3U)) - _Bnd(T, 3U)))
//#define va_end_me(ap) 				(void)0
//#define va_start_me(ap, A) 			(void)((ap) = (char *)&(A) + _Bnd(A, 3U))
//#define _Bnd(X, bnd) 				(sizeof (X) + (bnd) & ~(bnd))


// һ��ָ��ռ�еĿռ��С
//typedef uint16_t 	size_me;
typedef uint32_t 	size_me;

//ע����ߵ�����Ӧ�ú�ָ��ռ�еĿռ���һ��������ͣ�������о�����Ϣ
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
