/**
 * @file    menu_root.c
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

#include "menu_root_in.h"

// 根菜单的菜单项 英文
const char *sMenuRootTxtItemEn[] =
{
		"Parameter",
		"Calibration",
//		"Time",
//		"Restore Factory",
//		"Manufacture",
//		"Debug",
//		"User Right",
};

// 根菜单的菜单项 中文
const char *sMenuRootTxtItemCn[] =
{
//		"param",
//		"cali",
//		"time",
//		"restore",
//		"manuf",
//		"debug",
//		"user",
			"参数设置",
			"气体校准",
		//	"时间设定",
	//		"恢复出厂",
		//	"生产时间",
		//	"内部调试",
	//		"用户权限",
};

// 根菜单的菜单项 指针数组
const char **sMenuRootTxtItem[] =
{
		sMenuRootTxtItemEn,
		sMenuRootTxtItemCn,
};

// 根菜单自身名字 英文
const char sMenuRootTxtSelfEn[] = "Menu";

// 根菜单自身名字 中文
const char sMenuRootTxtSelfCn[] = "菜单";

// 根菜单自身名字
const char *sMenuRootTxtSelf[] =
{
		sMenuRootTxtSelfEn,
		sMenuRootTxtSelfCn,
};

// 根菜单的子菜单索引
const menu_t sMenuRootChild[] =
{
		MENU_PARAM_INDEX,
		MENU_CALI_INDEX,
//		MENU_TIME_INDEX,
//		MENU_RESTORE_INDEX,
//		MENU_MANUF_INDEX,
//		MENU_DEBUG_INDEX,
//		MENU_USER_INDEX,
};

// 根菜单的子菜单资源
const struct S_MenuResource *sMenuRsrRootChild[] =
{
		&gMenuRsrParam,
		&gMenuRsrCali,
//		&gMenuRsrTime,
//		&gMenuRsrRestore,
//		&gMenuRsrManuf,
//		&gMenuRsrDebug,
//		&gMenuRsrUser,
};

// 根菜单 资源，包括自身字符串，菜单项字符串，菜单项的数目
const struct S_MenuResource gMenuRsrRoot =
{
		MENU_RESOURCE(sMenuRootTxtItemEn,
						sMenuRootChild,
						sMenuRsrRootChild,
						sMenuRootTxtSelf,
						sMenuRootTxtItem)
};


/**
 * @brief   菜单初始化
 */
void MenuRootPreInit(void)
{
}


/**
 * @brief   菜单初始化
 */
void MenuRootInit(void)
{
//	MenuItemInit();
	// 根菜单变量初始化
	MenuValInit();
	// 根菜单资源初始化
	MenuItemInit(&gMenuRsrRoot);
	DisClr();
	MenuDisp();

//	DisClr();
//	S_Lcd_Area_RectangleShade lRec;
//	lRec.PS.X = 0;
//	lRec.PS.Y = 0;
//	lRec.PE.X = 127;
//	lRec.PE.Y = 63;
//	lRec.Ex.X = 3;
//	lRec.Ex.Y = 3;
//	DisRecFramSet(&lRec);
}


/**
 * @brief   进入子菜单
 */
void MenuRootChild(void)
{
	MenuKeyChild();
	MenuDisp();
}


/**
 * @brief   进入父菜单
 */
void MenuRootParent(void)
{
	SaveWrite();
	StateMenuToDetect();
}


/**
 * @brief   下一条菜单项
 */
void MenuRootNext(void)
{
	MenuKeyNext();

}


/**
 * @brief   上一条菜单项
 */
void MenuRootPrev(void)
{
	MenuKeyPrev();
}
