/**
 * @file    gas_cali_zero.c
 * @brief   零点校准
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

#include "gas_cali_zero_in.h"


/**
 * @brief   正向负向气体浓度标零
 *
 * @param   lpCali
 */
void GasCaliZero(S_Gas_Cali_Zero* lpCali)
{
	lpCali->CaliSuc = E_FALSE;

	// 小于零点
	if (lpCali->AdcNow < lpCali->AdcZero)
	{
		// 零点的数值大于零点范围，才能相减，不然下溢
		if (lpCali->AdcZero >= lpCali->ZeroRange)
		{
			if (lpCali->AdcNow >=
						(lpCali->AdcZero - lpCali->ZeroRange))
			{
				lpCali->CaliSuc = E_TRUE;
			}
			else
			{
				lpCali->ErrNum = ERROR_CALI_ZERO_LOWER;
			}
		}
		// 零点范围大于零点的数值，ADC又小于零点，那么必然成功
		else
		{
			lpCali->CaliSuc = E_TRUE;
		}
	}
	else
	{
		// ADC的数值大于零点范围，才能相减，不然下溢
		if (lpCali->AdcNow >= lpCali->ZeroRange)
		{
			if (lpCali->AdcZero >=
						(lpCali->AdcNow - lpCali->ZeroRange))
			{
				lpCali->CaliSuc = E_TRUE;
			}
			else
			{
				lpCali->ErrNum = ERROR_CALI_ZERO_UPPER;
			}
		}
		// 零点范围比ADC的数值还大，而且ADC还是大于零点的，那么肯定成功
		else
		{
				lpCali->CaliSuc = E_TRUE;
		}
	}
}


/**
 * @brief   正向气体浓度标零
 *
 * @param   lpCali
 * @param   lpGas
 */
void GasCaliZeroGetPositive(S_Gas_Cali_Zero* lpCali,
								S_Gas* lpGas)
{
	GasCaliZero(lpCali);

	if (lpCali->CaliSuc == E_TRUE)
	{
		lpGas->pSave->Ref1.Adc = lpCali->AdcNow;
		lpGas->pSave->Ref1.Value = lpGas->pConst->ZeroValue;
		lpGas->pSave->Save_Bits.Ref1 = FLASH_SAVE_TRUE;
	}
}


/**
 * @brief   负向气体浓度标零
 *
 * @param   lpCali
 * @param   lpGas
 */
void GasCaliZeroGetNegative(S_Gas_Cali_Zero* lpCali,
								S_Gas* lpGas)
{
	GasCaliZero(lpCali);

	if (lpCali->CaliSuc == E_TRUE)
	{
		lpGas->pSave->Ref3.Adc = lpCali->AdcNow;
		lpGas->pSave->Ref3.Value = lpGas->pConst->ZeroValue;
		lpGas->pSave->Save_Bits.Ref3 = FLASH_SAVE_TRUE;
	}
}


/**
 * @brief   双向气体浓度标零
 *
 * @param   lpCali
 * @param   lpGas
 */
void GasCaliZeroGetBoth(S_Gas_Cali_Zero* lpCali,
								S_Gas* lpGas)
{
	GasCaliZeroGetNegative(lpCali, lpGas);
//	GasCaliZero(lpCali);
//
//	if (lpCali->CaliSuc == E_TRUE)
//	{
//		lpGas->pSave->Ref3->Adc = lpCali->AdcNow;
//		lpGas->pSave->Ref3->Value = lpGas->pConst->ZeroValue;
//		lpGas->pSave->Save_Bits.Ref3 = FLASH_SAVE_TRUE;
//	}
}

