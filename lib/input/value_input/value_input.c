/**
 * @file    value_input.c
 * @brief   输入数值
 * @author  ptz
 * @email   ptz19861212@163.com
 * @version 0.0.1
 * @date    2013-12-29 21:26:41 星期日 
 * @history (1).2013-12-29 21:26:41 星期日 create
 */
/* Copyright (C)
 * 
 * My own license
 * All right reserved
 * 
 */

#include "value_input_in.h"

typedef struct
{
	// 16位带小数点的数 上限
//	char Up[7];
	uint16_t Up;
	char UpArray[7];
	// 16位带小数点的数 下限
//	char Low[7];
	uint16_t Low;
	char LowArray[7];
	// 16位带小数点的数
	char Now[7];
	// 当前的数值
	S_Value_Array_U16 ValueArray;
	// 16位数值的实际长度，包括小数点在内
	uint8_t Len;
	// 16位数值当前位的下标，-1 对应的是还没有进入输入状态的反显准备状态
	int8_t Index;
}S_Value_Input_Array_U16;

S_Value_Input_Array_U16 sInputArrayU16 =
{
		.Index = -1,
};


/**
 * @brief   设置数值输入的上下限制
 *
 * @param   lpInput 输入的数值
 */
void ValueInputSetU16(S_Value_Input_U16* lpInput)
{
//	if (lpInput->Up, lpInput->Low)
	if (lpInput->Up < lpInput->Low)
	{
		SWAP(lpInput->Up, lpInput->Low);
	}

	sInputArrayU16.ValueArray.Char = sInputArrayU16.Now;

	uint8_t lArray[7];
	S_Value_Array_U16 lValue;
	lValue.Char = lArray;
//	lValue.Value.Num = lpInput->Up - 1;
	lValue.Value.Num = lpInput->Up;
	lValue.Value.Point = lpInput->Point;

	DecToStrU16(&lValue);
	sInputArrayU16.Len = strlen(lArray);
//	sInputArrayU16.Up = lpInput->Up - 1;
	sInputArrayU16.Up = lpInput->Up;

	// 这个是为了增加数值的时候防止上溢出
	lValue.Char = sInputArrayU16.UpArray;
	lValue.Value.Num = sInputArrayU16.Up;
	DecToStrU16(&lValue);

	lValue.Char = sInputArrayU16.Now;
	lValue.Value.Num = lpInput->Init;
	DecToStrU16(&lValue);
	FlushRightStr(sInputArrayU16.Now, sInputArrayU16.Len, '0');

//	sInputArrayU16.Low = lpInput->Low + 1;
	sInputArrayU16.Low = lpInput->Low;

	lValue.Char = sInputArrayU16.LowArray;
	lValue.Value.Num = sInputArrayU16.Low;
	DecToStrU16(&lValue);
	FlushRightStr(sInputArrayU16.LowArray, sInputArrayU16.Len,
						'0');

	sInputArrayU16.Index = -1;
}


/**
 * @brief   数值增加
 */
void ValueInputPlusU16(void)
{
	if (sInputArrayU16.Now[sInputArrayU16.Index] < '9')
	{
		sInputArrayU16.Now[sInputArrayU16.Index]++;
	}

	DecStrLimitUpperU16(sInputArrayU16.Now,
							sInputArrayU16.UpArray);
}


/**
 * @brief   数值减少
 */
void ValueInputMinusU16(void)
{
	if (sInputArrayU16.Now[sInputArrayU16.Index] > '0')
	{
		sInputArrayU16.Now[sInputArrayU16.Index]--;
	}

	DecStrLimitLowerU16(sInputArrayU16.Now,
								sInputArrayU16.LowArray);
}


/**
 * @brief   按确认按键，下标移动
 *
 * @return  返回输入状态
 */
ReturnState ValueInputAcceptU16(void)
{
	sInputArrayU16.Index++;

	// 还没完全输入完成
	if (sInputArrayU16.Index < sInputArrayU16.Len)
	{
		// 判断小数点
		if (sInputArrayU16.Now[sInputArrayU16.Index] == '.')
		{
			sInputArrayU16.Index++;
		}

		return RETURN_WAIT;
	}
	// 输入结束
	else
	{
		sInputArrayU16.Index = -1;
		return RETURN_OK;
	}
}


/**
 * @brief   按返回按键，下标移动
 *
 * @return  返回输入状态
 */
ReturnState ValueInputCancelU16(void)
{
	// 还没完全输入完成
//	if (sInputArrayU16.Index > -1)
	if (sInputArrayU16.Index > 0)
	{
		sInputArrayU16.Index--;
		// 判断小数点
		if (sInputArrayU16.Now[sInputArrayU16.Index] == '.')
		{
			sInputArrayU16.Index--;
		}

		return RETURN_WAIT;
	}
	// 退出
	else
	{
		sInputArrayU16.Index = -1;
		return RETURN_EXIT;
	}
}


/**
 * @brief   获得位置下标
 *
 * @param   lpIndex 当前的位置下标
 */
void ValueInputIndexGet(uint8_t* lpIndex)
{
	*lpIndex = sInputArrayU16.Index;
}


/**
 * @brief   获得当前显示的数组
 *
 * @param   lpArray 当前显示的数组的地址
 */
void ValueInputArrayGet(char** lpArray)
{
	*lpArray = sInputArrayU16.Now;
}


/**
 * @brief   获得当前输入的数
 *
 * @param   lpValue
 */
void ValueInputGetU16(S_Value_Array_U16* lpValue)
{
	lpValue->Char = sInputArrayU16.Now;

	StrToDecU16(lpValue);
}
