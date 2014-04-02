/**
 * @file    menu_param_language.c
 * @brief   语言菜单
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

#include "menu_param_language_in.h"

// 菜单的菜单项 英文
const char *sMenuParamLanguageTxtItemEn[] =
{
		"English",
		"简体中文",
//		"Chinese",
};

// 菜单的菜单项 中文
const char *sMenuParamLanguageTxtItemCn[] =
{
		"English",
		"简体中文",
//		"english",
//		"chinese",
		//	"英文",
	//		"中文",
};

// 菜单的菜单项 指针数组
const char **sMenuParamLanguageTxtItem[] =
{
		sMenuParamLanguageTxtItemEn,
		sMenuParamLanguageTxtItemCn,
};

// 菜单自身名字 英文
const char sMenuParamLanguageTxtSelfEn[] = "Lang";

// 菜单自身名字 中文
const char sMenuParamLanguageTxtSelfCn[] = "语言";

// 菜单自身名字
const char *sMenuParamLanguageTxtSelf[] =
{
		sMenuParamLanguageTxtSelfEn,
		sMenuParamLanguageTxtSelfCn,
};

// 菜单的子菜单索引
const menu_t sMenuParamLanguageChild[] =
{
		MENU_PARAM_ALARM_INDEX,
};

// 菜单的子菜单资源
const struct S_MenuResource *sMenuRsrParamLanguageChild[] =
{
		&gMenuRsrParamLanguage,
};

// 菜单 资源，包括自身字符串，菜单项字符串，菜单项的数目
const struct S_MenuResource gMenuRsrParamLanguage =
{
	MENU_RESOURCE(sMenuParamLanguageTxtItemEn,
					sMenuParamLanguageChild,
					sMenuRsrParamLanguageChild,
					sMenuParamLanguageTxtSelf,
					sMenuParamLanguageTxtItem)
};


/**
 * @brief   菜单预先初始化
 */
void MenuParamLanguagePreInit(void)
{
	E_Language lLang;

	// 获得当前显示的语言
	lLang = Lcd__LangGet();

	MenuItemSet(lLang);
}


/**
 * @brief   菜单初始化
 */
void MenuParamLanguageInit(void)
{
//	E_Language lLang;
//
//	// 获得当前显示的语言
//	lLang = Lcd__LangGet();
//	rt_kprintf("lang = %d\n", lLang);
//
//	MenuItemSet(lLang);
}


/**
 * @brief   输入函数保存的数值提取获得，用于初次进入的数值显示
 */
void MenuParamLanguageBinaryGet(E_TurnState* lpState)
{
//	struct S_Device* lpDev;
//	StateDevicePointGet(&lpDev);

//	*lpState = lpDev->pSave->Vibration;

	E_Language lLang;

	// 获得当前显示的语言
	lLang = Lcd__LangGet();

	menu_t lItem;

	MenuItemGet(&lItem);

	if (lLang == lItem)
	{
		*lpState = TURN_ON;
	}
	else
	{
		*lpState = TURN_OFF;
	}

//	*lpState = Lcd__LangGet();
}

static E_Language sParamLangOld;

/**
 * @brief   输入函数数值保存
 */
void MenuParamLanguageSave(E_TurnState lTurn)
{
	S_Device* lpDev;
	StateDevicePointGet(&lpDev);

	if (lTurn == TURN_ON)
	{
		menu_t lItem;

		MenuItemGet(&lItem);
		lpDev->pSave->Language = lItem;
		lpDev->pSave->Save_Bits.Lang = FLASH_SAVE_TRUE;

		Lcd__LangSet(lItem);
		MenuLangInit();
	}
	else
	{
		Lcd__LangSet(sParamLangOld);
	}

//	StateInputToMenu();
}


/**
 * @brief   输入函数数值保存
 */
void MenuParamLanguageConfirm(E_TurnState lTurn)
{
	StateInputToMenu();
}


/**
 * @brief   进入子菜单
 */
void MenuParamLanguageChild(void)
{
//	MenuKeyChild();
//	MenuDisp();
	S_InputBinary lInput;

//	struct S_Device* lpDev;
//	StateDevicePointGet(&lpDev);

	lInput.Func.BinaryGet = MenuParamLanguageBinaryGet;
	lInput.Func.Save = MenuParamLanguageSave;
	lInput.Func.Confirm = MenuParamLanguageConfirm;
	lInput.State = BINARY_YESNO;
	// 保存当前语言
	sParamLangOld = Lcd__LangGet();

	// 使用新的语言进行是否的选择
	menu_t lItem;
	MenuItemGet(&lItem);

	if (lItem == 0)
	{
		Lcd__LangSet(LANGUAGE_EN);
	}
	else
	{
		Lcd__LangSet(LANGUAGE_CN);
	}

	StateInputBinaryInit(&lInput);
	StateMenuToInput();
}


/**
 * @brief   进入父菜单
 */
void MenuParamLanguageParent(void)
{
	MenuKeyParent();
	MenuDisp();
}


/**
 * @brief   下一条菜单项
 */
void MenuParamLanguageNext(void)
{
	MenuKeyNext();

}


/**
 * @brief   上一条菜单项
 */
void MenuParamLanguagePrev(void)
{
	MenuKeyPrev();
}
