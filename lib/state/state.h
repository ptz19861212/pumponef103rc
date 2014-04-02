/**
 * @file    status.h
 * @brief   
 * @author  ptz
 * @email   ptz19861212@163.com
 * @version 0.0.1
 * @date    2013-12-03 12:55:09 星期二 
 * @history (1).2013-12-03 12:55:09 星期二 create
 */
/* Copyright (C)
 * 
 * My own license
 * All right reserved
 * 
 */

#ifndef __STATE_H__
#define __STATE_H__


#include "my_gas.h"
#include "my_device.h"

/**
 * @brief   数据设置写入
 */
void SaveWrite(void);


/**
 * @brief   自检状态转换为检测状态
 */
void StateSelfCheckToDetect(void);


/**
 * @brief   状态转换为菜单状态
 */
void StateDetectToMenu(void);


/**
 * @brief   状态转换为检测状态
 */
void StateMenuToDetect(void);


/**
 * @brief   菜单状态转换为输入状态
 */
void StateMenuToInput(void);


/**
 * @brief   输入状态转换为菜单状态
 */
void StateInputToMenu(void);


/**
 * @brief   菜单状态转换为倒计时状态
 */
void StateInputToCountdown(void);


/**
 * @brief   倒计时状态转换为菜单状态
 */
void StateCountdownToMenu(void);


/**
 * @brief   倒计时状态转换为结果状态
 */
void StateCountdownToResult(void);


/**
 * @brief   结果状态转换为菜单状态
 */
void StateResultToMenu(void);


/**
 * @brief   结果状态转换为检测状态
 */
void StateResultToDetect(void);


/**
 * @brief   检测状态转换为关机状态
 */
void StateDetectToShutdown(void);


/**
 * @brief   关机状态转换为检测状态
 */
void StateShutdownToDetect(void);


/**
 * @brief   关机状态转换为断电状态
 */
void StateShutdownToPowerOff(void);


/**
 * @brief   提示状态转换为检测状态
 */
void StateInfoToDetect(void);


/**
 * @brief   检测状态转换为提示状态
 */
void StateDetectToInfo(void);


/**
 * @brief   计数允许显示控制初始化
 */
void DeviceDispCountInit(void);


/**
 * @brief   获得气体结构体的指针
 *
 * @param   lpGas 气体结构体指针的地址
 */
void StateGasPointGet(S_Gas** lpGas);


/**
 * @brief   获得设备结构体的指针
 *
 * @param   lpDev 设备结构体指针的地址
 */
void StateDevicePointGet(S_Device** lpDev);


/**
 * @brief   state init
 */
void StateInit(void);


/**
 * @brief   status handler config
 */
void StateHandler(void);



#endif
