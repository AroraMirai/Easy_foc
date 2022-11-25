/*
 * Weak_control.c
 *
 *  Created on: 2022年11月23日
 *      Author: HUAWEI
 */

#include "Weak_control.h"

weaken_Loop_t 	weaken_Loop_struct;
MTPA_Loop_t 	MTPA_Loop_struct;



void MTPA_loop(MTPA_Loop_t *p , double Iq_ref)
{
	if (Ld == Lq)									//判断是否为隐极PMSM
	{
		p->id_weaken = 0;
		p->iq_weaken = 0;
	}
	else
	{
		double L_Delta = Lq - Ld;
		p->iq_weaken = Iq_ref;
		p->id_weaken = Flux_f /(2 * L_Delta) * Iq_ref * Iq_ref;
	}
}


/*
 * @brief	超前角弱磁方法
 * @param	p 弱磁控制结构体 其中包含了
 * @param
 */
void weak_loop_preAngel(weaken_Loop_t *p,double Iq_ref)
{
	double weak_preAngel;										//电流超前角

	p->Udc_max = adcGet_struct.Udc * 0.8 / SQRT3;
	p->Us = sqrt(Udq_to_AlphaBeta.Ds * Udq_to_AlphaBeta.Ds + Udq_to_AlphaBeta.Qs * Udq_to_AlphaBeta.Qs);

	weak_PI.InMeas = p->Us;

	weak_PI.Inref = p->Udc_max;

	PID_Calu(&weak_preAngel, &weak_PI, weaken_Select_Flag);

	p->iq_weaken = Iq_ref * cos(weak_preAngel);
	p->id_weaken = Iq_ref * sin(weak_preAngel);
}
