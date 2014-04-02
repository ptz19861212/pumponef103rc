/**
 * @file    menu_debug_build.c
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

#include "menu_debug_build_in.h"

// 菜单的菜单项 英文
const char *sMenuDebugBuildTxtItemEn[] =
{
		"Build",
		"Coefficient",
		"Reference 1",
		"Reference 2",
		"Build Date",
};

// 菜单的菜单项 中文
const char *sMenuDebugBuildTxtItemCn[] =
{
		"build",
		"coeff",
		"Build",
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
const char **sMenuDebugBuildTxtItem[] =
{
		sMenuDebugBuildTxtItemEn,
		sMenuDebugBuildTxtItemCn,
};

// 菜单自身名字 英文
const char sMenuDebugBuildTxtSelfEn[] = "Build";

// 菜单自身名字 中文
const char sMenuDebugBuildTxtSelfCn[] = "build";

// 菜单自身名字
const char *sMenuDebugBuildTxtSelf[] =
{
		sMenuDebugBuildTxtSelfEn,
		sMenuDebugBuildTxtSelfCn,
};

// 菜单的子菜单索引
const menu_t sMenuDebugBuildChild[] =
{
		MENU_DEBUG_INDEX,
};

// 菜单的子菜单资源
const struct S_MenuResource *sMenuRsrDebugBuildChild[] =
{
		&gMenuRsrDebugBuild,
};

// 菜单 资源，包括自身字符串，菜单项字符串，菜单项的数目
const struct S_MenuResource gMenuRsrDebugBuild =
{
	MENU_RESOURCE(sMenuDebugBuildTxtItemEn,
					sMenuDebugBuildChild,
					sMenuRsrDebugBuildChild,
					sMenuDebugBuildTxtSelf,
					sMenuDebugBuildTxtItem)
};


/**
 * @brief   菜单初始化
 */
void MenuDebugBuildPreInit(void)
{
}


/**
 * @brief   菜单初始化
 */
void MenuDebugBuildInit(void)
{
}


/**
 * @brief   进入子菜单
 */
void MenuDebugBuildChild(void)
{
	MenuKeyChild();
	MenuDisp();
}


/**
 * @brief   进入父菜单
 */
void MenuDebugBuildParent(void)
{
	MenuKeyParent();
	MenuDisp();
}


/**
 * @brief   下一条菜单项
 */
void MenuDebugBuildNext(void)
{
	MenuKeyNext();

}


/**
 * @brief   上一条菜单项
 */
void MenuDebugBuildPrev(void)
{
	MenuKeyPrev();
}
