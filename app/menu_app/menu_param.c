/**
 * @file    menu_param.c
 * @brief   根菜单
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

#include "menu_param_in.h"

// 菜单的菜单项 英文
const char *sMenuParamTxtItemEn[] =
{
		"Alarm",
		"Upper Alarm",
		"Lower Alarm",

#if ((CONFIG_GAS != GAS_O2) && (CONFIG_GAS != GAS_EX))
		"Stel",
		"Twa",
#endif

		// 注意 language 所在的位置，因为下面 child中有相关联的地方
//		"Pump",
//		"Bak Gap",
		"Language",
};

// 菜单的菜单项 中文
const char *sMenuParamTxtItemCn[] =
{
//		"alarm",
//		"upper",
//		"lower",

			"报警设置",
			"高级报警",
			"低级报警",

#if ((CONFIG_GAS != GAS_O2) && (CONFIG_GAS != GAS_EX))
//		"stel",
//		"twa",
			"短时报警",
			"长时报警",
#endif

//		"pump",
//		"bak",
//		"language",
//			"泵吸设置",
//			"备份间隔设置",
			"语言设置",
};

// 菜单的菜单项 指针数组
const char **sMenuParamTxtItem[] =
{
		sMenuParamTxtItemEn,
		sMenuParamTxtItemCn,
};

// 菜单自身名字 英文
const char sMenuParamTxtSelfEn[] = "Param";

// 菜单自身名字 中文
const char sMenuParamTxtSelfCn[] = "参数";

// 菜单自身名字
const char *sMenuParamTxtSelf[] =
{
		sMenuParamTxtSelfEn,
		sMenuParamTxtSelfCn,
};

// 菜单的子菜单索引
const menu_t sMenuParamChild[] =
{
		MENU_PARAM_ALARM_INDEX,
		MENU_PARAM_UPPER_INDEX,
		MENU_PARAM_LOWER_INDEX,

#if ((CONFIG_GAS != GAS_O2) && (CONFIG_GAS != GAS_EX))
		MENU_PARAM_STEL_INDEX,
		MENU_PARAM_TWA_INDEX,
#endif

//		MENU_PARAM_PUMP_INDEX,
//		MENU_PARAM_BAK_INDEX,
		MENU_PARAM_LANGUAGE_INDEX,
};

// 菜单的子菜单资源
const struct S_MenuResource *sMenuRsrParamChild[] =
{
		&gMenuRsrParamAlarm,
//		(const struct S_MenuResource*)&gMenuRsrParamUpper,
		&gMenuRsrParamUpper,
//		(const struct S_MenuResource*)&gMenuRsrParamLower,
		&gMenuRsrParamLower,

#if ((CONFIG_GAS != GAS_O2) && (CONFIG_GAS != GAS_EX))
//		(const struct S_MenuResource*)&gMenuRsrParamStel,
		&gMenuRsrParamStel,
//		(const struct S_MenuResource*)&gMenuRsrParamTwa,
		&gMenuRsrParamTwa,
#endif

//		&gMenuRsrParamPump,
//		&gMenuRsrParamBak,
		&gMenuRsrParamLanguage,
};

// 菜单 资源，包括自身字符串，菜单项字符串，菜单项的数目
const struct S_MenuResource gMenuRsrParam =
{
	MENU_RESOURCE(sMenuParamTxtItemEn,
					sMenuParamChild,
					sMenuRsrParamChild,
					sMenuParamTxtSelf,
					sMenuParamTxtItem)
};

/**
 * @brief   菜单初始化
 */
void MenuParamPreInit(void)
{
}


/**
 * @brief   菜单初始化
 */
void MenuParamInit(void)
{
}


/**
 * @brief   进入子菜单
 */
void MenuParamChild(void)
{
//	menu_t lItem;

//	MenuItemGet(&lItem);

//	if (lItem == 0)
//	{
		MenuKeyChild();
		MenuLoadPreInit();
		MenuDisp();
		MenuLoadInit();
//	}
//	else
//	{
//		MenuDisposeEntry();
//		MenuDisposeDisp();
//		MenuDisposeChildInit();
//	}
}


/**
 * @brief   进入父菜单
 */
void MenuParamParent(void)
{
	MenuKeyParent();
	MenuDisp();
}


/**
 * @brief   下一条菜单项
 */
void MenuParamNext(void)
{
	MenuKeyNext();

}


/**
 * @brief   上一条菜单项
 */
void MenuParamPrev(void)
{
	MenuKeyPrev();
}
