/**
 * @file    config_bsp.h
 * @brief   config
 * @author  ptz
 * @email   ptz19861212@163.com
 * @version 0.0.1
 * @date    2013-11-26 10:44:57 星期二 
 * @history (1).2013-11-26 10:44:57 星期二 create
 */
/* Copyright (C)
 * 
 * My own license
 * All right reserved
 * 
 */

#ifndef __CONFIG_BSP_H__
#define __CONFIG_BSP_H__

#include "my_compile.h"

#define DEFINE_DEBUG

#ifdef DEFINE_DEBUG
#define DEBUG_Printf			rt_kprintf
#else
#define DEBUG_Printf
#endif

#define DEBUG_ON					PRE_COMP_ENABLE
#define DEBUG_OFF					PRE_COMP_DISABLE

// 测试某项功能
// 测试电池
#define DEBUG_TEST_BAT			DEBUG_OFF


// 设备软件版本号
// V108 在自检的时候增加了量程的显示
// V107 软件改动了一下，把气体的调用的函数放到一个结构体里面了，然后
//			具体气体头文件的函数对应也一起放到了抽象气体头文件里面了
// V106 修正了便携板子取平均值以后ADC数值不对的问题，原因是因为ADC部分
//			设定去平均数值的函数的调用，要注意ADC是16位的，所以Num 必须
//			是 sizeof()/2，泵的板子没问题，应该是内存上面没有读写到
//			ADC求滑动平均的后半截，否则的话，也会同样的不正确了，因为
//			内存使用超界了
//		 把ADC取平均的数组个数改为两个
//		 针对氧气修正了一个小BUG，设置语言时候的问题，原因是在 menu_param
//			文件中的#if 有一个写错了，写为了GAS_GAS，而不是CONFIG_GAS
// V105 显示部分的CD引脚的RCC和GPIO不一致，一个是GPIOA，一个是GPIOB
// V104 修正了电池低电量充电的时候，屏幕会瞬间显示其他东西，原因是因为在
//			电量检测的时候没有跳过充电状态，这样就会先显示电量低，然后瞬间
//			显示充电状态.
// V103 改变了泵的图标，不转了
// V102 修正了单位只显示后3位的问题(%LEL,%VOL),不影响PPM
// V101 调整了液晶对比度，让显示颜色更明显
// V100 增加了充电完成
// v013 添加了看门狗 1S
// v012 用于第二次电池测试，关闭了报警功能
// v011 用于第二次的电池测试，电池ADC 实时显示，电池等级基于第一次放电测试
#define DEVICE_VERSION						"1.08"


// 仪器多长时间位1秒的计数次数 20ms * 50 = 1000ms
#define DEVICE_TIME_SECOND					50
// 仪器多长时间显示一次的计数次数 20ms * 50 = 1000ms
#define DEVICE_DISPLAY_FRESH				50
// 风扇旋转动画最大次数
//#define DEVICE_FAN_DISP_MAX					4
// 风扇进气等级的最大
#define DEVICE_FAN_MAX						3

// 电池容量 0%
#define DEVICE_BAT_VALUE_0						0
//#define DEVICE_BAT_ADC_0							1986
//#define DEVICE_BAT_ADC_0							2111
#define DEVICE_BAT_ADC_0							2141
// 电池容量 20%
#define DEVICE_BAT_VALUE_20						20
//#define DEVICE_BAT_ADC_20						2110
//#define DEVICE_BAT_ADC_20						2130
#define DEVICE_BAT_ADC_20						2233
// 电池容量 40%
#define DEVICE_BAT_VALUE_40						40
//#define DEVICE_BAT_ADC_40						2234
//#define DEVICE_BAT_ADC_40						2249
#define DEVICE_BAT_ADC_40						2301
// 电池容量 60%
#define DEVICE_BAT_VALUE_60						60
//#define DEVICE_BAT_ADC_60						2358
//#define DEVICE_BAT_ADC_60						2368
#define DEVICE_BAT_ADC_60						2355
// 电池容量 80%
#define DEVICE_BAT_VALUE_80						80
//#define DEVICE_BAT_ADC_80						2482
//#define DEVICE_BAT_ADC_80						2487
#define DEVICE_BAT_ADC_80						2438
// 电池容量 100%
#define DEVICE_BAT_VALUE_100					100
//#define DEVICE_BAT_ADC_100						2606
#define DEVICE_BAT_ADC_100						2557

// 充电状态比非充电状态大约要多出ADC 43 左右
// 考虑到电池的不一致性，所以这边就ADC标准就低一些
#define DEVICE_BAT_ADC_FULL						2545

/************************************* 语言初始 *************************************/
#define CONFIG_LANGUAGE							LANGUAGE_EN

