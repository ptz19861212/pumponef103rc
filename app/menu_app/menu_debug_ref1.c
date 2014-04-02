/**
 * @file    menu_debug_ref1.c
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

#include "menu_debug_ref1_in.h"

// 菜单的菜单项 英文
const char *sMenuDebugRef1TxtItemEn[] =
{
		"Ref1",
		"Coefficient",
		"Reference 1",
		"Reference 2",
		"Build Date",
};

// 菜单的菜单项 中文
const char *sMenuDebugRef1TxtItemCn[] =
{
		"ref1",
		"coeff",
		"Ref1",
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
const char **sMenuDebugRef1TxtItem[] =
{
		sMenuDebugRef1TxtItemEn,
		sMenuDebugRef1TxtItemCn,
};

// 菜单自身名字 英文
const char sMenuDebugRef1TxtSelfEn[] = "Ref1";

// 菜单自身名字 中文
const char sMenuDebugRef1TxtSelfCn[] = "ref1";

// 菜单自身名字
const char *sMenuDebugRef1TxtSelf[] =
{
		sMenuDebugRef1TxtSelfEn,
		sMenuDebugRef1TxtSelfCn,
};

// 菜单的子菜单索引
const menu_t sMenuDebugRef1Child[] =
{
		MENU_DEBUG_INDEX,
};

// 菜单的子菜单资源
const struct S_MenuResource *sMenuRsrDebugRef1Child[] =
{
		&gMenuRsrDebugRef1,
};

// 菜单 资源，包括自身字符串，菜单项字符串，菜单项的数目
const struct S_MenuResource gMenuRsrDebugRef1 =
{
	MENU_RESOURCE(sMenuDebugRef1TxtItemEn,
					sMenuDebugRef1Child,
					sMenuRsrDebugRef1Child,
					sMenuDebugRef1TxtSelf,
					sMenuDebugRef1TxtItem)
};


/**
 * @brief   菜单初始化
 */
void MenuDebugRef1PreInit(void)
{
}


/**
 * @brief   菜单初始化
 */
void MenuDebugRef1Init(void)
{
}


/**
 * @brief   进入子菜单
 */
void MenuDebugRef1Child(void)
{
	MenuKeyChild();
	MenuDisp();
}


/**
 * @brief   进入父菜单
 */
void MenuDebugRef1Parent(void)
{
	MenuKeyParent();
	MenuDisp();
}


/**
 * @brief   下一条菜单项
 */
void MenuDebugRef1Next(void)
{
	MenuKeyNext();

}


/**
 * @brief   上一条菜单项
 */
void MenuDebugRef1Prev(void)
{
	MenuKeyPrev();
}
