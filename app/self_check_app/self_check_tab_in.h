/**
 * @file    self_check_tab_in.h
 * @brief   根自检
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

#ifndef __SELF_CHECK_TAB_IN_H__
#define __SELF_CHECK_TAB_IN_H__


#include <stdint.h>
#include "my_define.h"
#include "self_check_root.h"
#include "self_check_tab.h"
#include "self_check_sample.h"
#include "self_check_version.h"
#include "self_check_build_date.h"
#include "self_check_build_time.h"
#include "self_check_manf_date.h"
#include "self_check_warranty_date.h"
#include "self_check_gas_name.h"
#include "self_check_cali_date.h"
#include "self_check_cali_time.h"
#include "self_check_alarm_upper.h"
#include "self_check_alarm_lower.h"
#include "self_check_alarm_stel.h"
#include "self_check_alarm_twa.h"
#include "self_check_alarm_sound.h"
#include "self_check_alarm_vibration.h"
#include "self_check_usr_group.h"
#include "self_check_end.h"
#include "self_check_gas_range.h"

// 生成函数表
#define SELF_CHECK_KEY_TAB(TXT, Txt)		\
									{\
										SELF_CHECK_##TXT##_INDEX,\
										SelfCheck##Txt##Init,\
									}


#endif