// 设备报警
#define DEVICE_STATE_DETECT_EN					"Detect"
#define DEVICE_STATE_DETECT_CN					"检测"
//#define DEVICE_STATE_DETECT_CN					"detect"
#define DEVICE_STATE_ZERO_EN					"CaliZero"
#define DEVICE_STATE_ZERO_CN					"标零"
//#define DEVICE_STATE_ZERO_CN					"zero"
#define DEVICE_STATE_GAS_EN						"CaliGas"
#define DEVICE_STATE_GAS_CN						"标气"
//#define DEVICE_STATE_GAS_CN						"gas"
#define DEVICE_ALARM_LOWER_EN					"Lower"
#define DEVICE_ALARM_LOWER_CN					"低报"
//#define DEVICE_ALARM_LOWER_CN					"lower"
#define DEVICE_ALARM_UPPER_EN					"Upper"
#define DEVICE_ALARM_UPPER_CN					"高报"
//#define DEVICE_ALARM_UPPER_CN					"upper"


/******************************** 保存数据设置 **********************************/
#define CONFIG_FLASH_SAVE_ADDR_START				((uint32_t)0x0803F800)
#define CONFIG_FLASH_SAVE_BAK_ADDR_START			((uint32_t)0x0803F000)


/******************************** 显示相关 ************************************/
// 是否使用段式屏幕
//#define CONFIG_LCD_NIXIETUBE

// 使用点阵屏幕
#ifndef CONFIG_LCD_NIXIETUBE

// LCD 显示芯片
#define CONFIG_LCD_CHIP_UC1701

#endif


/******************************* 泵相关 ******************************/
// 设备带吸气泵
#define CONFIG_USING_PUMP

/******************************* 气体数值范围相关 ******************************/
// gas value 16位数字
#define CONFIG_GAS_VALUE_BITS					16

/******************************* 菜单相关 ******************************/
// menu 8位数字
#define CONFIG_MENU_BITS							8

/******************************* 灯的数目 ******************************/
#define CONFIG_LED_NUM							1

/******************************* 报警设置 *************************************/
#define CONFIG_ALARM_SOUND							PRE_COMP_ENABLE
#define CONFIG_ALARM_VIBRATION						PRE_COMP_ENABLE

/******************************* 生产日期 ******************************/
#define CONFIG_MANF_DATE_MON		1
#define CONFIG_MANF_DATE_DAY		22
#define CONFIG_MANF_DATE_YEAR		2014

/******************************* 质保日期 ******************************/
#define CONFIG_WARRANTY_DATE_MON		1
#define CONFIG_WARRANTY_DATE_DAY		22
#define CONFIG_WARRANTY_DATE_YEAR		2016



// 气体
#define CONFIG_CO__1000			PRE_COMP_DISABLE
#define CONFIG_CO__2000			PRE_COMP_DISABLE
#define CONFIG_H2__1000			PRE_COMP_DISABLE
#define CONFIG_H2__2000			PRE_COMP_DISABLE
#define CONFIG_H2S__100			PRE_COMP_DISABLE
#define CONFIG_EX__100			PRE_COMP_DISABLE
#define CONFIG_EX__100_0			PRE_COMP_ENABLE
#define CONFIG_O2__30_0			PRE_COMP_DISABLE
#define CONFIG_C2H4O__100_0		PRE_COMP_DISABLE
#define CONFIG_CH4O__100_0		PRE_COMP_DISABLE

#if ((CONFIG_CO__1000 == PRE_COMP_ENABLE) || \
		(CONFIG_CO__2000 == PRE_COMP_ENABLE))
	#include "config_gas_co.h"
#elif ((CONFIG_H2__1000 == PRE_COMP_ENABLE) || \
		(CONFIG_H2__2000 == PRE_COMP_ENABLE))
	#include "config_gas_h2.h"
#elif (CONFIG_H2S__100 == PRE_COMP_ENABLE)
	#include "config_gas_h2s.h"
#elif ((CONFIG_EX__100 == PRE_COMP_ENABLE) || \
		(CONFIG_EX__100_0 == PRE_COMP_ENABLE))
	#include "config_gas_ex.h"
#elif (CONFIG_O2__30_0 == PRE_COMP_ENABLE)
	#include "config_gas_o2.h"
#elif (CONFIG_C2H4O__100_0 == PRE_COMP_ENABLE)
	#include "config_gas_c2h4o.h"
#elif (CONFIG_CH4O__100_0 == PRE_COMP_ENABLE)
	#include "config_gas_ch4o.h"
#endif





//#ifdef DEBUG
//#define D_STR(_STR_)   printf("f:%s(l:%d)%s\n",__FILE__,__LINE__,_STR_);
//#define D_LINE         printf("f:%s(l:%d)-fn:%s\n",__FILE__,__LINE__,__FUNCTION__);
//#define D_CHAR(_CHAR_) printf("f:%s(l:%d)%d\n",__FILE__,__LINE__,_CHAR_);
//#define D_HEX(_HEX_)   printf("f:%s(l:%d)[%x]\n",__FILE__,__LINE__,_HEX_);
//#else
//#define D_STR(_STR_)   ;
//#define D_LINE         ;
//#define D_CHAR(_CHAR_) ;
//#define D_HEX(_HEX_)   ;
//#endif

#endif
