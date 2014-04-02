/**
 * @file    my_bsp.h
 * @brief   
 * @author  ptz
 * @email   ptz19861212@163.com
 * @version 0.0.1
 * @date    2014-01-17 09:58:36 星期五 
 * @history (1).2014-01-17 09:58:36 星期五 create
 */
/* Copyright (C)
 * 
 * My own license
 * All right reserved
 * 
 */

#ifndef __MY_BSP_H__
#define __MY_BSP_H__

#include <stdint.h>

/************************ 灯 **************************************/
typedef uint8_t 						my_led_t;
typedef uint8_t 						my_led_cd_t;

//typedef enum {LED_NONE = 0,
typedef enum {
	LED_ALARM_UPPER = 0,
	LED_ALARM_LOWER,
	LED_RUN,
	LED_POWER_ON,
} E_LedSource;

#define LED_SOURCE_NUM					4

typedef enum{
	LED_ALARM_TIME_UPPER = 12,
	LED_ALARM_TIME_LOWER = 25,
	LED_ALARM_TIME_RUN = 6,
	LED_POWER_ON_TIME = 6,
}E_LedSourceTime;

typedef enum {
				LED_PIN_1 = 0,
				LED_PIN_2,
}E_LedPin;


typedef struct
{
	// 来源
	E_LedSource Src;
	// 倒计时
	my_led_cd_t Time;
	// 那个灯
	E_LedPin Pin;
}S_Led;

/************************ 蜂鸣器 **************************************/
typedef uint8_t 						my_buzzer_t;
typedef uint8_t 						my_buzzer_cd_t;

//typedef enum {BUZZER_NONE = 0,
typedef enum {
	BUZZER_ALARM_UPPER = 0,
	BUZZER_ALARM_LOWER,
	BUZZER_KEY,
	BUZZER_SECOND,
	BUZZER_POWER_ON,
} E_BuzzerSource;

#define BUZZER_SOURCE_NUM					5

typedef enum {
	BUZZER_ALARM_TIME_UPPER = 12,
	BUZZER_ALARM_TIME_LOWER = 25,
	BUZZER_KEY_TIME = 6,
	BUZZER_SECOND_TIME = 6,
	BUZZER_POWER_ON_TIME = 6,
} E_BuzzerSourceTime;


typedef struct
{
	// 来源
	E_BuzzerSource Src;
	// 倒计时
	my_buzzer_cd_t Time;
}S_Buzzer;

/************************ 振动泵 **************************************/
typedef uint8_t 						my_vibration_t;
typedef uint8_t 						my_vibration_cd_t;

//typedef enum {VIBRATION_NONE = 0,
typedef enum {
	VIBRATION_ALARM_UPPER = 0,
	VIBRATION_ALARM_LOWER,
	VIBRATION_POWER_ON,
} E_VibrationSource;

#define VIBRATION_SOURCE_NUM					3

typedef enum {
	VIBRATION_ALARM_TIME_UPPER = 12,
	VIBRATION_ALARM_TIME_LOWER = 25,
	VIBRATION_POWER_ON_TIME = 12,
} E_VibrationSourceTime;


typedef struct
{
	// 来源
	E_VibrationSource Src;
	// 倒计时
	my_vibration_cd_t Time;
}S_Vibration;

#endif
