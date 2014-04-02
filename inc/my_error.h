/**
 * @file    my_error.h
 * @brief   
 * @author  ptz
 * @email   ptz19861212@163.com
 * @version 0.0.1
 * @date    2014-01-17 13:02:31 星期五 
 * @history (1).2014-01-17 13:02:31 星期五 create
 */
/* Copyright (C)
 * 
 * My own license
 * All right reserved
 * 
 */

#ifndef __MY_ERROR_H__
#define __MY_ERROR_H__

typedef enum {
				ERROR_NONE = 0,
				ERROR_CALI_ZERO_LOWER,
				ERROR_CALI_ZERO_UPPER,
				// 标气的时候ADC小于零点
				ERROR_CALI_COEFF_POSITIVE_LOWER,
				// 标气的时候ADC大于零点，但是在屏蔽的数值以内
				ERROR_CALI_COEFF_POSITIVE_THRESHOLD,
				// 标气的时候ADC大于零点
				ERROR_CALI_COEFF_NEGATIVE_UPPER,
				// 标气的时候ADC小于零点，但是在屏蔽的数值以内
				ERROR_CALI_COEFF_NEGATIVE_THRESHOLD,
				// 标气的时候ADC在零点周围，但是在屏蔽的数值以内
				ERROR_CALI_COEFF_BOTH_THRESHOLD,
				// 标气的时候如果REF1对应的ADC大于REF3的ADC
				ERROR_CALI_COEFF_BOTH_REF1_UPPER,
				// 标气的时候如果REF2对应的ADC大于REF3的ADC
				ERROR_CALI_COEFF_BOTH_REF2_UPPER,
				// 标气的时候如果REF2对应的ADC小于REF1的ADC
				ERROR_CALI_COEFF_BOTH_REF2_LOWER,
				// 标气的时候如果REF4对应的ADC大于REF5的ADC
				ERROR_CALI_COEFF_BOTH_REF4_UPPER,
				// 标气的时候如果REF4对应的ADC小于REF3的ADC
				ERROR_CALI_COEFF_BOTH_REF4_LOWER,
				// 标气的时候如果REF5对应的ADC小于REF3的ADC
				ERROR_CALI_COEFF_BOTH_REF5_LOWER,

}E_ErrorState;


#endif
