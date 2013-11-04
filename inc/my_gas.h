/**
 * @file    my_gas.h
 * @brief   gas
 * @author  ptz
 * @email   ptz19861212@163.com
 * @version 0.0.1
 * @date    2012-08-07 15:24:16 星期四 
 * @history (1).2012-08-07 15:24:16 星期四 create
 */
/* Copyright (C)
 * 
 * My own license
 * All right reserved
 * 
 */

#ifndef __MY_GAS_H__
#define __MY_GAS_H__

#include <stdint.h>


#define GAS_ADC_BUFFER_SIZE_BITS		5	
#define GAS_ADC_BUFFER_SIZE			(1 << GAS_ADC_BUFFER_SIZE_BITS)

struct S_Gas_Channel_Const
{
	//the direct of gas sensor, 0 positive, 1 negative, 2 both
    	uint8_t Direct;                       	
	//gas name
    	uint8_t Name;                             
	//the point of gas value
    	uint8_t Point;
	//range of gas value
    	uint16_t Range;
};

struct S_Gas_Channel_Save
{
	//gas value trig low alarm
    	uint16_t Low;                           
	//gas value trig high alarm
    	uint16_t High;                          
	//gas value in the succesful gas service routine last time
	uint16_t GasValue;					
	//adc value in the successful gas service routine last time 
	uint16_t GasAdc;		
	//adc value of zero in the successful gas service routine last time
	uint16_t GasZeroAdc;
	//adc value of zero last time
	uint16_t ZeroAdc;
	//is this struct member saved?
	union
	{
		uint8_t Control;
		struct
		{
			uint8_t LOW			:	1;		//low
			uint8_t HIGH			:	1;
			uint8_t GV			:	1;
			uint8_t GA			:	1;			
			uint8_t GZA			:	1;
			uint8_t ZA			:	1;
			uint8_t RESERVE			:	2;
		}Control_Bits;
	};
};

struct S_Gas_Channel_Temp
{
	//gas value now
    	uint16_t Value;
	//sum of value in the zero or gas service routine
    	uint32_t Sum;                           
	//gas adc now
    	uint16_t Adc;
	//gas adc array now
    	uint16_t AdcBuffer[GAS_ADC_BUFFER_SIZE];
	//the sum of gas adc array now
    	uint32_t AdcTotal;
	//the counter of the gas adc array now
    	uint8_t AdcBufferCounter;
	//the adc in the gas service rootine this time
	uint16_t GasAdc;
	//the gas value in the gas service rootine this time 
	uint16_t GasValue;
	//the status of gas, nomal? low alarm? high alarm?
	uint8_t Alarm;
	//the status of service routime? nomal? zero? gas?
	uint8_t Status;
	//blink the value when reach it`s range
	uint8_t FullBlink;
	//error in the zero or gas service routine this time
	uint8_t Error;
};

struct S_Gas_Channel
{
	struct S_Gas_Channel_Const GC;
	struct S_Gas_Channel_Save GS;
	struct S_Gas_Channel_Temp GT;
};

#define GAS_DIRECT_POSITIVE				0
#define GAS_DIRECT_NEGATIVE				1
#define GAS_DIRECT_BOTH					2

#define GAS_ALARM_NORMAL				0
#define GAS_ALARM_LOW					1
#define GAS_ALARM_HIGH					2

#define GAS_ERROR_NONE					0
#define GAS_ERROR_ZERO					1
#define GAS_ERROR_GAS					2

#define GAS_STATUS_NORMAL				0
#define GAS_STATUS_ZERO					1
#define GAS_STATUS_GAS					2

#define GAS_UNIT_NONE					0
#define GAS_UNIT_PPM					1
#define GAS_UNIT_LEL					2
#define GAS_UNIT_VOL					3



#define GAS_NAME_O2                                     0x01
#define GAS_NAME_EX                                     0x02
#define GAS_NAME_CO                                 	0x03
#define GAS_NAME_H2S                         		0x04
#define GAS_NAME_CL2					0x08
#define GAS_NAME_PH3					0x09

#define GAS_NAME_HF						18
#define GAS_NAME_SO2F2						22


#endif
