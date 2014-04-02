/**
 * @file    state_input.c
 * @brief   
 * @author  ptz
 * @email   ptz19861212@163.com
 * @version 0.0.1
 * @date    2014-01-07 16:41:47 星期二 
 * @history (1).2014-01-07 16:41:47 星期二 create
 */
/* Copyright (C)
 * 
 * My own license
 * All right reserved
 * 
 */

#include "state_input_in.h"

// 使能字符串 英文
const char *sInputOnOffEn[] =
{
		"On",
		"Off",
};

// 使能字符串 英文
const char *sInputOnOffCn[] =
{
		"打开",
		"关闭",
};

// 使能字符串 指针数组
const char **sInputOnOff[] =
{
		sInputOnOffEn,
		sInputOnOffCn,
};

// 使能字符串 英文
const char *sInputConfirmEn[] =
{
		"Yes",
		"No",
};

// 使能字符串 英文
const char *sInputConfirmCn[] =
{
		"是",
		"否",
};

// 使能字符串 指针数组
const char **sInputConfirm[] =
{
		sInputConfirmEn,
		sInputConfirmCn,
};

// 二值字符串 指针数组
const char ***gInputBinary[] =
{
		sInputOnOff,
		sInputConfirm,
};

// 使能字符串 英文
const char *sInputValueEn[] =
{
		"",
		"Yes",
		"No",
};

// 使能字符串 英文
const char *sInputValueCn[] =
{
		"",
		"是",
		"否",
};

// 使能字符串 指针数组
const char **sInputValue[] =
{
		sInputValueEn,
		sInputValueCn,
};


S_StateInputValue sValue;


// 用于按键表
S_State_Input_Tab sStateInputNow;


/**
 * @brief   菜单项输入数值的那一行的正常显示
 */
static void StateInputValueDispInit(void)
{
	S_Lcd__Item_Mid lTrig;

	char lData[GAS_VALUE_ARRAY_SIZE];
	S_Value_Array_U16 lArray;

	lArray.Char = lData;

	// 获取数值
//	(*(FUNC_STATE_INPUT_VALUE_GET)sValue.Func.ValueGet)(&(lArray.Value));
	(*sValue.Func.ValueGet)(&(lArray.Value));

	DecToStrU16(&lArray);
	lTrig.Item.Pos = CONFIG_INPUT_VALUE_POS;
	lTrig.Item.Char = lData;
	lTrig.Len = CONFIG_INPUT_LEN;
	Lcd__FrameItemMidDispHalf(&lTrig);
	// 反显
	Lcd__FrameItemRevHalf(CONFIG_INPUT_VALUE_POS);
}

/**
 * @brief   菜单项输入数值的初始显示，包括数值本身的显示
 *
 * @param   lpInput
 */
void StateInputValueInit(S_InputValue* lpInput)
{
	// 初始的
	sValue.Line.Index = 0;
	// 非锁定状态
	sValue.Line.Lock = LOCK_OFF;
	// 数值输入一共三行
	sValue.Line.Num = 3;

	// 函数
	sValue.Func.LimitGet = lpInput->Func.LimitGet;
	sValue.Func.Set = lpInput->Func.Set;
	// 这个必须先赋值，不然下面的显示第一行输入数值的函数就不能正常使用了
	sValue.Func.ValueGet = lpInput->Func.ValueGet;
	sValue.Func.Save = lpInput->Func.Save;
	sValue.Func.Confirm = lpInput->Func.Confirm;

	// 按键列表索引
	sStateInputNow.InputIndex = STATE_INPUT_VALUE_INDEX;

	E_Language lLang;

	// 获得当前显示的语言
	lLang = Lcd__LangGet();

	DisClr();

	S_Lcd_Area_RectangleShade lRec;
	lRec.Ex.X = CONFIG_VALUE_FRAME_EX_X;
	lRec.Ex.Y = CONFIG_VALUE_FRAME_EX_Y;
	lRec.PS.X = CONFIG_VALUE_FRAME_X_START;
	lRec.PS.Y = CONFIG_VALUE_FRAME_Y_START;
	lRec.PE.X = CONFIG_VALUE_FRAME_X_END;
	lRec.PE.Y = CONFIG_VALUE_FRAME_Y_END;
	DisRecFramSet(&lRec);

	uint8_t lI;
	S_Lcd__Item_Mid lTrig;
	// 显示全部的标签
	for (lI = 0; lI < STR_NUM(sInputValueEn); lI++)
	{
		lTrig.Item.Pos = CONFIG_INPUT_VALUE_POS + 2 * lI;
		lTrig.Item.Char = *(sInputValue[lLang] + lI);
		lTrig.Len = CONFIG_INPUT_LEN;
		Lcd__FrameItemMidDispHalf(&lTrig);
	}

	// 显示输入数字
//	char lData[GAS_VALUE_ARRAY_SIZE];
//	S_Value_Array_U16 lArray;
//
//	lArray.Char = lData;
//	lArray.Value.Num = lpInput->Value.Num;
//	lArray.Value.Point = lpInput->Value.Point;
//	DecToStrU16(&lArray);
//	lTrig.Item.Pos = CONFIG_INPUT_VALUE_POS;
//	lTrig.Item.Char = lData;
//	Lcd__FrameItemMidDispHalf(&lTrig);

	StateInputValueDispInit();
	// 反显
//	Lcd__FrameItemRevHalf(CONFIG_INPUT_VALUE_POS);
}


