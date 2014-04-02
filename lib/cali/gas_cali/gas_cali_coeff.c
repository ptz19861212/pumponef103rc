/**
 * @file    gas_cali_coeff.c
 * @brief   系数校准
 * @author  ptz
 * @email   ptz19861212@163.com
 * @version 0.0.1
 * @date    2014-01-14 16:17:21 星期二 
 * @history (1).2014-01-14 16:17:21 星期二 create
 */
/* Copyright (C)
 * 
 * My own license
 * All right reserved
 * 
 */

#include "gas_cali_coeff_in.h"


/**
 * @brief   正向负向气体浓度标气，出错可能只有几种
 * 				ADC在零点上面几个屏蔽点以内
 * 				ADC小于零点
 *
 * @param   lpCali
 */
void GasCaliCoeffPositive(S_Gas_Cali_Coeff* lpCali)
{
	lpCali->CaliSuc = E_FALSE;

	// 小于零点
	if (lpCali->AdcNow < lpCali->AdcZero)
	{
		lpCali->ErrNum = ERROR_CALI_COEFF_POSITIVE_LOWER;
	}
	else
	{
		//大于零点但是在屏蔽范围内
		if (lpCali->AdcNow <
					(lpCali->AdcZero + lpCali->Threshold))
		{
			lpCali->ErrNum = ERROR_CALI_COEFF_POSITIVE_THRESHOLD;
		}
		else
		{
				lpCali->CaliSuc = E_TRUE;
		}
	}
}


/**
 * @brief   负向气体浓度标气，出错可能只有几种
 * 				ADC在零点下面几个屏蔽点以内
 * 				ADC大于零点
 *
 * @param   lpCali
 */
void GasCaliCoeffNegative(S_Gas_Cali_Coeff* lpCali)
{
	lpCali->CaliSuc = E_FALSE;

	// 大于零点
	if (lpCali->AdcNow > lpCali->AdcZero)
	{
		lpCali->ErrNum = ERROR_CALI_COEFF_NEGATIVE_UPPER;
	}
	else
	{
		// 小于零点但是在屏蔽范围内
		if ((lpCali->AdcNow + lpCali->Threshold) >
											lpCali->AdcZero)
		{
			lpCali->ErrNum = ERROR_CALI_COEFF_NEGATIVE_THRESHOLD;
		}
		else
		{
				lpCali->CaliSuc = E_TRUE;
		}
	}
}


/**
 * @brief   双向气体浓度标气，出错可能只有几种
 * 				ADC在零点几个屏蔽点以内
 * 				标REF1的ADC大于REF3的ADC
 *
 * @param   lpCali
 */
void GasCaliCoeffBothZero(S_Gas_Cali_Coeff* lpCali)
{
	lpCali->CaliSuc = E_FALSE;

	// 大于零点
	if (lpCali->AdcNow > lpCali->AdcZero)
	{
		//大于零点但是在屏蔽范围内
		if (lpCali->AdcNow <
					(lpCali->AdcZero + lpCali->Threshold))
		{
			lpCali->ErrNum = ERROR_CALI_COEFF_BOTH_THRESHOLD;
		}
		else
		{
			lpCali->CaliSuc = E_TRUE;
		}
	}
	else
	{
		// 小于零点但是在屏蔽范围内
		if ((lpCali->AdcNow + lpCali->Threshold) >
											lpCali->AdcZero)
		{
			lpCali->ErrNum = ERROR_CALI_COEFF_BOTH_THRESHOLD;
		}
		else
		{
			lpCali->CaliSuc = E_TRUE;
		}
	}
}


/**
 * @brief   双向气体浓度标气，出错可能
 * 				标REF1的ADC大于REF3的ADC
 *
 * @param   lpCali
 */
void GasCaliCoeffBothRef1(S_Gas_Cali_Coeff* lpCali,
								S_Gas* lpGas)
{
	lpCali->CaliSuc = E_FALSE;

	// 大于ref3点
	if (lpCali->AdcNow > lpGas->pSave->Ref3.Adc)
	{
		lpCali->ErrNum = ERROR_CALI_COEFF_BOTH_REF1_UPPER;
	}
	else
	{
		lpCali->CaliSuc = E_TRUE;
	}
}


/**
 * @brief   双向气体浓度标气，出错可能
 * 				标REF2的ADC大于REF3的ADC, 标REF2的ADC小于REF1的ADC
 *
 * @param   lpCali
 */
void GasCaliCoeffBothRef2(S_Gas_Cali_Coeff* lpCali,
								S_Gas* lpGas)
{
	lpCali->CaliSuc = E_FALSE;

	// 大于ref3
	if (lpCali->AdcNow > lpGas->pSave->Ref3.Adc)
	{
		lpCali->ErrNum = ERROR_CALI_COEFF_BOTH_REF2_UPPER;
	}
	else if (lpCali->AdcNow < lpGas->pSave->Ref1.Adc)
	{
		lpCali->ErrNum = ERROR_CALI_COEFF_BOTH_REF2_LOWER;
	}
	else
	{
		lpCali->CaliSuc = E_TRUE;
	}
}


/**
 * @brief   双向气体浓度标气，出错可能
 * 				标REF4的ADC大于REF5的ADC, 标REF4的ADC小于REF3的ADC
 *
 * @param   lpCali
 */
