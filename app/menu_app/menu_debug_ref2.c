/**
 * @file    menu_debug_ref2.c
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

#include "menu_debug_ref2_in.h"

// 菜单的菜单项 英文
const char *sMenuDebugRef2TxtItemEn[] =
{
		"Ref2",
		"Coefficient",
		"Reference 1",
		"Reference 2",
		"Build Date",
};

// 菜单的菜单项 中文
const char *sMenuDebugRef2TxtItemCn[] =
{
		"ref2",
		"coeff",
		"Ref2",
		"Ref2",
		"build",
	//		"参数设置",
	//		"气体校准",
		//	"时间设定",
	//		"恢复出厂",
		//	"生产时间",
		//	"内部调试",
	//		"用户权限",
};

// 菜单的菜单项 指针数组
const char **sMenuDebugRef2TxtItem[] =
{
		sMenuDebugRef2TxtItemEn,
		sMenuDebugRef2TxtItemCn,
};

// 菜单自身名字 英文
const char sMenuDebugRef2TxtSelfEn[] = "Ref2";

// 菜单自身名字 中文
const char sMenuDebugRef2TxtSelfCn[] = "ref2";

// 菜单自身名字
const char *sMenuDebugRef2TxtSelf[] =
{
		sMenuDebugRef2TxtSelfEn,
		sMenuDebugRef2TxtSelfCn,
};

// 菜单的子菜单索引
const menu_t sMenuDebugRef2Child[] =
{
		MENU_DEBUG_INDEX,
};

// 菜单的子菜单资源
const struct S_MenuResource *sMenuRsrDebugRef2Child[] =
{
		&gMenuRsrDebugRef2,
};

// 菜单 资源，包括自身字符串，菜单项字符串，菜单项的数目
const struct S_MenuResource gMenuRsrDebugRef2 =
{
	MENU_RESOURCE(sMenuDebugRef2TxtItemEn,
					sMenuDebugRef2Child,
					sMenuRsrDebugRef2Child,
					sMenuDebugRef2TxtSelf,
					sMenuDebugRef2TxtItem)
};


/**
 * @brief   菜单初始化
 */
void MenuDebugRef2PreInit(void)
{
}


/**
 * @brief   菜单初始化
 */
void MenuDebugRef2Init(void)
{
}


/**
 * @brief   进入子菜单
 */
void MenuDebugRef2Child(void)
{
	MenuKeyChild();
	MenuDisp();
}


/**
 * @brief   进入父菜单
 */
void MenuDebugRef2Parent(void)
{
	MenuKeyParent();
	MenuDisp();
}


/**
 * @brief   下一条菜单项
 */
void MenuDebugRef2Next(void)
{
	MenuKeyNext();

}


/**
 * @brief   上一条菜单项
 */
void MenuDebugRef2Prev(void)
{
	MenuKeyPrev();
}
