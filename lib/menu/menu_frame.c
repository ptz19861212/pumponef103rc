/**
 * @file    menu_frame.c
 * @brief   菜单 框架代码
 * @author  ptz
 * @email   ptz19861212@163.com
 * @version 0.0.1
 * @date    2013-12-01 18:50:09 星期日 
 * @history (1).2013-12-01 18:50:09 星期日 create
 */
/* Copyright (C)
 * 
 * My own license
 * All right reserved
 * 
 */

#include "menu_frame_in.h"


// 当前指向菜单
struct S_MenuItem sMenuItem;

// 菜单框架
struct S_MenuFrame sMenuFrame;

// 菜单显示
struct S_MenuDisp sMenuDisp;

// 当前菜单控制
//struct S_MenuCtr sMenuCtr;

// 备份结构体
struct S_MenuBak sMenuBak;


/**
 * @brief   菜单项语言初始化
 */
void MenuLangInit(void)
{
	E_Language lLang;
	lLang = Lcd__LangGet();
	sMenuDisp.TextItem = *((sMenuFrame.MenuRsr->ItemText) + lLang);
	sMenuDisp.TextSelf = *(sMenuFrame.MenuRsr->SelfText + lLang);
}


/**
 * @brief   菜单项初始化
 */
void MenuItemInit(const struct S_MenuResource *lpMenuRsr)
{
	// 清屏
//	DisClr();
	// 获得相应的菜单资源
	sMenuFrame.MenuRsr = lpMenuRsr;

	sMenuItem.ItemNum = sMenuFrame.MenuRsr->Num;
	sMenuItem.ScrollLen = sMenuFrame.MenuRsr->ScrollLen;
	sMenuItem.ScrollGap = sMenuFrame.MenuRsr->ScrollGap;
//	sMenuDisp.TextItem = *((sMenuFrame.MenuRsr->ItemText) + sMenuCtr.Lang);
//	sMenuDisp.TextSelf = *(sMenuFrame.MenuRsr->SelfText + sMenuCtr.Lang);

//	E_Language lLang;
//	lLang = Lcd__LangGet();
//	sMenuDisp.TextItem = *((sMenuFrame.MenuRsr->ItemText) + lLang);
//	sMenuDisp.TextSelf = *(sMenuFrame.MenuRsr->SelfText + lLang);

	MenuLangInit();
}

/**
 * @brief   菜单变量初始化
 */
void MenuValInit(void)
{
	// 初始化菜单
	sMenuBak.Depth = 0;
	sMenuItem.Item = 0;
	sMenuItem.Where = 0;
	// 初始化语言
//	sMenuCtr.Lang = Lcd__LangGet();
	// 初始化菜单项
	sMenuFrame.MenuIndex = MENU_ROOT_INDEX;
}


/**
 * @brief   菜单项显示
 */
//static void MenuDispItem(const char *lpStr, menu_t lX, menu_t lY)
//{
////	DisStat(lpStr, lX, lY);
//	Lcd__StatDisp(lpStr);
//}


/**
 * @brief   菜单项居中显示
 *
 * @param   lpX 返回的X坐标，是居中的起始坐标
 * @param   lpY 返回的Y坐标，是居中的起始坐标
 */
//static void MenuDispItemMid(const char* lpStr, S_Lcd_Point* lpPoint)
//{
//	uint16_t lLen = 0;
//	uint16_t lTemp = 0;
//
//	lLen = strlen(lpStr);
////	lTemp = DisGapGet(CONFIG_ITEM_DESPOSE_LCD_X_SIZE,
////						lLen * CONFIG_ITEM_DESPOSE_TXT_X_SIZE, 1);
//	lTemp = GAP_GET(CONFIG_ITEM_DESPOSE_LCD_X_SIZE,
//						lLen * CONFIG_ITEM_DESPOSE_TXT_X_SIZE, 1);
//	lpPoint->X += lTemp;
////	DisStat(lpStr, lpPoint->X, lpPoint->Y);
//	Lcd__StatDisp(lpStr);
//}


