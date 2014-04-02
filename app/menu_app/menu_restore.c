/**
 * @file    menu_restore.c
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

#include "menu_restore_in.h"

// 菜单的菜单项 英文
const char *sMenuRestoreTxtItemEn[] =
{
		"Param",
		"Cali",
};

// 菜单的菜单项 中文
const char *sMenuRestoreTxtItemCn[] =
{
		"param",
		"cali",
	//		"恢复参数",
	//		"恢复校准数值",
};

// 菜单的菜单项 指针数组
const char **sMenuRestoreTxtItem[] =
{
		sMenuRestoreTxtItemEn,
		sMenuRestoreTxtItemCn,
};

// 菜单自身名字 英文
const char sMenuRestoreTxtSelfEn[] = "Restore";

// 菜单自身名字 中文
const char sMenuRestoreTxtSelfCn[] = "restore";

// 菜单自身名字
const char *sMenuRestoreTxtSelf[] =
{
		sMenuRestoreTxtSelfEn,
		sMenuRestoreTxtSelfCn,
};

// 菜单的子菜单索引
const menu_t sMenuRestoreChild[] =
{
		MENU_RST_PARAM_INDEX,
		MENU_RST_CALI_INDEX,
};

// 菜单的子菜单资源
const struct S_MenuResource *sMenuRsrRestoreChild[] =
{
		&gMenuRsrRestoreParam,
		&gMenuRsrRestoreCali,
};

// 菜单 资源，包括自身字符串，菜单项字符串，菜单项的数目
const struct S_MenuResource gMenuRsrRestore =
{
	MENU_RESOURCE(sMenuRestoreTxtItemEn,
					sMenuRestoreChild,
					sMenuRsrRestoreChild,
					sMenuRestoreTxtSelf,
					sMenuRestoreTxtItem)
};


/**
 * @brief   菜单初始化
 */
void MenuRestorePreInit(void)
{
}


/**
 * @brief   菜单初始化
 */
void MenuRestoreInit(void)
{
}


/**
 * @brief   进入子菜单
 */
void MenuRestoreChild(void)
{
	MenuKeyChild();
	MenuDisp();
}


/**
 * @brief   进入父菜单
 */
void MenuRestoreParent(void)
{
	MenuKeyParent();
	MenuDisp();
}


/**
 * @brief   下一条菜单项
 */
void MenuRestoreNext(void)
{
	MenuKeyNext();

}


/**
 * @brief   上一条菜单项
 */
void MenuRestorePrev(void)
{
	MenuKeyPrev();
}
