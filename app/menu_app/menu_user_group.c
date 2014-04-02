/**
 * @file    menu_user_group.c
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

#include "menu_user_group_in.h"

// 菜单的菜单项 英文
const char *sMenuUserGroupTxtItemEn[] =
{
		"UserGroup"
};

// 菜单的菜单项 中文
const char *sMenuUserGroupTxtItemCn[] =
{
		"user_group"
	//		"参数设置",
	//		"气体校准",
		//	"时间设定",
	//		"恢复出厂",
		//	"生产时间",
		//	"内部调试",
	//		"用户权限",
};

// 菜单的菜单项 指针数组
const char **sMenuUserGroupTxtItem[] =
{
		sMenuUserGroupTxtItemEn,
		sMenuUserGroupTxtItemCn,
};

// 菜单自身名字 英文
const char sMenuUserGroupTxtSelfEn[] = "Group";

// 菜单自身名字 中文
const char sMenuUserGroupTxtSelfCn[] = "group";

// 菜单自身名字
const char *sMenuUserGroupTxtSelf[] =
{
		sMenuUserGroupTxtSelfEn,
		sMenuUserGroupTxtSelfCn,
};

// 菜单的子菜单索引
const menu_t sMenuUserGroupChild[] =
{
		MENU_USER_INDEX,
};

// 菜单的子菜单资源
const struct S_MenuResource *sMenuRsrUserGroupChild[] =
{
		&gMenuRsrUserGroup,
};

// 菜单 资源，包括自身字符串，菜单项字符串，菜单项的数目
const struct S_MenuResource gMenuRsrUserGroup =
{
	MENU_RESOURCE(sMenuUserGroupTxtItemEn,
					sMenuUserGroupChild,
					sMenuRsrUserGroupChild,
					sMenuUserGroupTxtSelf,
					sMenuUserGroupTxtItem)
};


/**
 * @brief   菜单初始化
 */
void MenuUserGroupPreInit(void)
{
}



/**
 * @brief   菜单初始化
 */
void MenuUserGroupInit(void)
{
}


/**
 * @brief   进入子菜单
 */
void MenuUserGroupChild(void)
{
	MenuKeyChild();
	MenuDisp();
}


/**
 * @brief   进入父菜单
 */
void MenuUserGroupParent(void)
{
	MenuKeyParent();
	MenuDisp();
}


/**
 * @brief   下一条菜单项
 */
void MenuUserGroupNext(void)
{
	MenuKeyNext();

}


/**
 * @brief   上一条菜单项
 */
void MenuUserGroupPrev(void)
{
	MenuKeyPrev();
}
