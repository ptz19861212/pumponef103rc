/**
 * @file    menu_manuf.c
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

#include "menu_manuf_in.h"

// 菜单的菜单项 英文
const char *sMenuManufTxtItemEn[] =
{
		"Manuf Time"
};

// 菜单的菜单项 中文
const char *sMenuManufTxtItemCn[] =
{
		"manuf"
};

// 菜单的菜单项 指针数组
const char **sMenuManufTxtItem[] =
{
		sMenuManufTxtItemEn,
		sMenuManufTxtItemCn,
};

// 菜单自身名字 英文
const char sMenuManufTxtSelfEn[] = "Manuf";

// 菜单自身名字 中文
const char sMenuManufTxtSelfCn[] = "manuf";

// 菜单自身名字
const char *sMenuManufTxtSelf[] =
{
		sMenuManufTxtSelfEn,
		sMenuManufTxtSelfCn,
};

// 菜单的子菜单索引
const menu_t sMenuManufChild[] =
{
		MENU_MANUF_INDEX,
};

// 菜单的子菜单资源
const struct S_MenuResource *sMenuRsrManufChild[] =
{
		&gMenuRsrManuf,
};

// 菜单 资源，包括自身字符串，菜单项字符串，菜单项的数目
const struct S_MenuResource gMenuRsrManuf =
{
	MENU_RESOURCE(sMenuManufTxtItemEn,
					sMenuManufChild,
					sMenuRsrManufChild,
					sMenuManufTxtSelf,
					sMenuManufTxtItem)
};


/**
 * @brief   菜单初始化
 */
void MenuManufPreInit(void)
{
}


/**
 * @brief   菜单初始化
 */
void MenuManufInit(void)
{
}


/**
 * @brief   进入子菜单
 */
void MenuManufChild(void)
{
	MenuKeyChild();
	MenuDisp();
}


/**
 * @brief   进入父菜单
 */
void MenuManufParent(void)
{
	MenuKeyParent();
	MenuDisp();
}


/**
 * @brief   下一条菜单项
 */
void MenuManufNext(void)
{
	MenuKeyNext();

}


/**
 * @brief   上一条菜单项
 */
void MenuManufPrev(void)
{
	MenuKeyPrev();
}
