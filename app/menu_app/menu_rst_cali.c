/**
 * @file    menu_rst_cali.c
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

#include "menu_rst_cali_in.h"

// 菜单的菜单项 英文
const char *sMenuRestoreCaliTxtItemEn[] =
{
		"Cali",
		"Cali",
};

// 菜单的菜单项 中文
const char *sMenuRestoreCaliTxtItemCn[] =
{
		"cali",
		"cali",
	//		"参数设置",
	//		"气体校准",
		//	"时间设定",
	//		"恢复出厂",
		//	"生产时间",
		//	"内部调试",
	//		"用户权限",
};

// 菜单的菜单项 指针数组
const char **sMenuRestoreCaliTxtItem[] =
{
		sMenuRestoreCaliTxtItemEn,
		sMenuRestoreCaliTxtItemCn,
};

// 菜单自身名字 英文
const char sMenuRestoreCaliTxtSelfEn[] = "Cali";

// 菜单自身名字 中文
const char sMenuRestoreCaliTxtSelfCn[] = "cali";

// 菜单自身名字
const char *sMenuRestoreCaliTxtSelf[] =
{
		sMenuRestoreCaliTxtSelfEn,
		sMenuRestoreCaliTxtSelfCn,
};

// 菜单的子菜单索引
const menu_t sMenuRestoreCaliChild[] =
{
		MENU_RESTORE_INDEX,
};

// 菜单的子菜单资源
const struct S_MenuResource *sMenuRsrRestoreCaliChild[] =
{
		&gMenuRsrRestoreCali,
};

// 菜单 资源，包括自身字符串，菜单项字符串，菜单项的数目
const struct S_MenuResource gMenuRsrRestoreCali =
{
	MENU_RESOURCE(sMenuRestoreCaliTxtItemEn,
					sMenuRestoreCaliChild,
					sMenuRsrRestoreCaliChild,
					sMenuRestoreCaliTxtSelf,
					sMenuRestoreCaliTxtItem)
};


/**
 * @brief   菜单初始化
 */
void MenuRestoreCaliPreInit(void)
{
}


/**
 * @brief   菜单初始化
 */
void MenuRestoreCaliInit(void)
{
}


/**
 * @brief   进入子菜单
 */
void MenuRestoreCaliChild(void)
{
	MenuKeyChild();
	MenuDisp();
}


/**
 * @brief   进入父菜单
 */
void MenuRestoreCaliParent(void)
{
	MenuKeyParent();
	MenuDisp();
}


/**
 * @brief   下一条菜单项
 */
void MenuRestoreCaliNext(void)
{
	MenuKeyNext();

}


/**
 * @brief   上一条菜单项
 */
void MenuRestoreCaliPrev(void)
{
	MenuKeyPrev();
}
