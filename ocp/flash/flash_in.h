/**
 * @file    flash_in.h
 * @brief   FLASH 编程
 * @author  ptz
 * @email   ptz19861212@163.com
 * @version 0.0.1
 * @date    2013-12-11 15:00:13 星期三 
 * @history (1).2013-12-11 15:00:13 星期三 create
 */
/* Copyright (C)
 * 
 * My own license
 * All right reserved
 * 
 */

#ifndef __FLASH_IN_H__
#define __FLASH_IN_H__

#include "stm32f10x_flash.h"
#include "flash.h"


// 一页大小
#define FLASH_PAGE_SIZE				((uint16_t)0x800)

// 写入开始的页
//#define CONFIG_FLASH_PAGE_WRITE_ADDR_START		((uint32_t)0x0803F800)
//#define CONFIG_FLASH_PAGE_WRITE_ADDR_END			((uint32_t)0x0803FFFF)


#endif
