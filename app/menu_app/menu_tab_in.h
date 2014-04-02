/**
 * @file    menu_tab_in.h
 * @brief   根菜单
 * @author  ptz
 * @email   ptz19861212@163.com
 * @version 0.0.1
 * @date    2013-12-02 13:36:02 星期一 
 * @history (1).2013-12-02 13:36:02 星期一 create
 */
/* Copyright (C)
 * 
 * My own license
 * All right reserved
 * 
 */

#ifndef __MENU_TAB_IN_H__
#define __MENU_TAB_IN_H__


#include <stdint.h>
#include "my_define.h"
#include "menu_root.h"
#include "menu_param.h"
#include "menu_cali.h"
#include "menu_time.h"
#include "menu_restore.h"
#include "menu_manuf.h"
#include "menu_debug.h"
#include "menu_user.h"
#include "menu_param_alarm.h"
#include "menu_param_upper.h"
#include "menu_param_lower.h"
#include "menu_param_stel.h"
#include "menu_param_twa.h"
#include "menu_param_pump.h"
#include "menu_param_bak.h"
//#include "menu_cali_zero.h"
//#include "menu_cali_coeff.h"
#include "menu_rst_param.h"
#include "menu_rst_cali.h"
#include "menu_debug_zero.h"
#include "menu_debug_coeff.h"
#include "menu_debug_ref1.h"
#include "menu_debug_ref2.h"
#include "menu_debug_build.h"
#include "menu_user_group.h"
#include "menu_user_upgrade.h"
#include "menu_user_degrade.h"
#include "menu_param_alarm_sound.h"
#include "menu_param_alarm_vibration.h"
#include "menu_param_language.h"
#include "menu_tab.h"

// 生成按键函数表
#define MENU_KEY_TAB(TXT, Txt)		\
									{\
									MENU_##TXT##_INDEX,\
									Menu##Txt##PreInit,\
									Menu##Txt##Init,\
									Menu##Txt##Child,\
									Menu##Txt##Parent,\
									Menu##Txt##Next,\
									Menu##Txt##Prev,\
									}


#endif
