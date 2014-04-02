/**
 * @file    menu_debug.c
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

#include "menu_debug_in.h"

// 菜单的菜单项 英文
const char *sMenuDebugTxtItemEn[] =
{
		"Zero",
		"Coefficient",
		"Reference 1",
		"Reference 2",
		"Build Date",
};

// 菜单的菜单项 中文
const char *sMenuDebugTxtItemCn[] =
{
		"zero",
		"coeff",
		"Ref1",
		"Ref2",
		"build",
	//		"查看零点",
	//		"查看系数",
		//	"查看参考点1",
	//		"查看参考点2",
		//	"查看编译时间",
};

// 菜单的菜单项 指针数组
const char **sMenuDebugTxtItem[] =
{
		sMenuDebugTxtItemEn,
		sMenuDebugTxtItemCn,
};

// 菜单自身名字 英文
const char sMenuDebugTxtSelfEn[] = "Debug";

// 菜单自身名字 中文
const char sMenuDebugTxtSelfCn[] = "debug";

// 菜单自身名字
const char *sMenuDebugTxtSelf[] =
{
		sMenuDebugTxtSelfEn,
		sMenuDebugTxtSelfCn,
};

// 菜单的子菜单索引
const menu_t sMenuDebugChild[] =
{
		MENU_DEBUG_ZERO_INDEX,
		MENU_DEBUG_COEFF_INDEX,
		MENU_DEBUG_REF1_INDEX,
		MENU_DEBUG_REF2_INDEX,
		MENU_DEBUG_BUILD_INDEX,
};

// 菜单的子菜单资源
const struct S_MenuResource *sMenuRsrDebugChild[] =
{
		&gMenuRsrDebugZero,
		&gMenuRsrDebugCoeff,
		&gMenuRsrDebugRef1,
		&gMenuRsrDebugRef2,
		&gMenuRsrDebugBuild,
};

// 菜单 资源，包括自身字符串，菜单项字符串，菜单项的数目
const struct S_MenuResource gMenuRsrDebug =
{
	MENU_RESOURCE(sMenuDebugTxtItemEn,
					sMenuDebugChild,
					sMenuRsrDebugChild,
					sMenuDebugTxtSelf,
					sMenuDebugTxtItem)
};


/**
 * @brief   菜单初始化
 */
void MenuDebugPreInit(void)
{
}


/**
 * @brief   菜单初始化
 */
void MenuDebugInit(void)
{
}


/**
 * @brief   进入子菜单
 */
void MenuDebugChild(void)
{
	MenuKeyChild();
	MenuDisp();
}


/**
 * @brief   进入父菜单
 */
void MenuDebugParent(void)
{
	MenuKeyParent();
	MenuDisp();
}


/**
 * @brief   下一条菜单项
 */
void MenuDebugNext(void)
{
	MenuKeyNext();

}


/**
 * @brief   上一条菜单项
 */
void MenuDebugPrev(void)
{
	MenuKeyPrev();
}