///**
// * @brief   菜单项反显
// */
//static void MenuDispItemRev(menu_t lX, menu_t lY)
//{
//	// 例如，第一行子的Y方向的大小是 16,占据了 0 - 15 行，所以计算反显的时候要 - 1
//	// 否则会多反显一行，可能会造成反显一行的右下角多了一小块，其实是反显的左下已经被下一行
//	// 给遮住了，才显得右下多了一小块
//
//	S_Lcd_Area_Rectangle lRec;
//
//	lRec.PS.X = lX;
//	lRec.PS.Y = lY;
//	lRec.PE.X = CONFIG_ITEM_REV_X;
//	lRec.PE.Y = lY + CONFIG_ITEM_OFFSET_GAP_Y - 1;
//	DisRecRev(&lRec);
////	DisRecRev(lX, lY, CONFIG_ITEM_REV_X, lY + CONFIG_ITEM_OFFSET_GAP_Y - 1);
//}


/**
 * @brief   菜单本身名字显示
 */
static void MenuDispMenuSelf(void)
{
//	DisMenuSelfTxt(sMenuDisp.TextSelf, CONFIG_MENU_SELF_TXT_X_START,
//					CONFIG_MENU_SELF_TXT_Y_START);
	Lcd__MenuSelfTxtDisp(sMenuDisp.TextSelf);
}


/**
 * @brief   显示滚动条
 */
static void MenuDispScrollBar(menu_t lLen, menu_t lGap, menu_t lItem)
{
//	DisScrollBar(lLen, CONFIG_SCROLL_BAR_EX, CONFIG_SCROLL_BAR_X,
//					SCROLL_BAR_REMAIN_DOT + lGap * lItem);
	S_Lcd__ScrollBar lScrollBar;

	lScrollBar.Len = lLen;
	lScrollBar.Y = SCROLL_BAR_REMAIN_DOT + lGap * lItem;
	Lcd__MenuScrollBarDisp(&lScrollBar);
}


/**
 * @brief   清除滚动条区域
 */
static void MenuScrollBarClr(void)
{
	S_Lcd_Area_Rectangle lRec;

	lRec.PS.X = CONFIG_SCROLL_BAR_X_START;
	lRec.PS.Y = CONFIG_SCROLL_BAR_Y_START;
	lRec.PE.X = CONFIG_SCROLL_BAR_X_END;
	lRec.PE.Y = CONFIG_SCROLL_BAR_Y_END;
	DisRecFillClr(&lRec);

//	DisRecFillClr(CONFIG_SCROLL_BAR_X_START, CONFIG_SCROLL_BAR_Y_START,
//					CONFIG_SCROLL_BAR_X_END, CONFIG_SCROLL_BAR_Y_END);
}


/**
 * @brief   显示滚动条文字
 */
static void MenuDispScrollBarTxt(void)
{
	static char sScrollBarTxt[MENU_SCROLL_TXT_SIZE];
	menu_t lI;
	uint8_t lLen = 0;
	S_Value_Scroll_Bar_Txt lArray;

	// 首先添加一下结束符，这样才好检查字符串长度
	sScrollBarTxt[0] = 0;

	// 备份菜单项数值
	if (sMenuBak.Depth > 0)
	{
		// 因为深度都是指向的是需要写入的下一个，所以for循环就这样就可以了
		for (lI = 0; lI < sMenuBak.Depth; lI++)
		{
			// 转换菜单项
			lLen = strlen(sScrollBarTxt);
			// 注意显示的菜单项是从1开始的，所以要+1
			lArray.Char = sScrollBarTxt + lLen;
			lArray.Value.Num = sMenuBak.Item[lI] + 1;
			lArray.Value.Point = POINT_HHHHH;
			NUM_TO_STR(&lArray);
//			NUM_TO_STR(sScrollBarTxt + lLen,
//						sMenuBak.Item[lI] + 1, POINT_HHHHH);

			// 转换字符'-'
			lLen = strlen(sScrollBarTxt);
			sScrollBarTxt[lLen] = '-';
			sScrollBarTxt[lLen + 1] = 0;
		}
	}

	// 当前菜单项数值
	lLen = strlen(sScrollBarTxt);
	lArray.Char = sScrollBarTxt + lLen;
	lArray.Value.Num = sMenuItem.Item + 1;
	lArray.Value.Point = POINT_HHHHH;
	NUM_TO_STR(&lArray);

//	NUM_TO_STR(sScrollBarTxt + lLen, sMenuItem.Item + 1, POINT_HHHHH);

	// 整个字符串的长度
	lLen = strlen(sScrollBarTxt);

	// 显示滚动条文字
//	DisScrollBarTxt(sScrollBarTxt,
//			CONFIG_SCROLL_BAR_TXT_X_END - lLen * CONFIG_SCROLL_BAR_TXT_X,
//			CONFIG_SCROLL_BAR_TXT_Y_START);
	Lcd__MenuScrollBarTxtDisp(sScrollBarTxt);
}