/**
 * @brief   输入控制函数结束
 */
static void StateInputValueOk(void)
{
	sValue.Line.Lock = LOCK_OFF;
//	gStateInputTab[sStateInputTab.InputIndex].Init();
	StateInputValueDispInit();
	DisBlinkOff();
	sStateInputTab[sStateInputNow.InputIndex].Down();
}


/**
 * @brief   输入控制函数退出
 */
static void StateInputValueCancel(void)
{
	sValue.Line.Lock = LOCK_OFF;
//	gMenuTab[sMenuFrame.MenuIndex].Init();
	StateInputValueDispInit();
	DisBlinkOff();
}


/**
 * @brief   输入控制函数+
 *
 * @param   lLine 输入的是屏幕的第几行
 */
static void StateInputValuePlus(void)
{
	int8_t lIndex;

	// 获取当前的下标
	ValueInputIndexGet(&lIndex);
	// +
	ValueInputPlusU16();

	// 获得当前的数值的显示数组
	char* lpArray;
	ValueInputArrayGet(&lpArray);

	// 在对应的行显示显示数组
//	MenuDisposeInputDisp(lpArray, lLine, lIndex);
	// 在对应的行显示显示数组， 闪烁显示
	S_Lcd__Blink lBlink;

	lBlink.Index = lIndex;
	lBlink.Trig.Len = CONFIG_INPUT_LEN;
	lBlink.Trig.Item.Char = lpArray;
	lBlink.Trig.Item.Pos = CONFIG_INPUT_VALUE_POS;
	Lcd__MenuInputValueBlinkDispHalf(&lBlink);
}


/**
 * @brief   输入控制函数-
 *
 * @param   lLine 输入的是屏幕的第几行
 */
static void StateInputValueMinus(void)
{
	int8_t lIndex;

	// 获取当前的下标
	ValueInputIndexGet(&lIndex);
	// +
	ValueInputMinusU16();

	// 获得当前的数值的显示数组
	char* lpArray;
	ValueInputArrayGet(&lpArray);

	// 在对应的行显示显示数组
//	MenuDisposeInputDisp(lpArray, lLine, lIndex);
	// 在对应的行显示显示数组， 闪烁显示
	S_Lcd__Blink lBlink;

	lBlink.Index = lIndex;
	lBlink.Trig.Len = CONFIG_INPUT_LEN;
	lBlink.Trig.Item.Char = lpArray;
	lBlink.Trig.Item.Pos = CONFIG_INPUT_VALUE_POS;
	Lcd__MenuInputValueBlinkDispHalf(&lBlink);
}


/**
 * @brief   按键 下一条
 */
static void StateInputValueNext(void)
{
	Lcd__FrameItemRevHalf(CONFIG_INPUT_VALUE_POS +
								2 * sValue.Line.Index);

	sValue.Line.Index++;

	if (sValue.Line.Index >= sValue.Line.Num)
	{
		// 这个是不能循环显示
		//sValue.Line.Index--;
		// 循环显示
		sValue.Line.Index = 0;
	}

	Lcd__FrameItemRevHalf(CONFIG_INPUT_VALUE_POS + 2 * sValue.Line.Index);
}


/**
 * @brief   按键 上一条
 */
static void StateInputValuePrev(void)
{
	Lcd__FrameItemRevHalf(CONFIG_INPUT_VALUE_POS +
								2 * sValue.Line.Index);

	if (sValue.Line.Index > 0)
	{
		// 这个是不能循环显示
		//sValue.Line.Index = 0;
		// 循环显示
		sValue.Line.Index--;
	}
	else
	{
		sValue.Line.Index = sValue.Line.Num - 1;
	}
	Lcd__FrameItemRevHalf(CONFIG_INPUT_VALUE_POS +
									2 * sValue.Line.Index);
}


