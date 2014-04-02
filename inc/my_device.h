/**
 * @file    my_device.h
 * @brief   设备
 * @author  ptz
 * @email   ptz19861212@163.com
 * @version 0.0.1
 * @date    2013-12-18 00:27:43 星期三 
 * @history (1).2013-12-18 00:27:43 星期三 create
 */
/* Copyright (C)
 * 
 * My own license
 * All right reserved
 * 
 */

#ifndef __MY_DEVICE_H__
#define __MY_DEVICE_H__

#include "my_define.h"
#include "my_calendar.h"


typedef enum {DEVICE_AUTHORITY_USR = (1 << 0), \
				DEVICE_AUTHORITY_DEBUG = (1 << 3),\
				DEVICE_AUTHORITY_ROOT = (1 << 7)} E_DeviceAuthorityState;

typedef enum {\
				DEVICE_PWD_USR = 0x00000000, \
				// 1101 0010 0011 1111 0111 1011 0101 1110
				DEVICE_PWD_DEBUG = 0xD23F7B5E,\
				// 1100 0111 0011 0001 1010 1110 0010 1101
				DEVICE_PWD_ROOT = 0xC731AE2D} E_DevicePasswordState;

typedef enum {DEVICE_ERR_NONE = 0, \
				DEVICE_ERR_ZERO,\
				DEVICE_ERR_GAS} E_DeviceErrorState;

typedef enum {DEVICE_CHARGE_OFF = 0, \
				DEVICE_CHARGE_ON,\
				DEVICE_CHARGE_FULL,
} E_DeviceChargeState;

// 风扇
struct S_Device_Fan_Temp
{
	// 计数
//	uint8_t Count;
	// 风扇状态
	E_TurnState State;
};

// 风扇
struct S_Device_Fan_Const
{
	// 风扇显示动画的最大
//	uint8_t DispMax;
	// 风扇进气等级的最大
	uint8_t Max;
};

// 风扇
struct S_Device_Fan_Save
{
	// 风扇进气等级
	uint8_t Level;
};

// 显示
struct S_Device_Display
{
	// 计数
	uint8_t Count;
	// 刷新
	E_TurnState Fresh;
};

// 时长
typedef struct
{
	// 计数
	uint8_t Count;
	// 秒
	my_second_t Sec;
	// 分
	my_minute_t Min;
	// 时
	my_hour_t Hour;
	// 天
	my_day_t Day;
}S_Device_Time;

// 电池
struct S_Device_Bat_Point
{
	// 电池百分比
	uint8_t Value;
	// 电池ADC数值
	uint16_t Adc;
};

// 电池
struct S_Device_Bat_Const
{
	// 电池 0%
	struct S_Device_Bat_Point Lv0;
	// 电池 20%
	struct S_Device_Bat_Point Lv20;
	// 电池 40%
	struct S_Device_Bat_Point Lv40;
	// 电池 60%
	struct S_Device_Bat_Point Lv60;
	// 电池 80%
	struct S_Device_Bat_Point Lv80;
	// 电池 100%
	struct S_Device_Bat_Point Lv100;
};

// 电池
struct S_Device_Bat_Temp
{
	// 电池当前的点
	struct S_Device_Bat_Point Point;
	// 电池当前容量的等级
//	uint8_t Lv;
};

// 充电
struct S_Device_Charge
{
	// 充电电流大小，单位mA
	uint16_t Value;
	// 充电ADC数值
	uint16_t Adc;
	// 充电状态
	E_DeviceChargeState State;
};

struct S_Device_Group
{
	// 用户组
	E_DeviceAuthorityState Authority;
	// 密码
	E_DevicePasswordState Pwd;
};

struct S_Device_Member
{
	struct S_Device_Group Root;
	struct S_Device_Group Debug;
	struct S_Device_Group Usr;
};

// state
struct S_Device_State_Txt
{
	// 设备检测状态字符串数组
	const char** Detect;
	// 设备标零状态字符串数组
	const char** CaliZero;
	// 设备标气状态字符串数组
	const char** CaliGas;
};

// alarm
struct S_Device_Alarm_Txt
{
	// 设备一级报警字符串数组
	const char** Lower;
	// 设备二级报警字符串数组
	const char** Upper;
};

// version
typedef struct
{
	// 软件版本号
	const char* Ver;
	// 软件编译日期
	const char* Date;
	// 软件编译时间
	const char* Time;
}S_Device_Version_Txt;

struct S_Device_Const
{
	// 多长时间为1S
	uint8_t SecMax;
	// 多长时间仪器显示一次的计数次数
	uint8_t DispMax;
	// 风扇
	struct S_Device_Fan_Const Fan;
	// 电池容量ADC
	struct S_Device_Bat_Const Bat;
	// 设备用户组
	struct S_Device_Member Member;
	// state txt
	struct S_Device_State_Txt State;
	// alarm txt
	struct S_Device_Alarm_Txt Alarm;
	// version
	S_Device_Version_Txt Version;
};

struct S_Device_Save
{
	// 设备地址
	uint16_t Address;
	// 气泵的进气等级
	uint8_t Fan;
	// 语言
	uint8_t Language;
	// 是否声音报警
	E_TurnState Sound;
	// 是否震动报警
	E_TurnState Vibration;
	// 生产日期
	S_Calendar_Date Manf;
	// 质保日期
	S_Calendar_Date Warranty;
	//is this struct member saved?
	union
	{
		uint8_t Save;
		struct
		{
			uint8_t Addr			:	1;
			uint8_t Fan			:	1;
			uint8_t Lang			:	1;
			uint8_t Snd			:	1;
			uint8_t Vbr			:	1;
			uint8_t Manf			:	1;
			uint8_t Wrnty			:	1;
			uint8_t RESERVE		:	1;
		}Save_Bits;
	};
};

struct S_Device_Temp
{
	// 继电器
	E_TurnState Relay;
	// 继电器
	struct S_Device_Fan_Temp Fan;
	// 确认等的闪烁显示
	E_BlinkState Blink;
	// 设备出错
	E_DeviceErrorState Error;
	// 设备充电状态
	struct S_Device_Charge Charge;
	// 允许显示相关
	struct S_Device_Display Disp;
	// 电池电量
	struct S_Device_Bat_Temp Bat;
	// 用户组
	struct S_Device_Group Group;
	// 开机时长
	S_Device_Time Time;
};

typedef struct
{
	const struct S_Device_Const* pConst;
	struct S_Device_Save* pSave;
	struct S_Device_Temp* pTemp;
}S_Device;



// 用户组
//#define DEVICE_USR_ROOT						(1 << 7)
//#define DEVICE_USR_DEBUG						(1 << 3)
//#define DEVICE_USR_USR						(1 << 0)


// 密码
//// 1100 0111 0011 0001 1010 1110 0010 1101
//#define DEVICE_PWD_ROOT						0xC731AE2D
//// 1101 0010 0011 1111 0111 1011 0101 1110
//#define DEVICE_PWD_DEBUG						0xD23F7B5E
//#define DEVICE_PWD_USR						0x00000000

#endif
