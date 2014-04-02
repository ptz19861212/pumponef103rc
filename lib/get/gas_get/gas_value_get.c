/**
 * @file    gas_value_get.c
 * @brief   获得气体浓度
 * @author  ptz
 * @email   ptz19861212@163.com
 * @version 0.0.1
 * @date    2013-12-22 09:54:06 星期日 
 * @history (1).2013-12-22 09:54:06 星期日 create
 */
/* Copyright (C)
 * 
 * My own license
 * All right reserved
 * 
 */

#include "gas_value_get_in.h"


/**
 * @brief   正向气体浓度求数值
 *
 * @param   lpPoint 当前的点
 * @param   lpRef1 参考点1
 * @param   lpRef3 参考点3
 * @param   lThreshold 参考点1向上的屏蔽数值
 */
void GasValueGetPositive(S_Gas* lpGas)
//void GasValueGetPositive(S_Gas_Point* lpPoint,
//							S_Gas_Point* lpRef1,
//							S_Gas_Point* lpRef3,
//							uint8_t lThreshold)
{
	uint16_t lTmp;
	uint16_t lAdc;

	// 防止在计算过程中被ADC采样的进程改变了数值，导致计算出现不可预测的后果
//	lAdc = lpPoint->Adc;
	lAdc = lpGas->pTemp->Point.Adc;

	if (lAdc > lpGas->pSave->Ref1.Adc)
	{
		lTmp = lAdc - lpGas->pSave->Ref1.Adc;
	}
	else
	{
		lTmp = 0;
	}

	if (lTmp > lpGas->pConst->ZeroThrs)
	{
		#if (CONFIG_GAS_VALUE_BITS == 16)
			uint32_t lProduct = 0;

			lProduct = lpGas->pSave->Ref3.Value -
							lpGas->pSave->Ref1.Value;
			lProduct *= lTmp;
			lpGas->pTemp->Point.Value =
					(lProduct / (lpGas->pSave->Ref3.Adc -
							lpGas->pSave->Ref1.Adc)) +
							lpGas->pSave->Ref1.Value;
		#elif (my_gas_t == uint32_t)
		#endif
	}
	else
	{
		lpGas->pTemp->Point.Value = lpGas->pSave->Ref1.Value;
	}

	if (lpGas->pTemp->Point.Value > lpGas->pConst->Range)
	{
		lpGas->pTemp->Point.Value = lpGas->pConst->Range;
	}
}


/**
 * @brief   负向气体浓度求数值
 *
 * @param   lpPoint 当前的点
 * @param   lpRef1 参考点1
 * @param   lpRef3 参考点3
 * @param   lThreshold 参考点1向上的屏蔽数值
 */
void GasValueGetNegative(S_Gas* lpGas)
//void GasValueGetNegative(S_Gas_Point* lpPoint,
//							S_Gas_Point* lpRef1,
//							S_Gas_Point* lpRef3,
//							uint8_t lThreshold)
{
	uint16_t lTmp;
	uint16_t lAdc;

	// 防止在计算过程中被ADC采样的进程改变了数值，导致计算出现不可预测的后果
//	lAdc = lpPoint->Adc;
	lAdc = lpGas->pTemp->Point.Adc;

	if (lAdc < lpGas->pSave->Ref3.Adc)
	{
		lTmp = lpGas->pSave->Ref3.Adc - lAdc;
	}
	else
	{
		lTmp = 0;
	}

	if (lTmp > lpGas->pConst->ZeroThrs)
	{
		#if (CONFIG_GAS_VALUE_BITS == 16)
			uint32_t lProduct = 0;

			lProduct = lpGas->pSave->Ref1.Value -
							lpGas->pSave->Ref3.Value;
			lProduct *= lTmp;
			lpGas->pTemp->Point.Value =
					(lProduct / (lpGas->pSave->Ref3.Adc -
							lpGas->pSave->Ref1.Adc)) +
							lpGas->pSave->Ref3.Value;
		#elif (my_gas_t == uint32_t)
		#endif
	}
	else
	{
		lpGas->pTemp->Point.Value = lpGas->pSave->Ref3.Value;
	}

	if (lpGas->pTemp->Point.Value > lpGas->pConst->Range)
	{
		lpGas->pTemp->Point.Value = lpGas->pConst->Range;
	}
}


/**
 * @brief   双向气体浓度求数值
 *
 * @param   lpPoint 当前的点
 * @param   lpRef1 参考点1
 * @param   lpRef3 参考点3
 * @param   lThreshold 参考点1向上的屏蔽数值
 */