/**
 * @brief   显示滚动条文字
 */
static void MenuScrollBarTxtClr(void)
{
	S_Lcd_Area_Rectangle lRec;

	lRec.PS.X = CONFIG_SCROLL_BAR_TXT_X_START;
	lRec.PS.Y = CONFIG_SCROLL_BAR_TXT_Y_START;
	lRec.PE.X = CONFIG_SCROLL_BAR_TXT_X_END;
	lRec.PE.Y = CONFIG_SCROLL_BAR_TXT_Y_END;
	DisRecFillClr(&lRec);
//	DisRecFillClr(CONFIG_SCROLL_BAR_TXT_X_START, CONFIG_SCROLL_BAR_TXT_Y_START,
//					CONFIG_SCROLL_BAR_TXT_X_END, CONFIG_SCROLL_BAR_TXT_Y_END);
}


/**
 * @brief   保存当前菜单参数
 */
void MenuPush(void)
{
	sMenuBak.Item[sMenuBak.Depth] = sMenuItem.Item;
	sMenuBak.Where[sMenuBak.Depth] = sMenuItem.Where;
	sMenuBak.MenuIndex[sMenuBak.Depth] = sMenuFrame.MenuIndex;
	sMenuBak.MenuRsr[sMenuBak.Depth] = sMenuFrame.MenuRsr;
	sMenuBak.Depth++;
}

/**
 * @brief   恢复当前菜单参数
 */
void MenuPop(void)
{
	sMenuBak.Depth--;
	sMenuItem.Item = sMenuBak.Item[sMenuBak.Depth];
	sMenuItem.Where = sMenuBak.Where[sMenuBak.Depth];
	sMenuFrame.MenuIndex = sMenuBak.MenuIndex[sMenuBak.Depth];
	sMenuFrame.MenuRsr = sMenuBak.MenuRsr[sMenuBak.Depth];
//	sMenuCtr.Fresh = MENU_FRESH_REFRESH;
}

/**
 * @brief   菜单显示
 */
