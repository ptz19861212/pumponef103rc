/**
 * @file    adc.c
 * @brief   stm32f103rc-adc
 * @author  ptz
 * @email   ptz19861212@163.com
 * @version 0.0.1
 * @date    2013-11-22 14:50:21 星期五 
 * @history (1).2013-11-22 14:50:21 星期五 create
 */
/* Copyright (C)
 * 
 * My own license
 * All right reserved
 * 
 */

#include "adc_in.h"


/**
 * @brief   adc rcc config
 */
static void RCC_Configuration(void)
{
	// ADCPLK MAX = 14MHZ，PCLK2 = 72MHZ，so 72/6 = 12MHZ
	// ADCCLK = 12MHZ
	RCC_ADCCLKConfig(CONFIG_RCC_DIV);

#ifdef DEFINE_DMA1_ADC1
	// Enable DMA1 clock
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
#endif

#ifdef DEFINE_DMA2_ADC3
	// Enable DMA2 clock
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA2, ENABLE);
#endif

	// Enable ADC1 ADC2 clock and GPIOC clock
	RCC_APB2PeriphClockCmd(CONFIG_RCC_ADC_GPIO, ENABLE);
}


/**
 * @brief   adc gpio config
 */
static void GPIO_Configuration(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	// config GPIO as analog input
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;

#ifdef DEFINE_ADC_GPIOA
	GPIO_InitStructure.GPIO_Pin = CONFIG_GPIOA_PIN;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
#endif

#ifdef DEFINE_ADC_GPIOB
	GPIO_InitStructure.GPIO_Pin = CONFIG_GPIOB_PIN;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
#endif

#ifdef DEFINE_ADC_GPIOC
	GPIO_InitStructure.GPIO_Pin = CONFIG_GPIOC_PIN;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
#endif
}


/**
 * @brief   adc nvic config
 */
static void NVIC_Configuration(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;

	/* Enable DMA1 channel6 IRQ Channel */
	NVIC_InitStructure.NVIC_IRQChannel = DMA1_Channel1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}


// 一个周期的ADC转换完成信号量
static struct rt_semaphore sSemAdc;

/**
  * @brief  This function handles DMA1 Channel 1 interrupt request.
  * @param  None
  * @retval None
  */
void DMA1_Channel1_IRQHandler(void)
{
	/* Test on DMA1 Channel6 Transfer Complete interrupt */
	if(DMA_GetITStatus(DMA1_IT_TC1))
	{
		/* Clear DMA1 Channel6 Half Transfer, Transfer Complete and Global
		 * interrupt pending bits */
		DMA_ClearITPendingBit(DMA1_IT_GL1);


		// 保证信号量最多就为1，是一个二值信号量
		if (sSemAdc.value == 0)
		{
			rt_sem_release(&sSemAdc);
		}
	}
}


/**
 * @brief   等待一个周期的adc转换完成
 */
void AdcWait(void)
{
	// 等待一个周期ADC完成的信号量
	rt_sem_take(&sSemAdc, RT_WAITING_FOREVER);
}


/**
 * @brief   等待一个周期的adc转换完成
 */
void AdcSuspend(void)
{
	TIM_Cmd(TIM2, DISABLE);
}


/**
 * @brief   等待一个周期的adc转换完成
 */
void AdcResume(void)
{
	TIM_Cmd(TIM2, ENABLE);
}


// adc value
//static volatile uint32_t sAdcDualValue[CONFIG_ADC_TRIG_NUM][CONFIG_ADC_CHAN_NUM];
static uint32_t sAdcDualValue[CONFIG_ADC_TRIG_NUM][CONFIG_ADC_CHAN_NUM];
// adc one channel value
static uint16_t sAdcChanValue[CONFIG_ADC_TRIG_NUM];
static uint16_t sAdcChanRefValue[CONFIG_ADC_TRIG_NUM];



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
int32_t AdcBufGet(uint32_t lIndex, uint16_t **lBuf, uint32_t *lSize)
{
	if (lIndex < CONFIG_ADC_CHAN_NUM)
	{
		uint32_t lI;

		for (lI = 0; lI < CONFIG_ADC_TRIG_NUM; lI++)
		{
			sAdcChanRefValue[lI] = (uint16_t)sAdcDualValue[lI][lIndex];
			sAdcChanValue[lI] = (uint16_t)(sAdcDualValue[lI][lIndex] >> 16);
		}
		*lBuf = sAdcChanValue;
		*lSize = CONFIG_ADC_TRIG_NUM;

		return ESUC;
	}
	else
	{
		return -EPERM;
	}
}


/**
 * @brief   adc reference buffer address. Must use after func AdcBufGet.
 *
 * @param   *lBufRef is the address of reference buffer
 */
