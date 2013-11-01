/**
 * @file    uc1701_in.h
 * @brief   UC1701驱动
 * @author  ptz
 * @email   ptz19861212@163.com
 * @version 0.0.1
 * @date    2013-08-08 14:23:12 星期四 
 * @history (1).2013-08-08 14:23:12 星期四 create
 */
/* Copyright (C)
 * 
 * My own license
 * All right reserved
 * 
 */

#ifndef __UC1701_IN_H__
#define __UC1701_IN_H__

#include <stm32f10x_gpio.h>
#include <stm32f10x_rcc.h>
#include "uc1701.h"
#include "my_define.h"
#include "rtthread.h"

// 引脚
//#define CONFIG_UC1701_PIN_PWR
//#define CONFIG_UC1701_PIN_RST

// 延时定义
#define UC1701_DELAY	\
			do { asm("nop"); } while(0)
#define UC1701_DELAY_2MS			rt_thread_delay(1)
#define UC1701_DELAY_6MS			rt_thread_delay(1)
#define UC1701_DELAY_120MS			rt_thread_delay(12)

// 引脚定义
#define UC1701_SCK_RCC				RCC_APB2Periph_GPIOA
#define UC1701_SCK_GPIO			GPIOA
#define UC1701_SCK_PIN				GPIO_Pin_5

#define UC1701_MISO_RCC				RCC_APB2Periph_GPIOA
#define UC1701_MISO_GPIO			GPIOA
#define UC1701_MISO_PIN				GPIO_Pin_6

#define UC1701_MOSI_RCC				RCC_APB2Periph_GPIOA
#define UC1701_MOSI_GPIO			GPIOA
#define UC1701_MOSI_PIN				GPIO_Pin_7

#define UC1701_CD_RCC				RCC_APB2Periph_GPIOA
#define UC1701_CD_GPIO				GPIOB
#define UC1701_CD_PIN				GPIO_Pin_0

#define UC1701_CS_RCC				RCC_APB2Periph_GPIOA
#define UC1701_CS_GPIO				GPIOA
#define UC1701_CS_PIN				GPIO_Pin_4

#ifdef CONFIG_UC1701_PIN_RST
#define UC1701_RST_RCC				RCC_APB2Periph_GPIOC
#define UC1701_RST_GPIO				GPIOC
#define UC1701_RST_PIN				GPIO_Pin_13
#endif	//#ifdef CONFIG_UC1701_PIN_RST

#ifdef CONFIG_UC1701_PIN_PWR
#define UC1701_PWR_RCC				RCC_APB2Periph_GPIOA
#define UC1701_PWR_GPIO				GPIOA
#define UC1701_PWR_PIN				GPIO_Pin_4
#endif	//#ifdef CONFIG_UC1701_PIN_PWR

#define UC1701_BG_RCC				RCC_APB2Periph_GPIOB
#define UC1701_BG_GPIO				GPIOB
#define UC1701_BG_PIN				GPIO_Pin_1

// 引脚动作定义
#define UC1701_SCK_LOW		\
			do {GPIO_ResetBits(UC1701_SCK_GPIO, UC1701_SCK_PIN);} while(0)
#define UC1701_SCK_HIGH		\
			do {GPIO_SetBits(UC1701_SCK_GPIO, UC1701_SCK_PIN);} while(0)

#define UC1701_MOSI_LOW		\
			do {GPIO_ResetBits(UC1701_MOSI_GPIO, UC1701_MOSI_PIN);} while(0)
#define UC1701_MOSI_HIGH	\
			do {GPIO_SetBits(UC1701_MOSI_GPIO, UC1701_MOSI_PIN);} while(0)

#define UC1701_CD_LOW		\
			do {GPIO_ResetBits(UC1701_CD_GPIO, UC1701_CD_PIN);} while(0)
#define UC1701_CD_HIGH	\
			do {GPIO_SetBits(UC1701_CD_GPIO, UC1701_CD_PIN);} while(0)

#define UC1701_CS_LOW		\
			do {GPIO_ResetBits(UC1701_CS_GPIO, UC1701_CS_PIN);} while(0)
#define UC1701_CS_HIGH	\
			do {GPIO_SetBits(UC1701_CS_GPIO, UC1701_CS_PIN);} while(0)

#ifdef CONFIG_UC1701_PIN_RST
#define UC1701_RST_LOW		\
			do {GPIO_ResetBits(UC1701_RST_GPIO, UC1701_RST_PIN);} while(0)
#define UC1701_RST_HIGH	\
			do {GPIO_SetBits(UC1701_RST_GPIO, UC1701_RST_PIN);} while(0)
#endif	//#ifdef CONFIG_UC1701_PIN_RST

#ifdef CONFIG_UC1701_PIN_PWR
#define UC1701_PWR_DOWN		\
			do {GPIO_ResetBits(UC1701_PWR_GPIO, UC1701_PWR_PIN);} while(0)
#define UC1701_PWR_UP	\
			do {GPIO_SetBits(UC1701_PWR_GPIO, UC1701_PWR_PIN);} while(0)
#endif	//#ifdef CONFIG_UC1701_PIN_PWR

#define UC1701_BG_OFF		\
			do {GPIO_ResetBits(UC1701_BG_GPIO, UC1701_BG_PIN);} while(0)
#define UC1701_BG_ON	\
			do {GPIO_SetBits(UC1701_BG_GPIO, UC1701_BG_PIN);} while(0)

// 命令定义
#define UC1701_CMD_CAL				0x00
#define UC1701_CMD_CAM				0x10
#define UC1701_CMD_PCL				0x28
#define UC1701_CMD_SL				0x40
#define UC1701_CMD_PA				0xB0
#define UC1701_CMD_PCM				0x20
#define UC1701_CMD_PMS				0x81
#define UC1701_CMD_PM				0x00
#define UC1701_CMD_DC1				0xA4
#define UC1701_CMD_DC0				0xA6
#define UC1701_CMD_DC2				0xAE
#define UC1701_CMD_LC0				0xA0
#define UC1701_CMD_LC1				0xC0
#define UC1701_CMD_SR				0xE2
#define UC1701_CMD_NOP				0xE3
#define UC1701_CMD_BR				0xA2
#define UC1701_CMD_ACS				0xE0
#define UC1701_CMD_ACR				0xEE
#define UC1701_CMD_PS				0x00
#define UC1701_CMD_APCS				0xFA
#define UC1701_CMD_APC				0x10

// 边界
#define UC1701_SEG_END				131
#define UC1701_LINE_END				63
#define UC1701_PAGE_END				7

#define UC1701_SEG_NUM				(UC1701_SEG_END + 1)
#define UC1701_LINE_NUM				(UC1701_LINE_END + 1)
#define UC1701_PAGE_NUM				(UC1701_PAGE_END + 1)

// 字符异或数值
#define UC1701_CHARACTER_DOT_SET			0x00
#define UC1701_CHARACTER_DOT_CLEAR			0xFF

#endif