void MenuDisp(void)
{
	// 清屏
	DisClr();
	// 确定一次要显示的菜单项的数目
	// 假设一个屏幕只能显示3项，那么当菜单项是2项的时候，就显示2项，当是3项的时候，就显示3项
	// 当4项的时候，还是显示3项
	if (sMenuItem.ItemNum > CONFIG_ITEM_DISP_MAX)
	{
		sMenuDisp.DispMin = CONFIG_ITEM_DISP_MAX;
	}
	else
	{
		sMenuDisp.DispMin = sMenuItem.ItemNum;
	}

	// 检查显示位置是否出界
	if (sMenuItem.Where > sMenuDisp.DispMin - 1)
	{
		// A方案，最底部的显示位置
		//sMenuItem.Where = sMenuDisp.DispMin - 1;
		// B方案，最顶部的显示位置
		sMenuItem.Where = 0;
	}
	// 检查菜单项是否出界
	if (sMenuItem.Item > sMenuItem.ItemNum - 1)
	{
		// A.最后的一个项
		//sMenuItem.Item = sMenuItem.ItemNum - 1;
		// B.最开始的一个项
		sMenuItem.Item = 0;
	}

	// 既然item,where还未定，那么从子菜单退出的时候，就要想办法确定在屏幕上面第一行显示的
	// item 究竟是那个菜单项。所以要求出在屏幕第一行显示的菜单项
	menu_t lDispItem = 0;

	// 屏幕已经显示过一个周期所有的菜单项，item = 0的那个菜单项再次出现在屏幕
	if (sMenuItem.Item >= sMenuItem.Where)
	{
		lDispItem = sMenuItem.Item - sMenuItem.Where;
	}
	else
	{
		lDispItem = sMenuItem.ItemNum - (sMenuItem.Where - sMenuItem.Item);
	}
	// 经过上面的计算，lDispItem的数值就是此时在屏幕最上方也就是where=0的那个位置的item

	menu_t lI;
	S_Lcd__Item lItem;
	// 显示全部的菜单
	for (lI = 0; lI < sMenuDisp.DispMin; lI++)
	{
		lItem.Char = *(sMenuDisp.TextItem + lDispItem);
		lItem.Pos = lI;
		Lcd__MenuItemDisp(&lItem);
//		MenuDispItem(*(sMenuDisp.TextItem + lDispItem),
//						CONFIG_ITEM_TXT_X,
//						CONFIG_ITEM_OFFSET_Y + lI * CONFIG_ITEM_OFFSET_GAP_Y);

		// 反显菜单项，应该是where对应的项，也就是lI对应的项
		if (lDispItem == sMenuItem.Item)
		{
			Lcd__MenuItemRev(lI);
//			MenuDispItemRev(CONFIG_ITEM_OFFSET_X,
//							CONFIG_ITEM_OFFSET_Y + lI * CONFIG_ITEM_OFFSET_GAP_Y);
		}

		if (lDispItem == (sMenuItem.ItemNum - 1))
		{
			lDispItem = 0;
		}
		else
		{
			lDispItem++;
		}
	}

	// 维护滚动条
	MenuDispScrollBar(sMenuItem.ScrollLen, sMenuItem.ScrollGap,
							sMenuItem.Item);
	// 维护滚动条文字
	MenuDispScrollBarTxt();

//	rt_kprintf("bar txt\n");
	// 显示本层菜单本身的名字
	MenuDispMenuSelf();
//	rt_kprintf("self \n");

	// 维护虚线
	S_Lcd_Line_Horizon lHor;

	lHor.XS = CONFIG_MENU_DOT_LINE_X_START;
	lHor.Y = CONFIG_MENU_DOT_LINE_Y_START;
	lHor.XE = CONFIG_MENU_DOT_LINE_X_END;
	DisHorDotLinSet(&lHor);

}


/**
 * @brief   获取当前的菜单项是那一条
 *
 * @param   lpItem 地址
 */
void MenuItemGet(menu_t* lpItem)
{
	*lpItem = sMenuItem.Item;
}


/**
 * @brief   设置当前的菜单项是那一条
 *
 * @param   lItem
 */
void MenuItemSet(menu_t lItem)
{
	sMenuItem.Item = lItem;
}


/**
 * @brief   编译时间显示
 */
void MenuDispBuildTime(void)
{
	MenuDispItem("Build Time!", 1, 0);
	MenuDispItem(__DATE__, 1, 16);
	MenuDispItem(__TIME__, 1, 32);
}


/**
 * @brief   清除菜单项显示区域
 */
static void MenuItemClr(void)
{
	S_Lcd_Area_Rectangle lRec;

	lRec.PS.X = CONFIG_ITEM_X_START;
	lRec.PS.Y = CONFIG_ITEM_Y_START;
	lRec.PE.X = CONFIG_ITEM_X_END;
	lRec.PE.Y = CONFIG_ITEM_Y_END;
	DisRecFillClr(&lRec);
//	DisRecFillClr(CONFIG_ITEM_X_START, CONFIG_ITEM_Y_START,
//					CONFIG_ITEM_X_END, CONFIG_ITEM_Y_END);
}


/*********************************** 按键部分 ********************************/

/**
 * @brief   按键 下一条
 */
