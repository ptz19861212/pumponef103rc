/**
 * @file    key.h
 * @brief   按键
 * @author  ptz
 * @email   ptz19861212@163.com
 * @version 0.0.1
 * @date    2013-12-03 09:14:47 星期二 
 * @history (1).2013-12-03 09:14:47 星期二 create
 */
/* Copyright (C)
 * 
 * My own license
 * All right reserved
 * 
 */

#ifndef __KEY_H__
#define __KEY_H__


// 这个是和有几个按键相关的，比如说8个以下，就是uint8_t,16个以下就是uint16_t
typedef uint8_t my_key_t;


/**
 * @brief   处理一次按键
 */
void KEY_Get(void);


/**
 * @brief   求指定按键的长按时间
 *
 * @param   lKey 指定的按键 类如 KEY_ENTER, KEY_UP 等等
 *
 * @return  长按的时间
 */
uint8_t KeyLongGet(my_key_t lKey);


/**
 * @brief   key config
 */
void KEY_Init(void);


/******************* 按键含义定义 ****************************/
#define CONFIG_KEY_ENTER_BIT				3
#define CONFIG_KEY_DOWN_BIT					2
#define CONFIG_KEY_UP_BIT					1
#define CONFIG_KEY_SPECIAL_BIT				0




// 短按
extern my_key_t gKeyShort;
// 长时间的按键
extern my_key_t gKeyLong;
// 按键一直按住，所产生的快速连续按键效果
extern my_key_t gKeyContinue;
// 本次触发的按键
extern my_key_t gKeyTrg;
// 当前按下的按键
extern my_key_t gKeyState;


#define KEY_ENTER						(1 << CONFIG_KEY_ENTER_BIT)
#define KEY_DOWN						(1 << CONFIG_KEY_DOWN_BIT)
#define KEY_UP						(1 << CONFIG_KEY_UP_BIT)
#define KEY_SPECIAL					(1 << CONFIG_KEY_SPECIAL_BIT)
#define KEY_NONE						0x00

#endif
