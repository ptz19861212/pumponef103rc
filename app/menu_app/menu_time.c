/**
 * @file    menu_time.c
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

#include "menu_time_in.h"

// 菜单的菜单项 英文
const char *sMenuTimeTxtItemEn[] =
{
		"Time"
};

// 菜单的菜单项 中文
const char *sMenuTimeTxtItemCn[] =
{
		"time"
	//		"参数设置",
	//		"气体校准",
		//	"时间设定",
	//		"恢复出厂",
		//	"生产时间",
		//	"内部调试",
	//		"用户权限",
};

// 菜单的菜单项 指针数组
const char **sMenuTimeTxtItem[] =
{
		sMenuTimeTxtItemEn,
		sMenuTimeTxtItemCn,
};

// 菜单自身名字 英文
const char sMenuTimeTxtSelfEn[] = "Time";

// 菜单自身名字 中文
const char sMenuTimeTxtSelfCn[] = "time";

// 菜单自身名字
const char *sMenuTimeTxtSelf[] =
{
		sMenuTimeTxtSelfEn,
		sMenuTimeTxtSelfCn,
};

// 菜单的子菜单索引
const menu_t sMenuTimeChild[] =
{
		MENU_TIME_INDEX,
};

// 菜单的子菜单资源
const struct S_MenuResource *sMenuRsrTimeChild[] =
{
		&gMenuRsrTime,
};

// 菜单 资源，包括自身字符串，菜单项字符串，菜单项的数目
const struct S_MenuResource gMenuRsrTime =
{
	MENU_RESOURCE(sMenuTimeTxtItemEn,
					sMenuTimeChild,
					sMenuRsrTimeChild,
					sMenuTimeTxtSelf,
					sMenuTimeTxtItem)
};


/**
 * @brief   菜单初始化
 */
void MenuTimePreInit(void)
{
}


/**
 * @brief   菜单初始化
 */
void MenuTimeInit(void)
{
}


/**
 * @brief   进入子菜单
 */
void MenuTimeChild(void)
{
	MenuKeyChild();
	MenuDisp();
}


/**
 * @brief   进入父菜单
 */
void MenuTimeParent(void)
{
	MenuKeyParent();
	MenuDisp();
}


/**
 * @brief   下一条菜单项
 */
void MenuTimeNext(void)
{
	MenuKeyNext();

}


/**
 * @brief   上一条菜单项
 */
void MenuTimePrev(void)
{
	MenuKeyPrev();
}
