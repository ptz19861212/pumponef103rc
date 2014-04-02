/**
 * @file    iwdg.c
 * @brief   
 * @author  ptz
 * @email   ptz19861212@163.com
 * @version 0.0.1
 * @date    2014-02-17 16:01:14 星期一 
 * @history (1).2014-02-17 16:01:14 星期一 create
 */
/* Copyright (C)
 * 
 * My own license
 * All right reserved
 * 
 */

#include "iwdg_in.h"

/**
 * @brief   iwdg config
 */
void IWDG_Configuration(void)
{
	/* Enable write access to IWDG_PR and IWDG_RLR registers */
	IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);

	/* IWDG counter clock: LSI/32 */
	IWDG_SetPrescaler(IWDG_Prescaler_32);

	/* Set counter reload value to obtain 250ms IWDG TimeOut.
	 Counter Reload Value = 250ms/IWDG counter clock period
						  = 250ms / (LSI/32)
						  = 0.25s / (LsiFreq/32)
						  = LsiFreq/(32 * 4)
						  = LsiFreq/128
	*/
//	IWDG_SetReload(LSI_FREQ / 128);

	// iwdg period is 1000mS
	IWDG_SetReload(LSI_FREQ / 32);

	/* Reload IWDG counter */
	IWDG_ReloadCounter();

	/* Enable IWDG (the LSI oscillator will be enabled by hardware) */
	IWDG_Enable();

}
