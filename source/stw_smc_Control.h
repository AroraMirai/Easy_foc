/*
 * STW_smc_control.h
 *
 *  Created on: 2022年11月24日
 *      Author: HUAWEI
 */

#ifndef STW_SMC_CONTROL_H_
#define STW_SMC_CONTROL_H_

#include "default.h"
#define DEAD_ZONE 0 			/*死区*/
#define STW_INTEGRAL_ERR_ZONE 20	/*积分分离时对应的误差范围*/
#define STW_INTEGRAL_MAX_VAL 2000   	/*积分范围限定，防止积分饱和*/


typedef struct _STW_SMC
{
	double Ki_smc;
	double Kp_smc;

	double In_meas;
	double In_ref;
	double Output;
	double OutMax;				//PI Output maximum limit
	double OutMin;				//PI output minimum limit

	double sError;
	double sError_last;
	double Ki_sum;
	double Kp_sum;

}STW_SMC_t;

extern STW_SMC_t Iq_STW;
extern STW_SMC_t Id_STW;
extern STW_SMC_t N_STW;

double sign_Fn(double input);

void STW_SMC_Calu(STW_SMC_t *p);

void Iq_stw_Loop(double *output ,STW_SMC_t *p);
void Id_stw_Loop(double *output ,STW_SMC_t *p);
void Nr_stw_Loop(double *output ,STW_SMC_t *p);


void STW_SMC_Loop(double *output, STW_SMC_t *p, int Select_Flag);

#endif /* STW_SMC_CONTROL_H_ */
