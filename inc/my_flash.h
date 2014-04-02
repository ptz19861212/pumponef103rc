/**
 * @file    my_flash.h
 * @brief   
 * @author  ptz
 * @email   ptz19861212@163.com
 * @version 0.0.1
 * @date    2014-01-02 14:32:06 星期四 
 * @history (1).2014-01-02 14:32:06 星期四 create
 */
/* Copyright (C)
 * 
 * My own license
 * All right reserved
 * 
 */

#ifndef __MY_FLASH_H__
#define __MY_FLASH_H__


typedef struct
{
	// 开始
	uint32_t Start;
	// 结束
	uint32_t End;
}S_Flash_Address;

//typedef struct
//{
//	// 开始的偏移量
//	uint32_t Start;
//	// 结束的
//	uint32_t End;
//}S_Flash_Offset;

typedef struct
{
	// 页面的大小
	uint32_t Size;
	// 页面的数目
	uint32_t Num;
}S_Flash_Page;

typedef struct
{
	// 符合页的首末地址
	S_Flash_Address Addr;
	// 页
	S_Flash_Page Page;
}S_Flash_Erase;

typedef struct
{
	// 实际的起始和结束地址
	S_Flash_Address Addr;
	// 写入数组
	uint16_t* Array;
}S_Flash_Write;

typedef struct
{
	S_Flash_Address Addr;
	// 读取数组
	uint8_t* Array;
}S_Flash_Read;

//typedef struct
//{
//	// 需要写入地址
//	S_Flash_Address AddrReal;
//	// 实际页的起始和结束地址
//	S_Flash_Address AddrPage;
//	// 写入页面
//	S_Flash_Page Page;
//	// 写入页面的位置
//	S_Flash_Offset Offset;
//	// 写入数组
//	const uint8_t* Array;
//}S_Flash_Write;



#endif