/**
 * @brief   输入控制函数，这个是处理某一行数值输入的时候进行显示的
 */
static void StateInputValueBlinkDisp(void)
{
	int8_t lIndex;

	// 获取当前的下标
	ValueInputIndexGet(&lIndex);

	// 获得当前的数值的显示数组
	char* lpArray;
	ValueInputArrayGet(&lpArray);

	// 在对应的行显示显示数组， 闪烁显示
	S_Lcd__Blink lBlink;

	lBlink.Index = lIndex;
	lBlink.Trig.Len = CONFIG_INPUT_LEN;
	lBlink.Trig.Item.Char = lpArray;
	lBlink.Trig.Item.Pos = CONFIG_INPUT_VALUE_POS;
	Lcd__MenuInputValueBlinkDispHalf(&lBlink);
}


/**
 * @brief   菜单项最终处理确认
 */
static void StateInputValueConfirm(void)
{
	if ((sValue.Line.Lock == LOCK_OFF) && (sValue.Line.Index == 0))
	{
		sValue.Line.Lock = LOCK_ON;
	}

	// 输入数值
	if (sValue.Line.Lock == LOCK_ON)
	{
		int8_t lIndex;
		ValueInputIndexGet(&lIndex);

		// -1 表示初始化，对应的是整行反显
		if (lIndex == -1)
		{
			sValue.Func.LimitGet();
		}

		my_return_t lRet;

		lRet= ValueInputAcceptU16();
		StateInputValueBlinkDisp();

		if (lRet == RETURN_OK)
		{
			sValue.Func.Set();
//			StateInputValueDispInit();
			StateInputValueOk();

//			MenuDisposeValueInputOk();
		}
	}
	else
	{
//		uint8_t lChoose;
//		uint8_t* lpAny;
//		MenuDisposeChooseGet(&lChoose, &lpAny);
//		MenuDisposeExit();
//		MenuDisp();
		if (sValue.Line.Index == 1)
		{
			sValue.Func.Save();
			sValue.Func.Confirm(E_TRUE);
		}
		else
		{
			sValue.Func.Confirm(E_FALSE);
		}
//		StateInputToMenu();

	}
}


/**
 * @brief   菜单项最终处理退出
 */
static void StateInputValueExit(void)
{
	// 输入数值
	if (sValue.Line.Lock == LOCK_ON)
	{
		my_return_t lRet;

		lRet= ValueInputCancelU16();
//		MenuDisposeValueInputDisp(CONFIG_PARAM_STEL_ENTER_LINE_INIT);
		StateInputValueBlinkDisp();

		if (lRet == RETURN_EXIT)
		{
//			MenuDisposeValueInputCancel();
			StateInputValueCancel();
		}
	}
	else
	{
//		MenuDisposeExit();
//		MenuDisp();
		StateInputToMenu();
	}

}


/**
 * @brief   菜单项向下按键
 */
static void StateInputValueDown(void)
{
	// 输入数值
	if (sValue.Line.Lock == LOCK_ON)
	{
		StateInputValueMinus();
	}
	else
	{
		StateInputValueNext();
	}

}


/**
 * @brief   菜单项向上按键
 */
static void StateInputValueUp(void)
{
	// 输入数值
	if (sValue.Line.Lock == LOCK_ON)
	{
		StateInputValuePlus();
	}
	else
	{
		StateInputValuePrev();
	}

}



/************************************ 开关输入 ****************************************/
static S_StateInputBinary sBinary;

/**
 * @brief   菜单项输入那一行的正常显示
 */
static void StateInputBinaryDispInit(void)
{
	E_TurnState lState;
	// 获取开关状态
	(*sBinary.Func.BinaryGet)(&(lState));

	if (lState == TURN_OFF)
	{
		sBinary.Line.Index = 1;
	}
	else
	{
		sBinary.Line.Index = 0;
	}

	Lcd__FrameItemRev(CONFIG_INPUT_ONOFF_POS + sBinary.Line.Index);
}

/**
 * @brief   菜单项输入的初始显示，包括本身的显示
 *
 * @param   lpInput
 */
