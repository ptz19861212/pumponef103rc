/**
 * @file    bsp_source.c
 * @brief   
 * @author  ptz
 * @email   ptz19861212@163.com
 * @version 0.0.1
 * @date    2014-01-23 15:24:29 星期四 
 * @history (1).2014-01-23 15:24:29 星期四 create
 */
/* Copyright (C)
 * 
 * My own license
 * All right reserved
 * 
 */

#include "bsp_source_in.h"

/**
 * @brief   电源打开
 */
void SourceOn(void)
{
	SOURCE_On();
}


/**
 * @brief   电源关闭
 */
void SourceOff(void)
{
	SOURCE_Off();
}


/**
 * @brief   电源初始化
 */
void SourceInit(void)
{
	SOURCE_Init();
}

