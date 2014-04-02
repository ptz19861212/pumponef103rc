/**
 * @file    flash.h
 * @brief   FLASH 编程
 * @author  ptz
 * @email   ptz19861212@163.com
 * @version 0.0.1
 * @date    2013-12-11 14:59:41 星期三 
 * @history (1).2013-12-11 14:59:41 星期三 create
 */
/* Copyright (C)
 * 
 * My own license
 * All right reserved
 * 
 */

#ifndef __FLASH_H__
#define __FLASH_H__

#include "my_flash.h"

/**
 * @brief   FLASH 写入
 *
 * @param   lpWrite
 */
void FlashWrite(S_Flash_Write* lpWrite);


/**
 * @brief   FLASH 读取
 *
 * @param   lpFlash
 */
void FlashRead(S_Flash_Read* lpFlash);

#endif
