/**
 * @file    self_check_sample.c
 * @brief   采样自检
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

#include "self_check_sample_in.h"

// 采样自检的自检项 英文
const char *sSelfCheckSampleTxtEn[] =
{
		"Sample Type",
		"inhaled",
};

// 采样自检的自检项 中文
const char *sSelfCheckSampleTxtCn[] =
{
		"采样类型",
		"泵吸式",
};

// 采样自检的自检项 指针数组
const char **sSelfCheckSampleTxt[] =
{
		sSelfCheckSampleTxtEn,
		sSelfCheckSampleTxtCn,
};


// 采样自检的下一个自检资源
const struct S_SelfCheckResource* sSelfCheckRsrSampleNext =
											&gSelfCheckRsrSample;

// 采样自检 资源，包括自身字符串，自检项字符串，自检项的数目
const struct S_SelfCheckResource gSelfCheckRsrSample =
{
//		SELF_CHECK_RESOURCE(sSelfCheckSampleTxtItemEn,
//						sSelfCheckSampleChild,
//						sSelfCheckRsrSampleChild,
//						sSelfCheckSampleTxtSelf,
//						sSelfCheckSampleTxtItem)
//		SELF_CHECK_SAMPLE_INDEX,
//		sSelfCheckSampleTxt,
////		sSelfCheckRsrSampleNext,
//		&gSelfCheckRsrSample,
//
		SELF_CHECK_RESOURCE(SAMPLE, Sample, Version)
};


/**
 * @brief   自检初始化
 */
void SelfCheckSampleInit(void)
{
	// 采样自检资源初始化
//	SelfCheckInit();
//	SelfCheckJumpInit();
//	DisClr();
//	SelfCheckFrameDisp();
//	SelfCheckDisp();

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