void StateInputBinaryInit(S_InputBinary* lpInput)
{
	// 初始的index 不要设置，因为要根据以前的onoff设置来确定初始的数值，
	// 在函数StateInputBinaryDispInit 中可以获得

	// 数值输入一共二行
	sBinary.Line.Num = 2;
	// 函数
//	sBinary.Func.Get = lpInput->Func.Get;
//	sBinary.Func.Set = lpInput->Func.Set;
	// 这个必须先赋值，不然下面的显示第一行输入数值的函数就不能正常使用了
	sBinary.Func.BinaryGet = lpInput->Func.BinaryGet;
	sBinary.Func.Save = lpInput->Func.Save;
	sBinary.Func.Confirm = lpInput->Func.Confirm;
	// 按键列表索引
	sStateInputNow.InputIndex = STATE_INPUT_BINARY_INDEX;

	E_Language lLang;

	// 获得当前显示的语言
	lLang = Lcd__LangGet();

	DisClr();

	S_Lcd_Area_RectangleShade lRec;
	lRec.Ex.X = CONFIG_BINARY_FRAME_EX_X;
	lRec.Ex.Y = CONFIG_BINARY_FRAME_EX_Y;
	lRec.PS.X = CONFIG_BINARY_FRAME_X_START;
	lRec.PS.Y = CONFIG_BINARY_FRAME_Y_START;
	lRec.PE.X = CONFIG_BINARY_FRAME_X_END;
	lRec.PE.Y = CONFIG_BINARY_FRAME_Y_END;
	DisRecFramSet(&lRec);

	uint8_t lI;
	S_Lcd__Item_Mid lTrig;
	// 显示全部的标签
	for (lI = 0; lI < STR_NUM(sInputOnOffEn); lI++)
	{
		lTrig.Item.Pos = CONFIG_INPUT_ONOFF_POS + lI;
//		lTrig.Item.Char = *(gInputBinary[lLang] + lI);
		lTrig.Item.Char = *(*(*(gInputBinary + lpInput->State) + lLang) + lI);
		lTrig.Len = CONFIG_INPUT_LEN;
		Lcd__FrameItemMidDisp(&lTrig);
	}



	StateInputBinaryDispInit();
}


/**
 * @brief   菜单项最终处理确认
 */
static void StateInputBinaryConfirm(void)
{
	if (sBinary.Line.Index == 0)
	{
		sBinary.Func.Save(TURN_ON);
		sBinary.Func.Confirm(TURN_ON);
	}
	else
	{
		sBinary.Func.Save(TURN_OFF);
		sBinary.Func.Confirm(TURN_OFF);
	}

//	StateInputToMenu();
}


/**
 * @brief   菜单项最终处理退出
 */
static void StateInputBinaryExit(void)
{
	StateInputToMenu();
}


/**
 * @brief   菜单项向下按键
 */
static void StateInputBinaryDown(void)
{
	Lcd__FrameItemRev(CONFIG_INPUT_ONOFF_POS + sBinary.Line.Index);

	sBinary.Line.Index++;

	if (sBinary.Line.Index >= sBinary.Line.Num)
	{
		// 这个是不能循环显示
		//sBinary.Line.Index--;
		// 循环显示
		sBinary.Line.Index = 0;
	}

	Lcd__FrameItemRev(CONFIG_INPUT_ONOFF_POS + sBinary.Line.Index);
}


/**
 * @brief   菜单项向上按键
 */
static void StateInputBinaryUp(void)
{
	Lcd__FrameItemRev(CONFIG_INPUT_ONOFF_POS + sBinary.Line.Index);

	if (sBinary.Line.Index > 0)
	{
		// 这个是不能循环显示
		//sBinary.Line.Index = 0;
		// 循环显示
		sBinary.Line.Index--;
	}
	else
	{
		sBinary.Line.Index = sBinary.Line.Num - 1;
	}
	Lcd__FrameItemRev(CONFIG_INPUT_ONOFF_POS + sBinary.Line.Index);
}



// 菜单对应的按键函数
static const S_State_Input_Tab sStateInputTab[] =
{
		STATE_INPUT_KEY_TAB(VALUE, Value),
		STATE_INPUT_KEY_TAB(BINARY, Binary),
};


/**
 * @brief   按键 调用函数
 */
void StateInputKey(uint8_t lKey)
{
	switch (lKey)
	{
		case KEY_DOWN:
			sStateInputTab[sStateInputNow.InputIndex].Down();
			break;

		case KEY_UP:
			sStateInputTab[sStateInputNow.InputIndex].Up();
			break;

		case KEY_ENTER:
			sStateInputTab[sStateInputNow.InputIndex].Confirm();
			break;

		case KEY_SPECIAL:
			sStateInputTab[sStateInputNow.InputIndex].Exit();
			break;

		default:
			break;
	}
}
