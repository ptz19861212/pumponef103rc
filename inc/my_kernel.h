/**
 * @file    mykernel.h
 * @brief   kernel
 * @author  ptz
 * @email   ptz19861212@163.com
 * @version 0.0.1
 * @date    2012-08-06 11:42:02 星期四 
 * @history (1).2012-08-06 11:42:02 星期四 create
 */
/* Copyright (C)
 * 
 * My own license
 * All right reserved
 * 
 */

#ifndef __MY_KERNEL_H__
#define __MY_KERNEL_H__

#include "my_int.h"

struct S_Kernel_Task
{
	//point of task function
	FUN_P pTask;						
	//delay of the task
	uint8_t TaskDelay;						
	//period of the task
	uint8_t TaskPeriod;						
	//task can run this time
	uint8_t TaskRun;						
};

#endif
