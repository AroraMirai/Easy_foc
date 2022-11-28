/*
 * STW_smc_control.c
 *
 *  Created on: 2022年11月24日
 *      Author: HUAWEI
 */

#include "stw_smc_Control.h"

STW_SMC_t Iq_STW;
STW_SMC_t Id_STW;
STW_SMC_t N_STW;


/*
 * ==============================sign function=================================
 * 					 | 1 , x > 0
 * 			f(x) = sign(x) = { 0 , x = 0
 * 					 | -1, x < 0
 * ============================================================================
 */

double sign_Fn(double input)
{
	if (input > 0)
	{
		return 1;
	}
	if (input < 0)
	{
		return -1;
	}
		return 0;
}

/*
 * ===============================================================================
 * 			超螺旋滑模控制
 * 			 i = Kp |c1|^ 1/2 sgn(c1) + u
 * 			 u'= Ki sgn(c1)
 * ===============================================================================
 */


void STW_SMC_Calu(STW_SMC_t *p)
{
	p->sError = (p->In_ref - p->In_meas) / 100;
	double sign_Value = sign_Fn(p->sError);

	/*积分项，积分分离，偏差较大时去掉积分作用*/
	if (p->sError > -STW_INTEGRAL_ERR_ZONE && p->sError < STW_INTEGRAL_ERR_ZONE)
	{
		p->Ki_sum += p->Ki_smc * p->sError;
		/*积分范围限定，防止积分饱和*/
		if (p->Ki_sum > STW_INTEGRAL_MAX_VAL)
		{
			p->Ki_sum = STW_INTEGRAL_MAX_VAL;
		}
		else if (p->Ki_sum < - STW_INTEGRAL_MAX_VAL)
		{
			p->Ki_sum = -STW_INTEGRAL_MAX_VAL;
		}
		p->sError_last = p->sError;
	}

	p->Kp_sum = sqrt(abs(p->sError)) * sign_Value * p->Kp_smc;
	p->Output = p->Kp_sum + p->Ki_sum;
	LIMIT_MIN_MAX(p->Output, p->OutMin, p->OutMax);
}

void Iq_stw_Loop(double *output ,STW_SMC_t *p)
{
	p->In_meas = IAlphaBeta_to_dq.Qs;
	p->Ki_smc = 1;
	p->Kp_smc = 40;
	p->OutMax = 24;
	p->OutMin = -24;
	STW_SMC_Calu(p);
	*output = p->Output;
}

void Id_stw_Loop(double *output ,STW_SMC_t *p)
{
	p->In_meas = IAlphaBeta_to_dq.Ds;
	p->Ki_smc = 1;
	p->Kp_smc = 5;
	p->OutMax = 24;
	p->OutMin = -24;
	STW_SMC_Calu(p);
	*output = p->Output;
}

void Nr_stw_Loop(double *output ,STW_SMC_t *p)
{
	p->In_meas = IAlphaBeta_to_dq.Ds;
	p->Ki_smc = 0.25;
	p->Kp_smc = 15;
	p->OutMax = 800;
	p->OutMin = -800;
	STW_SMC_Calu(p);
	*output = p->Output;
}

void STW_SMC_Loop(double *output, STW_SMC_t *p, int Select_Flag)
{
	switch(Select_Flag)
	{
	case Iq_Select_Flag:
		Iq_stw_Loop(output,p);
		break;

	case Id_Select_Flag:
		Id_stw_Loop(output,p);
		break;

	case Nr_Select_Flag:
		Nr_stw_Loop(output,p);
		break;
	}
}