void AdcRefBufGet(uint16_t **lBufRef)
{
	*lBufRef = sAdcChanRefValue;
}


/**
 * @brief   adc config
 */
void ADC_Configuration(void)
{
	// rcc config
	RCC_Configuration();
	//DEBUG_Printf("adc-rcc-config done \n");

	// gpio config
	GPIO_Configuration();
	//DEBUG_Printf("adc-gpio-config done \n");

	// nvic config
	NVIC_Configuration();

	// dma config
	DMA_InitTypeDef DMA_InitStructure;

	// dma config
	DMA_DeInit(DMA1_Channel1);
	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)(&(ADC1->DR));
	DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)(sAdcDualValue);
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
	DMA_InitStructure.DMA_BufferSize = CONFIG_ADC_DMA_SIZE;
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Word;
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Word;
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
	DMA_Init(DMA1_Channel1, &DMA_InitStructure);

	/* Enable DMA1 Channel6 Transfer Complete interrupt */
	DMA_ITConfig(DMA1_Channel1, DMA_IT_TC, ENABLE);

	/* Enable DMA1 channel1 */
	DMA_Cmd(DMA1_Channel1, ENABLE);
	//DEBUG_Printf("adc-dma-config done \n");

	// adc config
	ADC_InitTypeDef ADC_InitStructure;

	/* ADC1 configuration ------------------------------------------------------*/
	ADC_InitStructure.ADC_Mode = ADC_Mode_RegSimult;
	ADC_InitStructure.ADC_ScanConvMode = ENABLE;
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;
	// 由tim2 cc2 来触发
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_T2_CC2;
	// 由软件触发
	//ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
	ADC_InitStructure.ADC_NbrOfChannel = CONFIG_ADC_CHAN_NUM;
	ADC_Init(ADC1, &ADC_InitStructure);

	/* ADC1 regular channel14 configuration */
	ADC_RegularChannelConfig(ADC1, ADC_Channel_17, 1, CONFIG_SAMPLE_TIME);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_17, 2, CONFIG_SAMPLE_TIME);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_17, 3, CONFIG_SAMPLE_TIME);

	/* Enable ADC1 DMA */
	ADC_DMACmd(ADC1, ENABLE);

	/* ADC2 configuration ------------------------------------------------------*/
	ADC_InitStructure.ADC_Mode = ADC_Mode_RegSimult;
	ADC_InitStructure.ADC_ScanConvMode = ENABLE;
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
	ADC_InitStructure.ADC_NbrOfChannel = CONFIG_ADC_CHAN_NUM;
	ADC_Init(ADC2, &ADC_InitStructure);

	/* ADC2 regular channel14 configuration */
	ADC_RegularChannelConfig(ADC2, ADC_Channel_12, 1, CONFIG_SAMPLE_TIME);
	ADC_RegularChannelConfig(ADC2, ADC_Channel_11, 2, CONFIG_SAMPLE_TIME);
	ADC_RegularChannelConfig(ADC2, ADC_Channel_10, 3, CONFIG_SAMPLE_TIME);

	/* Enable ADC2 external trigger conversion */
	ADC_ExternalTrigConvCmd(ADC2, ENABLE);
	/* Enable ADC1 external trigger */
	ADC_ExternalTrigConvCmd(ADC1, ENABLE);

	/* Enable ADC1 */
	ADC_Cmd(ADC1, ENABLE);

	/* Enable Vrefint channel17 */
	ADC_TempSensorVrefintCmd(ENABLE);

	/* Enable ADC1 reset calibration register */
	ADC_ResetCalibration(ADC1);
	/* Check the end of ADC1 reset calibration register */
	while(ADC_GetResetCalibrationStatus(ADC1));

	/* Start ADC1 calibration */
	ADC_StartCalibration(ADC1);
	/* Check the end of ADC1 calibration */
	while(ADC_GetCalibrationStatus(ADC1));


	/* Enable ADC2 */
	ADC_Cmd(ADC2, ENABLE);

	/* Enable ADC2 reset calibration register */
	ADC_ResetCalibration(ADC2);
	/* Check the end of ADC2 reset calibration register */
	while(ADC_GetResetCalibrationStatus(ADC2));

	/* Start ADC2 calibration */
	ADC_StartCalibration(ADC2);
	/* Check the end of ADC2 calibration */
	while(ADC_GetCalibrationStatus(ADC2));

	/* Start ADC1 Software Conversion */
//	ADC_SoftwareStartConvCmd(ADC1, ENABLE);

	// 初始化信号量
	rt_sem_init(&sSemAdc, "sem_system_time", 0, RT_IPC_FLAG_FIFO);

	DEBUG_Printf("adc config done \n");
}