void MenuKeyNext(void)
{
	// 为了取消反显
	menu_t lItemBak;

	lItemBak = sMenuItem.Item;

	// 维护item
	if (sMenuItem.Item >= (sMenuItem.ItemNum - 1))
	{
		sMenuItem.Item = 0;
	}
	else
	{
		sMenuItem.Item++;
	}

	// 清除滚动条区域和滚动条文字区域，不管是否屏幕翻动，这些都是要更新的
	MenuScrollBarClr();
	MenuScrollBarTxtClr();

	menu_t lI, lDispItem;
	// 维护显示
	// 当前位置不是最下面，
	if (sMenuItem.Where != (sMenuDisp.DispMin - 1))
	{
		// 所以先取消反显当前，
		Lcd__MenuItemRev(sMenuItem.Where);
//		MenuDispItemRev(CONFIG_ITEM_OFFSET_X,
//							CONFIG_ITEM_OFFSET_Y +
//							sMenuItem.Where * CONFIG_ITEM_OFFSET_GAP_Y);
		// 然后在反显下一条
		sMenuItem.Where++;
		Lcd__MenuItemRev(sMenuItem.Where);
//		MenuDispItemRev(CONFIG_ITEM_OFFSET_X,
//							CONFIG_ITEM_OFFSET_Y +
//							sMenuItem.Where * CONFIG_ITEM_OFFSET_GAP_Y);
	}
	else  // 当前显示位置就是在最下面
	{
		if (sMenuItem.ItemNum > CONFIG_ITEM_DISP_MAX)
		{
			lDispItem = sMenuItem.Item;
			lI = CONFIG_ITEM_DISP_MAX;

			// 清除菜单项显示区域
			MenuItemClr();

			S_Lcd__Item lItem;
			// 项是item，位置是where， 显示最下面一条
			lItem.Char = *(sMenuDisp.TextItem + lDispItem);
			lItem.Pos = lI - 1;
			Lcd__MenuItemDisp(&lItem);
//			MenuDispItem(*(sMenuDisp.TextItem + lDispItem),
//							CONFIG_ITEM_TXT_X,
//							CONFIG_ITEM_OFFSET_Y +
//							(lI - 1) * CONFIG_ITEM_OFFSET_GAP_Y);
			Lcd__MenuItemRev(sMenuItem.Where);
//			MenuDispItemRev(CONFIG_ITEM_OFFSET_X,
//								CONFIG_ITEM_OFFSET_Y +
//								sMenuItem.Where * CONFIG_ITEM_OFFSET_GAP_Y);
			// 因为是从最下面一条向上面显示的，所以
			if (lDispItem == 0)
			{
				lDispItem = sMenuItem.ItemNum - 1;
			}
			else
			{
				lDispItem--;
			}

			// 显示除了最下面一条的上面几条，从下向上一条一条显示出来
			for (lI = (CONFIG_ITEM_DISP_MAX - 1); lI > 0; lI--)
			{
				lItem.Char = *(sMenuDisp.TextItem + lDispItem);
				lItem.Pos = lI - 1;
				Lcd__MenuItemDisp(&lItem);
//				MenuDispItem(*(sMenuDisp.TextItem + lDispItem),
//								CONFIG_ITEM_TXT_X,
//								CONFIG_ITEM_OFFSET_Y +
//								(lI - 1) * CONFIG_ITEM_OFFSET_GAP_Y);

				if (lDispItem == 0)
				{
					lDispItem = sMenuItem.ItemNum - 1;
				}
				else
				{
					lDispItem--;
				}
			}
			// 当前位置还是在最下面
			//sMenuItem.Where = CONFIG_ITEM_DISP_MAX - 1;
		}
		else  //单屏能显示玩全部菜单，所以直接跳到顶部反显
		{
			// 所以先取消反显当前，
			Lcd__MenuItemRev(sMenuItem.Where);
//			MenuDispItemRev(CONFIG_ITEM_OFFSET_X,
//								CONFIG_ITEM_OFFSET_Y +
//								sMenuItem.Where * CONFIG_ITEM_OFFSET_GAP_Y);
			// 然后在反显下一条
			sMenuItem.Where = 0;
			Lcd__MenuItemRev(sMenuItem.Where);
//			MenuDispItemRev(CONFIG_ITEM_OFFSET_X,
//								CONFIG_ITEM_OFFSET_Y +
//								sMenuItem.Where * CONFIG_ITEM_OFFSET_GAP_Y);

		}
	}
	// 维护滚动条
	MenuDispScrollBar(sMenuItem.ScrollLen, sMenuItem.ScrollGap, sMenuItem.Item);
	// 维护滚动条文字
	MenuDispScrollBarTxt();
	// 维护虚线
	S_Lcd_Line_Horizon lHor;

	lHor.XS = CONFIG_MENU_DOT_LINE_X_START;
	lHor.Y = CONFIG_MENU_DOT_LINE_Y_START;
	lHor.XE = CONFIG_MENU_DOT_LINE_X_END;
	DisHorDotLinSet(&lHor);
}


