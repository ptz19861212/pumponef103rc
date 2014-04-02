/**
 * @file    self_check_end.c
 * @brief   结束自检
 * @author  ptz
 * @email   ptz19861212@163.com
 * @version 0.0.1
 * @date    2013-12-02 13:34:47 星期一 
 * @history (1).2013-12-02 13:34:47 星期一 create
 */
/* Copyright (C)
 * 
 * My own license
 * All right reserved
 * 
 */

#include "self_check_end_in.h"

// 结束自检的自检项 英文
const char *sSelfCheckEndTxtEn[] =
{
		"",
};

// 结束自检的自检项 中文
const char *sSelfCheckEndTxtCn[] =
{
		"",
};

// 结束自检的自检项 指针数组
const char **sSelfCheckEndTxt[] =
{
		sSelfCheckEndTxtEn,
		sSelfCheckEndTxtCn,
};


// 结束自检的下一个自检资源
const struct S_SelfCheckResource* sSelfCheckRsrEndNext =
											&gSelfCheckRsrEnd;

// 结束自检 资源，包括自身字符串，自检项字符串，自检项的数目
const struct S_SelfCheckResource gSelfCheckRsrEnd =
{
		SELF_CHECK_RESOURCE(END, End, End)
};


/**
 * @brief   自检初始化
 */
void SelfCheckEndInit(void)
{
	// 结束自检资源初始化
//	SelfCheckInit();
//	SelfCheckJumpInit();
//	DisClr();
//	SelfCheckFrameDisp();
//	SelfCheckDisp();
	StateSelfCheckToDetect();
}

