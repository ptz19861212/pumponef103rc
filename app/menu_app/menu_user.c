/**
 * @file    menu_user.c
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

#include "menu_user_in.h"

// 菜单的菜单项 英文
const char *sMenuUserTxtItemEn[] =
{
		"Group",
		"Upgrade",
		"Degrade",
};

// 菜单的菜单项 中文
const char *sMenuUserTxtItemCn[] =
{
		"group",
		"upgrade",
		"degrade",
	//		"用户组",
	//		"升级权限",
		//	"降级权限",
};

// 菜单的菜单项 指针数组
const char **sMenuUserTxtItem[] =
{
		sMenuUserTxtItemEn,
		sMenuUserTxtItemCn,
};

// 菜单自身名字 英文
const char sMenuUserTxtSelfEn[] = "User";

// 菜单自身名字 中文
const char sMenuUserTxtSelfCn[] = "user";

// 菜单自身名字
const char *sMenuUserTxtSelf[] =
{
		sMenuUserTxtSelfEn,
		sMenuUserTxtSelfCn,
};

// 菜单的子菜单索引
const menu_t sMenuUserChild[] =
{
		MENU_USER_GROUP_INDEX,
		MENU_USER_UPGRADE_INDEX,
		MENU_USER_DEGRADE_INDEX,
};

// 菜单的子菜单资源
const struct S_MenuResource *sMenuRsrUserChild[] =
{
		&gMenuRsrUserGroup,
		&gMenuRsrUserUpgrade,
		&gMenuRsrUserDegrade,
};

// 菜单 资源，包括自身字符串，菜单项字符串，菜单项的数目
const struct S_MenuResource gMenuRsrUser =
{
	MENU_RESOURCE(sMenuUserTxtItemEn,
					sMenuUserChild,
					sMenuRsrUserChild,
					sMenuUserTxtSelf,
					sMenuUserTxtItem)
};


/**
 * @brief   菜单初始化
 */
void MenuUserPreInit(void)
{
}


/**
 * @brief   菜单初始化
 */
void MenuUserInit(void)
{
}


/**
 * @brief   进入子菜单
 */
void MenuUserChild(void)
{
	MenuKeyChild();
	MenuDisp();
}


/**
 * @brief   进入父菜单
 */
void MenuUserParent(void)
{
	MenuKeyParent();
	MenuDisp();
}


/**
 * @brief   下一条菜单项
 */
void MenuUserNext(void)
{
	MenuKeyNext();

}


/**
 * @brief   上一条菜单项
 */
void MenuUserPrev(void)
{
	MenuKeyPrev();
}
