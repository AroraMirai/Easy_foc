/*
 * Current_ipark.c
 *
 *  Created on: 2022年10月27日
 *      Author: HUAWEI
 */

#include <PARK_CLARKE.h>


PARK_CLARKE_t Udq_to_AlphaBeta;
PARK_CLARKE_t Iabc_to_AlphaBeta;
PARK_CLARKE_t IAlphaBeta_to_dq;

void PARK_CLARKE_Init(PARK_CLARKE_t *p)
{
	p->Alpha = 0;
	p->Beta = 0;

	p->Ds = 0;
	p->Qs = 0;

	p->As = 0;
	p->Bs = 0;
	p->Cs = 0;

	p->Theta_e = 0;
	p->the = 0;
	p->Udc = 0;
}

void ipark_Transf(PARK_CLARKE_t *p)
{
	p->the = p->Theta_e * PI / 180;
	//	double the = 0;
	p->Alpha = p->Ds * cos(p->the) - p->Qs * sin(p->the);
	p->Beta = p->Qs * cos(p->the) + p->Ds * sin(p->the);
}

void park_Transf(PARK_CLARKE_t*p )
{
	p->the = p->Theta_e * PI / 180;

	p->Ds = p->Alpha * cos(p->the) + p->Beta + sin(p->the);
	p->Qs = p->Beta * cos(p->the) - p->Alpha * sin(p->the);
}

void clarke_Transf(PARK_CLARKE_t *p)
{
	p->Alpha = (p->As - 0.5 * (p->Bs + p->Cs)) * 2 / 3;
	p->Beta = (p->Bs  - p->Cs ) / sqrt(3);
}
