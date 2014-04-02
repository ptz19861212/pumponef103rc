/**
 * @file    self_check.h
 * @brief   自检 框架代码的外露头文件
 * @author  ptz
 * @email   ptz19861212@163.com
 * @version 0.0.1
 * @date    2013-12-01 18:52:28 星期日 
 * @history (1).2013-12-01 18:52:28 星期日 create
 */
/* Copyright (C)
 * 
 * My own license
 * All right reserved
 * 
 */

#ifndef __SELF_CHECK_H__
#define __SELF_CHECK_H__

//#include "my_gas.h"
#include "my_device.h"
#include "display_uc1701.h"
#include "display.h"


/******************************* 预定义 ******************************/
typedef uint8_t 					self_check_t;

typedef void (*SelfCheckFun)(void);



/**
 * @brief   自检初始化
 */
void SelfCheckInit(void);


/**
 * @brief   获取当前的自检项是那一条
 *
 * @param   lpItem 地址
 */
self_check_t SelfCheckIndexGet(void);


/**
 * @brief   自检画面跳转的初始化
 */
void SelfCheckJumpInit(void);


/**
 * @brief   自检画面是否跳转的测试
 */
void SelfCheckJumpCheck(void);







// 用于自检调用相应的菜单函数
typedef struct
{
	self_check_t Index;
	SelfCheckFun Init;
}S_SelfCheckTab;


struct S_SelfCheckResource
{
	// 当前的自检索引
	self_check_t Index;
	// 多语言自检文字数组
	const char*** Text;
	// 文字字符串数量
	uint8_t Num;
	// 下一条自检资源
	const struct S_SelfCheckResource* Next;
};

//typedef struct
//{
//	// 当前的自检索引
//	self_check_t Index;
//	// 多语言自检标题数组
//	const char*** Text;
//	// 下一条自检资源
//	const S_SelfCheckResource* Next;
//}S_SelfCheckResource;


// 生成按键函数表
#define SELF_CHECK_RESOURCE(TEXT, Text, Next)		\
								SELF_CHECK_##TEXT##_INDEX,\
								sSelfCheck##Text##Txt,\
								STR_NUM(sSelfCheck##Text##TxtEn),\
								&gSelfCheckRsr##Next,\



#endif
