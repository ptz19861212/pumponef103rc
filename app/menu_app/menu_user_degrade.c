/**
 * @file    menu_user_degrade.c
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

#include "menu_user_degrade_in.h"

// 菜单的菜单项 英文
const char *sMenuUserDegradeTxtItemEn[] =
{
		"UserDegrade"
};

// 菜单的菜单项 中文
const char *sMenuUserDegradeTxtItemCn[] =
{
		"user_degrade"
	//		"参数设置",
	//		"气体校准",
		//	"时间设定",
	//		"恢复出厂",
		//	"生产时间",
		//	"内部调试",
	//		"用户权限",
};

// 菜单的菜单项 指针数组
const char **sMenuUserDegradeTxtItem[] =
{
		sMenuUserDegradeTxtItemEn,
		sMenuUserDegradeTxtItemCn,
};

// 菜单自身名字 英文
const char sMenuUserDegradeTxtSelfEn[] = "Degrade";

// 菜单自身名字 中文
const char sMenuUserDegradeTxtSelfCn[] = "degrade";

// 菜单自身名字
const char *sMenuUserDegradeTxtSelf[] =
{
		sMenuUserDegradeTxtSelfEn,
		sMenuUserDegradeTxtSelfCn,
};

// 菜单的子菜单索引
const menu_t sMenuUserDegradeChild[] =
{
		MENU_USER_INDEX,
};

// 菜单的子菜单资源
const struct S_MenuResource *sMenuRsrUserDegradeChild[] =
{
		&gMenuRsrUserDegrade,
};

// 菜单 资源，包括自身字符串，菜单项字符串，菜单项的数目
const struct S_MenuResource gMenuRsrUserDegrade =
{
	MENU_RESOURCE(sMenuUserDegradeTxtItemEn,
					sMenuUserDegradeChild,
					sMenuRsrUserDegradeChild,
					sMenuUserDegradeTxtSelf,
					sMenuUserDegradeTxtItem)
};


/**
 * @brief   菜单初始化
 */
void MenuUserDegradePreInit(void)
{
}


/**
 * @brief   菜单初始化
 */
void MenuUserDegradeInit(void)
{
}


/**
 * @brief   进入子菜单
 */
void MenuUserDegradeChild(void)
{
	MenuKeyChild();
	MenuDisp();
}


/**
 * @brief   进入父菜单
 */
void MenuUserDegradeParent(void)
{
	MenuKeyParent();
	MenuDisp();
}


/**
 * @brief   下一条菜单项
 */
void MenuUserDegradeNext(void)
{
	MenuKeyNext();

}


/**
 * @brief   上一条菜单项
 */
void MenuUserDegradePrev(void)
{
	MenuKeyPrev();
}
