/**
 * @file    my_usart.h
 * @brief   usart
 * @author  ptz
 * @email   ptz19861212@163.com
 * @version 0.0.1
 * @date    2012-08-02 09:47:24 星期四 
 * @history (1).2012-08-02 09:47:24 星期四 create
 */
/* Copyright (C)
 * 
 * My own license
 * All right reserved
 * 
 */


#ifndef __MY_USART_H__
#define __MY_USART_H__

#include <stdint.h>


//USART STATUS FLAG
enum ENUM_USART_STATU
{
	USART_STATUS_IDLE,			//USART status idle
	USART_STATUS_RECEIVING,			//USART status receiveing
	USART_STATUS_DATA_PROCESSING,		//USART status processing
	USART_STATUS_TRANSMITING		//USART status transmiting
};


enum ENUM_USART_RUN_MODE
{
	USART_RUN_MODE_NORMAL,			//USART normal
	USART_RUN_MODE_ESCAPE,			//USART escape
	USART_RUN_MODE_COMMAND			//USART command
};


enum ENUM_USART_MASTER
{
	USART_MASTER_NONE,
	// always master
	USART_MASTER_ALWAYS
};


struct	S_Usart
{
	uint8_t Status;
	uint8_t RunMode;
	uint8_t Master;
	uint16_t TimeOut;
};


struct S_Usart_Address
{
	uint16_t SelfAddress;
	uint16_t DesAddress;
};

#define USART_START				0x7E
#define USART_END				0x55

#define USART_CMD_READ				0x05
#define USART_CMD_READ_RESPONSE			0x85


#define USART_CMD_ZERO				0x06
//#define USART_CMD_ZERO_RESPONSE			0x86
//#define USART_CMD_ZERO_RESPONSE_COMPLETE	0x87

#define USART_CMD_GAS				0x09
//#define USART_CMD_GAS_RESPONSE			0x89
//#define USART_CMD_GAS_RESPONSE_COMPLETE		0x8A
	
#define USART_CMD_ADDRESS			0x0C

//#define USART_CMD_ADDRESS_RESPONSE		0x8C

#define USART_CMD_CUT_OFF			0x0D
#define USART_CMD_PUT_ON			0x0E

#define USART_CMD_INTERVAL			0x0F
#define USART_CMD_INTERVAL_RESPONSE		0x8F


#endif
