/**
 * @file    key.c
 * @brief   按键
 * @author  ptz
 * @email   ptz19861212@163.com
 * @version 0.0.1
 * @date    2013-12-03 09:14:23 星期二 
 * @history (1).2013-12-03 09:14:23 星期二 create
 */
/* Copyright (C)
 * 
 * My own license
 * All right reserved
 * 
 */

#include "key_in.h"

/**
 * @brief   key rcc config
 */

static void RCC_Configuration(void)
{
	// 引脚时钟配置
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
}


/**
 * @brief   key gpio config
 */
static void GPIO_Configuration(void)
{
	// 引脚配置
	GPIO_InitTypeDef GPIO_InitStructure;

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	//GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 |\
										GPIO_Pin_6 |\
										GPIO_Pin_7 |\
										GPIO_Pin_8;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
}


/**
 * @brief   按键适时读取并转化为8位数据
 */
uint8_t KEY_Read(void)
{
	uint16_t lKey = 0;

	lKey = GPIO_ReadInputData(GPIOB);
	lKey ^= 0xFFFF;
	lKey >>= 5;
	lKey &= ~(0xFFFF << CONFIG_KEYS_NUMBER);

	return (uint8_t)lKey;
}


// 按键计数数组
static uint8_t sKeyCount[CONFIG_KEYS_NUMBER];
// 按键持续按数组，这个是为了计数长按的时间，数值要除 10 才能得到长按时间
static uint8_t sKeyContinue[CONFIG_KEYS_NUMBER];
// 按键长按数组
static uint8_t sKeyLong[CONFIG_KEYS_NUMBER];
// 短按
my_key_t gKeyShort = 0x00;
// 长时间的按键
my_key_t gKeyLong = 0x00;
// 按键一直按住，所产生的快速连续按键效果
my_key_t gKeyContinue = 0x00;
// 本次触发的按键
my_key_t gKeyTrg = 0x00;
// 当前按下的按键
my_key_t gKeyState = 0x00;


/**
 * @brief   key get
 */
void KEY_Get(void)
{
	static uint8_t sKeyLast = 0x00;
	static uint8_t sKeyReadData = 0x00;
	uint8_t lKeyNow, lI;

	//lKeyNow = KEY_NOW;
	//KEY_IN(lKeyNow);

	// 获得当前按键
	lKeyNow = KEY_Read();
	// 和上次按键相与，用于去抖动
	sKeyReadData = (lKeyNow & sKeyLast);
	sKeyLast = lKeyNow;
	// 触发新的按键
	gKeyTrg = (sKeyReadData & (sKeyReadData ^ gKeyState));
	// 当前的按键
	gKeyState = sKeyReadData;

	for (lI = 0; lI < CONFIG_KEYS_NUMBER; lI++)
	{
		if (gKeyState & (1 << lI))
		{
			sKeyCount[lI] += 0x01;

			if (sKeyCount[lI] < 50)
			{
				gKeyContinue &= (~(1 << lI));
			}
			if (sKeyCount[lI] == 50)
			{
				gKeyLong |= (1 << lI);
				// it`s for the key continue press
				// the key continue will slowly
				sKeyCount[lI] = 45;
				gKeyContinue |= (1 << lI);

				// 连续按数组
				sKeyContinue[lI]++;

				// 多次的连续按数组导致长按数组+1
				if (sKeyContinue[lI] >= CONFIG_KEYS_CONT_COUNT)
				{
					sKeyLong[lI]++;
					sKeyContinue[lI] = 0;
				}
			}
		}
		else if((sKeyCount[lI] < 45) && (sKeyCount[lI] > 0))
		{
			gKeyShort |= (1 << lI);
			sKeyCount[lI] = 0x00;
		}
		else
		{
			gKeyShort &= ((1 << lI) ^ 0xff);
			gKeyLong &= ((1 << lI) ^ 0xff);
			gKeyContinue &= ((1 << lI) ^ 0xff);
			sKeyCount[lI] = 0x00;
			sKeyContinue[lI] = 0x00;
			sKeyLong[lI] = 0x00;
		}
	}
}


/**
 * @brief   求指定按键的长按时间
 *
 * @param   lKey 指定的按键 类如 KEY_ENTER, KEY_UP 等等
 *
 * @return  长按的时间
 */
uint8_t KeyLongGet(my_key_t lKey)
{
	uint8_t lBit;
	my_err_t lErr;

	lErr = BitGet((uint8_t*)&lKey, &lBit, sizeof(my_key_t) << 3);

	if (lErr == ESUC)
	{
		return sKeyLong[lBit];
	}
	else
	{
		return 0;
	}
}


/**
 * @brief   key config
 */
void KEY_Init(void)
{
	RCC_Configuration();
	GPIO_Configuration();
}