void GasCaliCoeffBothRef4(S_Gas_Cali_Coeff* lpCali,
								S_Gas* lpGas)
{
	lpCali->CaliSuc = E_FALSE;

	// 大于ref3
	if (lpCali->AdcNow > lpGas->pSave->Ref5.Adc)
	{
		lpCali->ErrNum = ERROR_CALI_COEFF_BOTH_REF4_UPPER;
	}
	else if (lpCali->AdcNow < lpGas->pSave->Ref3.Adc)
	{
		lpCali->ErrNum = ERROR_CALI_COEFF_BOTH_REF4_LOWER;
	}
	else
	{
		lpCali->CaliSuc = E_TRUE;
	}
}


/**
 * @brief   双向气体浓度标气，出错可能
 * 				标REF5的ADC小于REF3的ADC
 *
 * @param   lpCali
 */
void GasCaliCoeffBothRef5(S_Gas_Cali_Coeff* lpCali,
								S_Gas* lpGas)
{
	lpCali->CaliSuc = E_FALSE;

	if (lpCali->AdcNow < lpGas->pSave->Ref3.Adc)
	{
		lpCali->ErrNum = ERROR_CALI_COEFF_BOTH_REF5_LOWER;
	}
	else
	{
		lpCali->CaliSuc = E_TRUE;
	}
}


/**
 * @brief   气体浓度标气
 *
 * @param   lpCali
 * @param   lpPoint 正向气体使用REF1，负向和双向气体使用REF3
 */
void GasCaliCoeffGetPositive(S_Gas_Cali_Coeff* lpCali,
//										S_Gas_Point* lpPoint)
									S_Gas* lpGas)
{
	lpCali->AdcZero = lpGas->pSave->Ref1.Adc;
	GasCaliCoeffPositive(lpCali);

	if (lpCali->CaliSuc == E_TRUE)
	{
		lpGas->pSave->Ref3.Value = lpCali->Value;
		lpGas->pSave->Ref3.Adc = lpCali->AdcNow;
		lpGas->pSave->Save_Bits.Ref3 = FLASH_SAVE_TRUE;
	}
}

/**
 * @brief   气体浓度标气
 *
 * @param   lpCali
 * @param   lpPoint 正向气体使用REF1，负向和双向气体使用REF3
 */
void GasCaliCoeffGetNegative(S_Gas_Cali_Coeff* lpCali,
//										S_Gas_Point* lpPoint)
									S_Gas* lpGas)
{
	lpCali->AdcZero = lpGas->pSave->Ref3.Adc;
	GasCaliCoeffNegative(lpCali);

	if (lpCali->CaliSuc == E_TRUE)
	{
		lpGas->pSave->Ref1.Value = lpCali->Value;
		lpGas->pSave->Ref1.Adc = lpCali->AdcNow;
		lpGas->pSave->Save_Bits.Ref1 = FLASH_SAVE_TRUE;
	}
}


/**
 * @brief   气体浓度标气
 *
 * @param   lpCali
 * @param   lpPoint 正向气体使用REF1，负向和双向气体使用REF3
 */
void GasCaliCoeffGetBoth(S_Gas_Cali_Coeff* lpCali,
//										S_Gas_Point* lpPoint)
								S_Gas* lpGas)
{
	lpCali->AdcZero = lpGas->pSave->Ref3.Adc;
	// 查看零点是否可以
	GasCaliCoeffBothZero(lpCali);

	if (lpCali->CaliSuc == E_TRUE)
	{
//		if (lpPoint->Value == 0)
		if (lpCali->Value == lpGas->pSave->Ref1.Value)
		{
			GasCaliCoeffBothRef1(lpCali, lpGas);

			if (lpCali->CaliSuc == E_TRUE)
			{
				lpGas->pSave->Ref1.Value = lpCali->Value;
				lpGas->pSave->Ref1.Adc = lpCali->AdcNow;
				lpGas->pSave->Save_Bits.Ref1 = FLASH_SAVE_TRUE;
			}
		}
		else if (lpCali->Value < lpGas->pSave->Ref3.Value)
		{
			GasCaliCoeffBothRef2(lpCali, lpGas);

			if (lpCali->CaliSuc == E_TRUE)
			{
				lpGas->pSave->Ref2.Value = lpCali->Value;
				lpGas->pSave->Ref2.Adc = lpCali->AdcNow;
				lpGas->pSave->Save_Bits.Ref2 = FLASH_SAVE_TRUE;
			}
		}
		else if (lpCali->Value < lpGas->pSave->Ref5.Value)
		{
			GasCaliCoeffBothRef4(lpCali, lpGas);

			if (lpCali->CaliSuc == E_TRUE)
			{
				lpGas->pSave->Ref4.Value = lpCali->Value;
				lpGas->pSave->Ref4.Adc = lpCali->AdcNow;
				lpGas->pSave->Save_Bits.Ref4 = FLASH_SAVE_TRUE;
			}
		}
		else if (lpCali->Value == lpGas->pSave->Ref5.Value)
		{
			GasCaliCoeffBothRef5(lpCali, lpGas);

			if (lpCali->CaliSuc == E_TRUE)
			{
				lpGas->pSave->Ref5.Value = lpCali->Value;
				lpGas->pSave->Ref5.Adc = lpCali->AdcNow;
				lpGas->pSave->Save_Bits.Ref5 = FLASH_SAVE_TRUE;
			}
		}

	}
}

