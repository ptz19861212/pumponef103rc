/**
 * @file    value_input.h
 * @brief   数值输入
 * @author  ptz
 * @email   ptz19861212@163.com
 * @version 0.0.1
 * @date    2013-12-29 21:27:07 星期日 
 * @history (1).2013-12-29 21:27:07 星期日 create
 */
/* Copyright (C)
 * 
 * My own license
 * All right reserved
 * 
 */

#ifndef __VALUE_INPUT_H__
#define __VALUE_INPUT_H__

#include "my_define.h"
#include "my_gas.h"
#include "my_num.h"
#include "my_input.h"


/**
 * @brief   设置数值输入的上下限制
 *
 * @param   lpInput 输入的数值
 */
void ValueInputSetU16(S_Value_Input_U16* lpInput);


/**
 * @brief   数值增加
 */
void ValueInputPlusU16(void);


/**
 * @brief   数值减少
 */
void ValueInputMinusU16(void);


/**
 * @brief   按确认按键，下标移动
 *
 * @return  返回输入状态
 */
ReturnState ValueInputAcceptU16(void);


/**
 * @brief   按返回按键，下标移动
 *
 * @return  返回输入状态
 */
ReturnState ValueInputCancelU16(void);


/**
 * @brief   获得位置下标
 *
 * @param   lpIndex 当前的位置下标
 */
void ValueInputIndexGet(uint8_t* lpIndex);


/**
 * @brief   获得当前显示的数组
 *
 * @param   lpArray 当前显示的数组的地址
 */
void ValueInputArrayGet(char** lpArray);


/**
 * @brief   获得当前输入的数
 *
 * @param   lpValue
 */
void ValueInputGetU16(S_Value_Array_U16* lpValue);


#endif