/**
 * @brief   按键 上一条
 */
void MenuKeyPrev(void)
{
	// 为了取消反显
	menu_t lItemBak;

	lItemBak = sMenuItem.Item;

	// 维护item
	if (sMenuItem.Item == 0)
	{
		sMenuItem.Item = (sMenuItem.ItemNum - 1);
	}
	else
	{
		sMenuItem.Item--;
	}

	// 清除滚动条区域和滚动条文字区域，不管是否屏幕翻动，这些都是要更新的
	MenuScrollBarClr();
	MenuScrollBarTxtClr();

	menu_t lI, lDispItem;
	// 维护显示
	// 当前位置不是最上面，
	if (sMenuItem.Where != 0)
	{
		// 所以先取消反显当前，
		Lcd__MenuItemRev(sMenuItem.Where);
//		MenuDispItemRev(CONFIG_ITEM_OFFSET_X,
//							CONFIG_ITEM_OFFSET_Y +
//							sMenuItem.Where * CONFIG_ITEM_OFFSET_GAP_Y);
		// 然后在反显上一条
		sMenuItem.Where--;
		Lcd__MenuItemRev(sMenuItem.Where);
//		MenuDispItemRev(CONFIG_ITEM_OFFSET_X,
//							CONFIG_ITEM_OFFSET_Y +
//							sMenuItem.Where * CONFIG_ITEM_OFFSET_GAP_Y);
	}
	else  // 当前显示位置就是在最上面
	{
		if (sMenuItem.ItemNum > CONFIG_ITEM_DISP_MAX)
		{
			lDispItem = sMenuItem.Item;
			lI = 0;

			// 清除菜单项显示区域
			MenuItemClr();

			S_Lcd__Item lItem;
			// 项是item，位置是where， 显示最下面一条
			lItem.Char = *(sMenuDisp.TextItem + lDispItem);
			lItem.Pos = lI;
			Lcd__MenuItemDisp(&lItem);
//			MenuDispItem(*(sMenuDisp.TextItem + lDispItem),
//							CONFIG_ITEM_TXT_X,
//							CONFIG_ITEM_OFFSET_Y +
//							lI * CONFIG_ITEM_OFFSET_GAP_Y);
			Lcd__MenuItemRev(sMenuItem.Where);
//			MenuDispItemRev(CONFIG_ITEM_OFFSET_X,
//								CONFIG_ITEM_OFFSET_Y +
//								sMenuItem.Where * CONFIG_ITEM_OFFSET_GAP_Y);
			// 因为是从最上面一条向下面显示的，所以
			if (lDispItem == (sMenuItem.ItemNum - 1))
			{
				lDispItem = 0;
			}
			else
			{
				lDispItem++;
			}

			// 显示除了最下面一条的上面几条，从下向上一条一条显示出来
			for (lI = 1; lI < CONFIG_ITEM_DISP_MAX; lI++)
			{
				lItem.Char = *(sMenuDisp.TextItem + lDispItem);
				lItem.Pos = lI;
				Lcd__MenuItemDisp(&lItem);
//				MenuDispItem(*(sMenuDisp.TextItem + lDispItem),
//								CONFIG_ITEM_TXT_X,
//								CONFIG_ITEM_OFFSET_Y +
//								lI * CONFIG_ITEM_OFFSET_GAP_Y);

				if (lDispItem == (sMenuItem.ItemNum - 1))
				{
					lDispItem = 0;
				}
				else
				{
					lDispItem++;
				}
			}
			// 当前位置还是在最上面
			//sMenuItem.Where = 0;
		}
		else  //单屏能显示玩全部菜单，所以直接跳到顶部反显
		{
			// 所以先取消反显当前，
			Lcd__MenuItemRev(sMenuItem.Where);
//			MenuDispItemRev(CONFIG_ITEM_OFFSET_X,
//								CONFIG_ITEM_OFFSET_Y +
//								sMenuItem.Where * CONFIG_ITEM_OFFSET_GAP_Y);
			// 然后在反显下一条
			sMenuItem.Where = sMenuItem.ItemNum - 1;
			Lcd__MenuItemRev(sMenuItem.Where);
//			MenuDispItemRev(CONFIG_ITEM_OFFSET_X,
//								CONFIG_ITEM_OFFSET_Y +
//								sMenuItem.Where * CONFIG_ITEM_OFFSET_GAP_Y);

		}
	}
	// 维护滚动条
	MenuDispScrollBar(sMenuItem.ScrollLen, sMenuItem.ScrollGap, sMenuItem.Item);
	// 维护滚动条文字
	MenuDispScrollBarTxt();
	// 维护虚线
	S_Lcd_Line_Horizon lHor;

	lHor.XS = CONFIG_MENU_DOT_LINE_X_START;
	lHor.Y = CONFIG_MENU_DOT_LINE_Y_START;
	lHor.XE = CONFIG_MENU_DOT_LINE_X_END;
	DisHorDotLinSet(&lHor);
}


