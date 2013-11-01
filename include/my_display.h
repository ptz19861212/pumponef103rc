/**
 * @file my_display.h
 * @brief: 
 * @author ptz, ptz19861212@163.com
 * @version 0.0.1
 * @date 2012-10-13
 */

/* Copyright(C)
 * My own license
 * All right reserved
 * 
 */

#ifndef __MY_DISPLAY_H__
#define __MY_DISPLAY_H__


// point
#define POINT_HHHHH                             0
#define POINT_HHHHXH                            1
#define POINT_HHHXHH                            2
#define POINT_HHXHHH                            3
#define POINT_HXHHHH                            4


// nixietube label
#define LABEL_NO 				0x00
#define LABEL_YES 				0x01
#define LABEL_FULL_SCALE 			0x02
#define LABEL_HIGH 				0x03
#define LABEL_LOW				0x04
#define LABEL_ADDRESS				0x05
#define LABEL_0SE				0x06
#define LABEL_GAS				0x07
#define LABEL_ERROR				0x08
#define LABEL_4MA				0x09
#define LABEL_8MA				0x0a
#define LABEL_12MA				0x0b
#define LABEL_16MA				0x0c
#define LABEL_20MA				0x0d
#define LABEL_VER				0x0e
#define LABEL_CES_ON				0x0f
#define LABEL_CES_OFF				0x10
#define LABEL_SAVE				0x11
#define LABEL_RESET				0x12
#define LABEL_SAVE_ON				0x13
#define LABEL_SAVE_OFF				0x14
#define LABEL_WAIT				0x15
#define LABEL_NONE				0x16
#define LABEL_FLOOR				0x17
#define LABEL_UP_ADDRESS			0x18
#define LABEL_FLOOR_CONTROLA			0x19
#define LABEL_FLOOR_CONTROLB			0x1a
#define LABEL_B					0x1b
#define LABEL_CES				0x1C
#define LABEL_BEP				0x1D
#define LABEL_CHA				0x1E
#define LABEL_ALARM				0x1F
#define LABEL_DATA				0x20
#define LABEL_SET				0x21
#define LABEL_ON				0x22
#define LABEL_OFF				0x23
#define LABEL_LIST_D				0x24
#define LABEL_LIST_A				0x25
#define LABEL_NULL				0x26
#define LABEL_RTC_D				0x27
#define LABEL_RTC_T				0x28
#define LABEL_ALARM_T				0x29
#define LABEL_YEAR				0x2A
#define LABEL_MONTH				0x2B
#define LABEL_DAY				0x2C
#define LABEL_HOUR				0x2D
#define LABEL_MINUTE				0x2E
#define LABEL_SECOND				0x2F
#define LABEL_ERASE				0x30
#define LABEL_ERASE_W				0x31
#define LABEL_PASSWORD				0x32
#define LABEL_BAT				0x33
#define LABEL_SUM				0x34
#define LABEL_MULTI				0x35
#define LABEL_STATE				0x36
#define LABEL_STATU0				0x37
#define LABEL_STATU1				0x38
#define LABEL_STATU2				0x39
#define LABEL_POWER				0x3A
#define LABEL_RTC				0x3B
#define LABEL_HD_ADDRESS			0x3C
#define LABEL_NET_ADDRESS			0x3D
#define LABEL_NET_STATUS			0x3E
#define LABEL_PHONE_1_3				0x3F
#define LABEL_PHONE_4_7				0x40
#define LABEL_PHONE_8_11			0x41
#define LABEL_GPRS				0x42
#define LABEL_REBOOT				0x43
#define LABEL_OUT				0x44
#define LABEL_INTERVAL				0x45
#define LABEL_INTERVAL_MAIL_ALARM		0x46



// nixietube bat
// 接了电池，非充电，电池框子闪烁，内部不显示
#define BAT_NONE				0x00                
// 接了电池，非充电，电池框子闪烁，内部不显示
#define BAT_0_3					0x01                
// 接了电池，非充电，电池框子显示，内部显示1格
#define BAT_1_3					0x02                
// 接了电池，非充电，电池孔子显示，内部显示2格
#define BAT_2_3					0x03                
// 接了电池，非充电，电池框子显示，内部显示
#define BAT_3_3					0x04                
// 接了电池，充电中，电池框子显示，内部跑动
#define BAT_CHARGE				0x05                
// 接了电池，充满了，电池框子闪烁，内部显示
#define BAT_CHARGE_FULL				0x06                
// 没有接电池，只接了充电器，电池框子不显示，内部显示
#define BAT_NONE_CHARGE				0x07                
// 接了电池，非充电，彻底没电，直接关机
#define BAT_OFF					0x0f                


// nixietube Symbol 
#define SYMBOL_LEL  			0x01
#define SYMBOL_PPM  			0x02
#define SYMBOL_VOL  			0x03
#define SYMBOL_LOW  			0x04
#define SYMBOL_HIGH 			0x05
#define SYMBOL_STEL 			0x06
#define SYMBOL_TWA  			0x07
#define SYMBOL_RIGHT    		0x08
#define SYMBOL_ERROR    		0x09
#define SYMBOL_ALARM    		0x0A
#define SYMBOL_ZERO			0x0B
#define SYMBOL_GAS			0x0C
#define SYMBOL_TIME			0x0D
#define SYMBOL_BAT_0_3			0x0E
#define SYMBOL_BAT_1_3			0x0F
#define SYMBOL_BAT_2_3			0x10
#define SYMBOL_BAT_3_3			0x11
#define SYMBOL_BAT_3_0			0x12
#define SYMBOL_POINT_HHHHH		0x13
#define SYMBOL_POINT_HHHHXH		0x14
#define SYMBOL_POINT_HHHXHH		0x15
#define SYMBOL_POINT_HHXHHH		0x16
#define SYMBOL_POINT_HXHHHH		0x17


// nixietube character
#define CHARACTER_0		0
#define CHARACTER_1		1
#define CHARACTER_2		2
#define CHARACTER_3		3
#define CHARACTER_4		4
#define CHARACTER_5		5
#define CHARACTER_6		6
#define CHARACTER_7		7
#define CHARACTER_8		8
#define CHARACTER_9		9
#define CHARACTER_A		10
#define CHARACTER_b		11
#define CHARACTER_C		12
#define CHARACTER_d		13
#define CHARACTER_E		14
#define CHARACTER_F		15
#define CHARACTER_a		16
#define CHARACTER_c		17
#define CHARACTER_e		18
#define CHARACTER_G		19
#define CHARACTER_g		CHARACTER_9
#define CHARACTER_H		20
#define CHARACTER_h		21
#define CHARACTER_j		22
#define CHARACTER_L		23
#define CHARACTER_N		24
#define CHARACTER_n		25
#define CHARACTER_O		CHARACTER_0
#define CHARACTER_o		26
#define CHARACTER_P		27
#define CHARACTER_q		28
#define CHARACTER_r		29
#define CHARACTER_S		CHARACTER_5
#define CHARACTER_t		30
#define CHARACTER_U		31
#define CHARACTER_u		32
#define CHARACTER_V		CHARACTER_U
#define CHARACTER_y		33
#define CHARACTER_		34
#define CHARACTER__		35
#define CHARACTER_i		36
#define CHARACTER_NULL		37


#endif
