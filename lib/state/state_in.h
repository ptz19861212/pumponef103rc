/**
 * @file    state_in.h
 * @brief   
 * @author  ptz
 * @email   ptz19861212@163.com
 * @version 0.0.1
 * @date    2013-12-03 12:55:57 星期二 
 * @history (1).2013-12-03 12:55:57 星期二 create
 */
/* Copyright (C)
 * 
 * My own license
 * All right reserved
 * 
 */

#ifndef __STATE_IN_H__
#define __STATE_IN_H__

//#include "stm32f10x.h"
#include <stdint.h>
#include "rtthread.h"
#include "config_bsp.h"
#include "state.h"
#include "key.h"
#include "display_uc1701.h"
#include "gas_value_get.h"
#include "gas_alarm_get.h"
#include "gas_cali_zero.h"
#include "gas_cali_coeff.h"
#include "my_language.h"
#include "my_flash.h"
#include "flash.h"
#include "my_define.h"
#include "my_math.h"
#include "state_countdown.h"
#include "bsp_buzzer.h"
#include "bsp_source.h"
#include "bsp_pump.h"
#include "state_shutdown.h"
#include "state_detect.h"


typedef enum {STATE_SELF_CHECK= 0,\
				STATE_DETECT,\
				STATE_MENU,\
				STATE_INPUT,\
				STATE_COUNTDOWN,\
				STATE_RESULT,
				STATE_SHUTDOWN,
				STATE_POWER_OFF,
				STATE_INFO,
				STATE_CHARGE,
} StateState;

#define CONFIG_SAVE_GAS_SIZE			\
								EVEN(sizeof(struct S_Gas_Save))
#define CONFIG_SAVE_DEVICE_SIZE			\
								EVEN(sizeof(struct S_Device_Save))

//#define STATE_SELF_CHECK				0
//#define STATE_DETECT					1
//#define STATE_MENU					2

#endif