/**
 * @brief   菜单处理的进入预初始化
 */
void MenuLoadPreInit(void)
{
	// 初始化
	gMenuTab[sMenuFrame.MenuIndex].PreInit();
}


/**
 * @brief   菜单处理的进入初始化
 */
void MenuLoadInit(void)
{
	// 初始化
	gMenuTab[sMenuFrame.MenuIndex].Init();
}


/**
 * @brief   按键 子菜单
 */
void MenuKeyChild(void)
{
	// 对父菜单的相关进行常规备份，因为下面要修改菜单项和显示位置
	MenuPush();
	sMenuFrame.MenuIndex = sMenuFrame.MenuRsr->ItemIndex[sMenuItem.Item];
	MenuItemInit(sMenuFrame.MenuRsr->ItemResource[sMenuItem.Item]);
	sMenuItem.Item = 0;
	sMenuItem.Where = 0;
}


/**
 * @brief   按键 父菜单
 */
void MenuKeyParent(void)
{
	// 对父菜单的相关进行恢复
	MenuPop();
	MenuItemInit(sMenuFrame.MenuRsr);
}


/**
 * @brief   按键 调用函数
 */
void MenuKey(uint8_t lKey)
{
	switch (lKey)
	{
		case KEY_DOWN:
			gMenuTab[sMenuFrame.MenuIndex].Next();
			break;

		case KEY_UP:
			gMenuTab[sMenuFrame.MenuIndex].Prev();
			break;

		case KEY_ENTER:
			gMenuTab[sMenuFrame.MenuIndex].Child();
			break;

		case KEY_SPECIAL:
			gMenuTab[sMenuFrame.MenuIndex].Parent();
			break;

		default:
			break;
	}
}



/************************ 长时间菜单无操作 *****************************/
static uint8_t sMenuNoOperateCount;
static my_second_t sMenuNoOperateSecond;


/**
 * @brief   菜单无操作倒计时
 */
void MenuNoOperateCountdown(void)
{
	S_Device* lpDev;
	StateDevicePointGet(&lpDev);

	// 为了整秒
	if (lpDev->pTemp->Time.Count != sMenuNoOperateCount)
	{
		return;
	}

	if (lpDev->pTemp->Time.Sec > (sMenuNoOperateSecond +
								CONFIG_MENU_NO_OPERATE_SECOND))
	{
		StateMenuToDetect();
	}
}


/**
 * @brief   菜单无操作刷新
 */
void MenuNoOperateFresh(void)
{
	S_Device* lpDev;
	StateDevicePointGet(&lpDev);

	sMenuNoOperateCount = lpDev->pTemp->Time.Count;
	sMenuNoOperateSecond = lpDev->pTemp->Time.Sec;
}