void GasValueGetBoth(S_Gas* lpGas)
//void GasValueGetBoth(S_Gas_Point* lpPoint,
//							S_Gas_Point* lpRef1,
//							S_Gas_Point* lpRef2,
//							S_Gas_Point* lpRef3,
//							S_Gas_Point* lpRef4,
//							uint8_t lThreshold)
{
	uint16_t lTmp;
	uint16_t lAdc;

	// 防止在计算过程中被ADC采样的进程改变了数值，导致计算出现不可预测的后果
//	lAdc = lpPoint->Adc;
	lAdc = lpGas->pTemp->Point.Adc;;

	if (lAdc > lpGas->pSave->Ref1.Adc)
	{
		lTmp = lAdc - lpGas->pSave->Ref1.Adc;
	}
	else
	{
		lTmp = 0;
	}

	if (lTmp > lpGas->pConst->ZeroThrs)
	{
		#if (CONFIG_GAS_VALUE_BITS == 16)
			uint32_t lProduct = 0;

//			lProduct = lpRef3->Value - lpRef1->Value;
//			lProduct *= lTmp;
//			lpPoint->Value = (lProduct / (lpRef3->Adc - lpRef1->Adc)) +
//								lpRef1->Value;

			// 点在参考1和参考3之间
			if (lAdc < lpGas->pSave->Ref3.Adc)
			{
				// 参考点2正常， 分为1-2和2-3 两端区间
				if ((lpGas->pSave->Ref2.Adc >
						lpGas->pSave->Ref1.Adc) &&
						(lpGas->pSave->Ref2.Adc <
							lpGas->pSave->Ref3.Adc))
				{
					// 点在参考点1和参考点2之间，按照1-2斜率
					if (lAdc < lpGas->pSave->Ref2.Adc)
					{
						lProduct = lpGas->pSave->Ref2.Value -
										lpGas->pSave->Ref1.Value;
						lProduct *= lAdc - lpGas->pSave->Ref1.Adc;
						lpGas->pTemp->Point.Value =
							(lProduct / (lpGas->pSave->Ref2.Adc -
									lpGas->pSave->Ref1.Adc))
										+ lpGas->pSave->Ref1.Value;

					}
					// 点在参考点2和参考点3之间，按照2-3斜率
					else if (lAdc > lpGas->pSave->Ref2.Adc)
					{
						lProduct = lpGas->pSave->Ref3.Value -
										lpGas->pSave->Ref2.Value;
						lProduct *= lAdc - lpGas->pSave->Ref2.Adc;
						lpGas->pTemp->Point.Value =
							(lProduct / (lpGas->pSave->Ref3.Adc -
									lpGas->pSave->Ref2.Adc))
										+ lpGas->pSave->Ref2.Value;
					}
					// 点在参考点2的位置
					else
					{
						lpGas->pTemp->Point.Value =
								lpGas->pSave->Ref2.Value;
					}
				} // end of if ((lpRef2->Adc > lpRef1->Adc) &&
				// 					(lpRef2->Adc < lpRef3->Adc))
				// 参考点2不正常，直接1-3区间，按照1-3斜率
				else
				{
					lProduct = lpGas->pSave->Ref3.Value -
									lpGas->pSave->Ref1.Value;
					lProduct *= lAdc - lpGas->pSave->Ref1.Adc;
					lpGas->pTemp->Point.Value =
						(lProduct / (lpGas->pSave->Ref3.Adc -
								lpGas->pSave->Ref1.Adc))
									+ lpGas->pSave->Ref1.Value;
				}
			}
			// 点在参考点3以上
			else if (lAdc > lpGas->pSave->Ref3.Adc)
			{
				// 参考点4正常，就是3-4和4以上两个区间，
				if (lpGas->pSave->Ref4.Adc >
						lpGas->pSave->Ref3.Adc)
				{
					// 点在3-4之间，按照3-4斜率
					if (lAdc < lpGas->pSave->Ref4.Adc)
					{
						lProduct = lpGas->pSave->Ref4.Value -
										lpGas->pSave->Ref3.Value;
						lProduct *= lAdc - lpGas->pSave->Ref3.Adc;
						lpGas->pTemp->Point.Value =
							(lProduct / (lpGas->pSave->Ref4.Adc -
									lpGas->pSave->Ref3.Adc))
										+ lpGas->pSave->Ref3.Value;
					}
					// 点在4以上的区间，按照1-4的斜率
					else if (lAdc > lpGas->pSave->Ref4.Adc)
					{
						lProduct = lpGas->pSave->Ref4.Value -
										lpGas->pSave->Ref1.Value;
						lProduct *= lAdc - lpGas->pSave->Ref1.Adc;
						lpGas->pTemp->Point.Value =
							(lProduct / (lpGas->pSave->Ref4.Adc -
									lpGas->pSave->Ref1.Adc))
										+ lpGas->pSave->Ref1.Value;
					}
					// 点在点4的位置
					else
					{
						lpGas->pTemp->Point.Value =
								lpGas->pSave->Ref4.Value;
					}

				}
				// 参考点4不正常，直接3以上区间，按照1-3的斜率
				else
				{
					lProduct = lpGas->pSave->Ref3.Value -
									lpGas->pSave->Ref1.Value;
					lProduct *= lAdc - lpGas->pSave->Ref1.Adc;
					lpGas->pTemp->Point.Value =
							(lProduct / (lpGas->pSave->Ref3.Adc -
									lpGas->pSave->Ref1.Adc))
										+ lpGas->pSave->Ref1.Value;

				}
			} // end of else if (lpPoint->Adc > lpRef3->Adc)
			// 点在参考点3的位置
			else
			{
				lpGas->pTemp->Point.Value =
						lpGas->pSave->Ref3.Value;
			}
		#elif (my_gas_t == uint32_t)
		#endif
	}
	else
	{
		lpGas->pTemp->Point.Value = lpGas->pSave->Ref1.Value;
	}

	if (lpGas->pTemp->Point.Value > lpGas->pConst->Range)
	{
		lpGas->pTemp->Point.Value = lpGas->pConst->Range;
	}
}


/**
 * @brief   气体获得标气的上限和下限
 *
 * @param   lpGas 气体结构体
 * @param   lpInput 输入的数值上下限
 */
void GasValueLimitGet(S_Gas* lpGas,
								S_Value_Input_Gas* lpInput)
{
	lpInput->Up = 0xFFFF;
	lpInput->Low = 0;
	lpInput->Init = lpGas->pTemp->Point.Value;
//	lpInput->Init = lpGas->pTemp->AlarmSave.Stel;
}
