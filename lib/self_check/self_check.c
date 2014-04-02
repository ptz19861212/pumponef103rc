/**
 * @file    self_check.c
 * @brief   自检 框架代码
 * @author  ptz
 * @email   ptz19861212@163.com
 * @version 0.0.1
 * @date    2013-12-01 18:50:09 星期日 
 * @history (1).2013-12-01 18:50:09 星期日 create
 */
/* Copyright (C)
 * 
 * My own license
 * All right reserved
 * 
 */

#include "self_check_in.h"


// 当前的自检内容
S_SelfCheckFrame sSelfCheck;

// 当前的语言
static E_Language sLang;


/**
 * @brief   自检项语言初始化
 */
void SelfCheckLangInit(void)
{
//	E_Language lLang;
	sLang = Lcd__LangGet();
//	sSelfCheckDisp.TextItem = *((sSelfCheckFrame.SelfCheckRsr->ItemText) + lLang);
//	sSelfCheckDisp.TextSelf = *(sSelfCheckFrame.SelfCheckRsr->SelfText + lLang);
}


/**
 * @brief   自检加载资源
 */
void SelfCheckLoad(void)
{
	sSelfCheck.Index = sSelfCheck.SelfCheckRsr->Index;
	sSelfCheck.Text = *(sSelfCheck.SelfCheckRsr->Text + sLang);
}


/**
 * @brief   自检初始化
 */
void SelfCheckInit(void)
{
	SelfCheckLangInit();
	sSelfCheck.SelfCheckRsr = &gSelfCheckRsrRoot;
	SelfCheckLoad();
}


/**
 * @brief   自检显示
 */
void SelfCheckDisp(void)
{
	// 清屏
//	DisClr();

	uint8_t lI;
	S_Lcd__Item_Mid lTrig;

	// 显示全部的标签
//	for (lI = 0; lI < STR_NUM(sResultExitSucEn); lI++)
//	for (lI = 0; lI < STR_NUM(sSelfCheck.Text); lI++)
	for (lI = 0; lI < sSelfCheck.SelfCheckRsr->Num; lI++)
	{
		lTrig.Item.Pos = CONFIG_SELF_CHECK_POS + lI;
		lTrig.Item.Char = *(sSelfCheck.Text + lI);
		lTrig.Len = CONFIG_SELF_CHECK_LEN;
		Lcd__FrameItemMidDisp(&lTrig);
	}
}


/**
 * @brief   获取当前的自检项是那一条
 *
 * @param   lpItem 地址
 */
self_check_t SelfCheckIndexGet(void)
{
	return sSelfCheck.Index;
}


/**
 * @brief   自检显示框架
 */
void SelfCheckFrameDisp(void)
{
	// 画框架
	S_Lcd_Area_RectangleShade lRec;
	lRec.Ex.X = CONFIG_SELF_CHECK_FRAME_EX_X;
	lRec.Ex.Y = CONFIG_SELF_CHECK_FRAME_EX_Y;
	lRec.PS.X = CONFIG_SELF_CHECK_FRAME_X_START;
	lRec.PS.Y = CONFIG_SELF_CHECK_FRAME_Y_START;
	lRec.PE.X = CONFIG_SELF_CHECK_FRAME_X_END;
	lRec.PE.Y = CONFIG_SELF_CHECK_FRAME_Y_END;
	DisRecFramSet(&lRec);
}


/*********************************** 按键部分 ********************************/
/**
 * @brief   自检处理的进入初始化
 */
void SelfCheckSpecificDisp(void)
{
	// 初始化
	gSelfCheckTab[sSelfCheck.Index].Init();
}


/**
 * @brief   自检跳转下一个
 */
void SelfCheckNext(void)
{
	sSelfCheck.SelfCheckRsr = sSelfCheck.SelfCheckRsr->Next;
	SelfCheckLoad();
	SelfCheckDisp();
	SelfCheckSpecificDisp();
}



// 秒
static my_second_t sSelfCheckSecond;
// 秒内的计数，这个是为了整秒，不然第一秒长短不一
static uint8_t sSelfCheckCount;

/**
 * @brief   自检画面跳转的初始化
 */
void SelfCheckJumpInit(void)
{
	S_Device* lpDev;
	StateDevicePointGet(&lpDev);

	sSelfCheckSecond = lpDev->pTemp->Time.Sec;
	sSelfCheckCount = lpDev->pTemp->Time.Count;
}



/**
 * @brief   自检画面是否跳转的测试
 */
void SelfCheckJumpCheck(void)
{
	S_Device* lpDev;
	StateDevicePointGet(&lpDev);

	// 为了整秒
	if (lpDev->pTemp->Time.Count != sSelfCheckCount)
	{
		return;
	}

	PowerSaveBglFresh();

	if (lpDev->pTemp->Time.Sec > (sSelfCheckSecond + 2))
	{
		SelfCheckNext();
		sSelfCheckSecond = lpDev->pTemp->Time.Sec;
	}
}





