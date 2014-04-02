/**
 * @file    self_check_gas_range.h
 * @brief   气体名称自检 头文件
 * @author  ptz
 * @email   ptz19861212@163.com
 * @version 0.0.1
 * @date    2013-12-02 13:35:28 星期一 
 * @history (1).2013-12-02 13:35:28 星期一 create
 */
/* Copyright (C)
 * 
 * My own license
 * All right reserved
 * 
 */

#ifndef __SELF_CHECK_GAS_RANGE_H__
#define __SELF_CHECK_GAS_RANGE_H__

#include "self_check.h"

/**
 * @brief   自检初始化
 */
void SelfCheckGasRangeInit(void);


// 自检的资源
extern const struct S_SelfCheckResource gSelfCheckRsrGasRange;


#endif
