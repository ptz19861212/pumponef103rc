/**
 * @file    adc_in.h
 * @brief   stm32f103rc-adc
 * @author  ptz
 * @email   ptz19861212@163.com
 * @version 0.0.1
 * @date    2013-11-22 14:56:14 星期五 
 * @history (1).2013-11-22 14:56:14 星期五 create
 */
/* Copyright (C)
 * 
 * My own license
 * All right reserved
 * 
 */

#ifndef __ADC_IN_H__
#define __ADC_IN_H__

#include "stm32f10x_rcc.h"
#include "stm32f10x_dma.h"
#include "config_bsp.h"
#include "my_errno.h"
#include "adc.h"
#include "rtdef.h"

// adc channel trigger number
#define CONFIG_ADC_TRIG_NUM			128

// adc channel number
#define CONFIG_ADC_CHAN_NUM			3

// adc dma size
#define CONFIG_ADC_DMA_SIZE			(CONFIG_ADC_TRIG_NUM * CONFIG_ADC_CHAN_NUM)

// enable ADC1 DMA
#define DEFINE_DMA1_ADC1

// enable ADC3 DMA
//#define DEFINE_DMA2_ADC3

// enable ADC GPIOA
//#define DEFINE_ADC_GPIOA

// enable ADC GPIOB
//#define DEFINE_ADC_GPIOB

// enable ADC GPIOC
#define DEFINE_ADC_GPIOC


// ADCPLK MAX = 14MHZ，PCLK2 = 72MHZ，so 72/6 = 12MHZ
// ADCCLK = 12MHZ
#define CONFIG_RCC_DIV				RCC_PCLK2_Div6

// adc sample time
#define CONFIG_SAMPLE_TIME			ADC_SampleTime_239Cycles5

// enable adc clock and gpio clock
#define CONFIG_RCC_ADC_GPIO			RCC_APB2Periph_ADC1 |\
										RCC_APB2Periph_ADC2 |\
										RCC_APB2Periph_GPIOC

#ifdef DEFINE_ADC_GPIOA
// config GPIOA
#define CONFIG_GPIOA_PIN
#endif

#ifdef DEFINE_ADC_GPIOB
// config GPIOA
#define CONFIG_GPIOB_PIN
#endif

#ifdef DEFINE_ADC_GPIOC
// config GPIOA
#define CONFIG_GPIOC_PIN				GPIO_Pin_0 |\
										GPIO_Pin_1 |\
										GPIO_Pin_2
#endif

#endif
