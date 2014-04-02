/**
 * @file    menu_rst_param.c
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

#include "menu_rst_param_in.h"

// 菜单的菜单项 英文
const char *sMenuRestoreParamTxtItemEn[] =
{
		"Param",
		"Cali",
};

// 菜单的菜单项 中文
const char *sMenuRestoreParamTxtItemCn[] =
{
		"param",
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
const char **sMenuRestoreParamTxtItem[] =
{
		sMenuRestoreParamTxtItemEn,
		sMenuRestoreParamTxtItemCn,
};

// 菜单自身名字 英文
const char sMenuRestoreParamTxtSelfEn[] = "Param";

// 菜单自身名字 中文
const char sMenuRestoreParamTxtSelfCn[] = "param";

// 菜单自身名字
const char *sMenuRestoreParamTxtSelf[] =
{
		sMenuRestoreParamTxtSelfEn,
		sMenuRestoreParamTxtSelfCn,
};

// 菜单的子菜单索引
const menu_t sMenuRestoreParamChild[] =
{
		MENU_RESTORE_INDEX,
};

// 菜单的子菜单资源
const struct S_MenuResource *sMenuRsrRestoreParamChild[] =
{
		&gMenuRsrRestoreParam,
};

// 菜单 资源，包括自身字符串，菜单项字符串，菜单项的数目
const struct S_MenuResource gMenuRsrRestoreParam =
{
	MENU_RESOURCE(sMenuRestoreParamTxtItemEn,
					sMenuRestoreParamChild,
					sMenuRsrRestoreParamChild,
					sMenuRestoreParamTxtSelf,
					sMenuRestoreParamTxtItem)
};


/**
 * @brief   菜单初始化
 */
void MenuRestoreParamPreInit(void)
{
}


/**
 * @brief   菜单初始化
 */
void MenuRestoreParamInit(void)
{
}


/**
 * @brief   进入子菜单
 */
void MenuRestoreParamChild(void)
{
	MenuKeyChild();
//	MenuChildInit();
	MenuDisp();
}


/**
 * @brief   进入父菜单
 */
void MenuRestoreParamParent(void)
{
	MenuKeyParent();
	MenuDisp();
}


/**
 * @brief   下一条菜单项
 */
void MenuRestoreParamNext(void)
{
	MenuKeyNext();

}


/**
 * @brief   上一条菜单项
 */
void MenuRestoreParamPrev(void)
{
	MenuKeyPrev();
}
