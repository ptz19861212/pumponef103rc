/**
 * @file    adc.h
 * @brief   stm32f103rc-adc
 * @author  ptz
 * @email   ptz19861212@163.com
 * @version 0.0.1
 * @date    2013-11-22 14:55:27 星期五 
 * @history (1).2013-11-22 14:55:27 星期五 create
 */
/* Copyright (C)
 * 
 * My own license
 * All right reserved
 * 
 */

#ifndef __ADC_H__
#define __ADC_H__

/**
 * @brief   adc config
 */
void ADC_Configuration(void);


/**
 * @brief   等待一个周期的adc转换完成
 */
void AdcWait(void);


/**
 * @brief   等待一个周期的adc转换完成
 */
void AdcSuspend(void);


/**
 * @brief   等待一个周期的adc转换完成
 */
void AdcResume(void);


/**
 * @brief   adc buffer get
 *
 * @param   lIndex is the channel index
 *
 * @param   *lBuf is the address of one channel array
 *
 * @param   *lSize is the size of one channel array
 *
 * @return  error code
 */
int32_t AdcBufGet(uint32_t lIndex, uint16_t **lBuf, uint32_t *lSize);


/**
 * @brief   adc reference buffer address
 *
 * @param   *lBufRef is the address of reference buffer
 */
void AdcRefBufGet(uint16_t **lBufRef);

#endif
