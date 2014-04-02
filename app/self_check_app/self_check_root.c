/**
 * @file    self_check_root.c
 * @brief   根自检
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

#include "self_check_root_in.h"

// 根自检的自检项 英文
const char *sSelfCheckRootTxtEn[] =
{
		"Product Name",
		"Gas Detector",
};

// 根自检的自检项 中文
const char *sSelfCheckRootTxtCn[] =
{
		"产品名称",
		"气体检测仪",
};

// 根自检的自检项 指针数组
const char **sSelfCheckRootTxt[] =
{
		sSelfCheckRootTxtEn,
		sSelfCheckRootTxtCn,
};


// 根自检的下一个自检资源
const struct S_SelfCheckResource* sSelfCheckRsrRootNext =
											&gSelfCheckRsrRoot;

// 根自检 资源，包括自身字符串，自检项字符串，自检项的数目
const struct S_SelfCheckResource gSelfCheckRsrRoot =
{
//		SELF_CHECK_RESOURCE(sSelfCheckRootTxtItemEn,
//						sSelfCheckRootChild,
//						sSelfCheckRsrRootChild,
//						sSelfCheckRootTxtSelf,
//						sSelfCheckRootTxtItem)

		SELF_CHECK_RESOURCE(ROOT, Root, Sample)

//		SELF_CHECK_ROOT_INDEX,
//		sSelfCheckRootTxt,

//		sSelfCheckRsrRootNext,
//		&gSelfCheckRsrRoot,

//		STR_NUM(sSelfCheckRootTxtEn),
//		&gSelfCheckRsrSample,

};


/**
 * @brief   自检初始化
 */
void SelfCheckRootInit(void)
{
	// 根自检资源初始化
	SelfCheckInit();
	SelfCheckJumpInit();
	DisClr();
	SelfCheckFrameDisp();
	SelfCheckDisp();

//	static uint8_t sSelfCheckRootCount = 0;
//
//	if (sSelfCheckRootCount < 2) && ()
//	{
//
//	}
//
//	S_Led lLed;
//
//	lLed.Src = LED_POWER_ON;
//	lLed.Time = LED_POWER_ON_TIME;
//	lLed.Pin = LED_PIN_1,
//	LedOn(&lLed);
//
//	S_Buzzer lBz;
//
//	lBz.Src = BUZZER_POWER_ON;
//	lBz.Time = BUZZER_POWER_ON_TIME;
//	BuzzerOn(&lBz);
//
//	S_Vibration lVbr;
//
//	lVbr.Src = VIBRATION_POWER_ON;
//	lVbr.Time = VIBRATION_POWER_ON_TIME;
//	VibrationOn(&lVbr);
}

