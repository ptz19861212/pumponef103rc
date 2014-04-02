/**
 * @file    menu_param_pump.c
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

#include "menu_param_pump_in.h"

// 菜单的菜单项 英文
const char *sMenuParamPumpTxtItemEn[] =
{
		"Sound",
		"Vibration",
};

// 菜单的菜单项 中文
const char *sMenuParamPumpTxtItemCn[] =
{
		"sound",
		"vibration",
	//		"参数设置",
	//		"气体校准",
		//	"时间设定",
	//		"恢复出厂",
		//	"生产时间",
		//	"内部调试",
	//		"用户权限",
};

// 菜单的菜单项 指针数组
const char **sMenuParamPumpTxtItem[] =
{
		sMenuParamPumpTxtItemEn,
		sMenuParamPumpTxtItemCn,
};

// 菜单自身名字 英文
const char sMenuParamPumpTxtSelfEn[] = "Pump";

// 菜单自身名字 中文
const char sMenuParamPumpTxtSelfCn[] = "pump";

// 菜单自身名字
const char *sMenuParamPumpTxtSelf[] =
{
		sMenuParamPumpTxtSelfEn,
		sMenuParamPumpTxtSelfCn,
};

// 菜单的子菜单索引
const menu_t sMenuParamPumpChild[] =
{
		MENU_PARAM_ALARM_INDEX,
};

// 菜单的子菜单资源
const struct S_MenuResource *sMenuRsrParamPumpChild[] =
{
		&gMenuRsrParamPump,
};

// 菜单 资源，包括自身字符串，菜单项字符串，菜单项的数目
const struct S_MenuResource gMenuRsrParamPump =
{
	MENU_RESOURCE(sMenuParamPumpTxtItemEn,
					sMenuParamPumpChild,
					sMenuRsrParamPumpChild,
					sMenuParamPumpTxtSelf,
					sMenuParamPumpTxtItem)
};


/**
 * @brief   菜单初始化
 */
void MenuParamPumpPreInit(void)
{
}


/**
 * @brief   菜单初始化
 */
void MenuParamPumpInit(void)
{
}


/**
 * @brief   进入子菜单
 */
void MenuParamPumpChild(void)
{
	MenuKeyChild();
	MenuDisp();
}


/**
 * @brief   进入父菜单
 */
void MenuParamPumpParent(void)
{
	MenuKeyParent();
	MenuDisp();
}


/**
 * @brief   下一条菜单项
 */
void MenuParamPumpNext(void)
{
	MenuKeyNext();

}


/**
 * @brief   上一条菜单项
 */
void MenuParamPumpPrev(void)
{
	MenuKeyPrev();
}
