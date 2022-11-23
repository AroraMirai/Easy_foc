/**
 * @file svpwm.c    
 * @author Mirai
 * @brief 实现SVPWM的输入和计算
 * @version 0.1
 * @date 2022-09-24
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "svpwm.h"

/* Set  defaults*/
SVPWM_T svpwm_struct;

void svpwm_init(SVPWM_T *s) {
	s->Ualpha = Udq_to_AlphaBeta.Alpha;
	s->Ubeta = Udq_to_AlphaBeta.Beta;
	s->Vdc = 24;
	s->Tp = 0.00000416765;
	s->Tcmpa = 0;
	s->Tcmpb = 0;
	s->Tcmpc = 0;
}

void svpwm_calc_t(SVPWM_T *p) {
	double temp;
	double X, Y, Z, t1, t2;
	int A, B, C, N, Sector;
	double Ta, Tb, Tc;

	double h;

	h = SQRT3 * p->Tp / p->Vdc;

	X = h * p->Ubeta;
	Y = h * (SQRT3byTWO * p->Ualpha + 0.5 * p->Ubeta);
	Z = h * (-SQRT3byTWO * p->Ualpha + 0.5 * p->Ubeta);

	if (p->Ubeta > 0)
		A = 1;
	else
		A = 0;

	if ((SQRT3 * p->Ualpha - p->Ubeta) > 0)
		B = 1;
	else
		B = 0;

	if ((-SQRT3 * p->Ualpha - p->Ubeta) > 0)
		C = 1;
	else
		C = 0;

	N = A + 2 * B + 4 * C;

	switch (N) {
	case 1:
		Sector = 2;
		break;

	case 2:
		Sector = 6;
		break;

	case 3:
		Sector = 1;
		break;

	case 4:
		Sector = 4;
		break;

	case 5:
		Sector = 3;
		break;

	case 6:
		Sector = 5;
		break;

	default:
		;
	}

	switch (Sector) {
	case 1:
		t1 = -Z;
		t2 = X;
		break;
	case 2:
		t1 = Z;
		t2 = Y;
		break;
	case 3:
		t1 = X;
		t2 = -Y;
		break;
	case 4:
		t1 = -X;
		t2 = Z;
		break;
	case 5:
		t1 = -Y;
		t2 = -Z;
		break;
	case 6:
		t1 = Y;
		t2 = -X;
		break;
	default:
		;
	}

	if ((t1 + t2) > p->Tp) {
		temp = t1 + t2;
		t1 = t1 * p->Tp / temp;
		t2 = t2 * p->Tp / temp;
	}

	Ta = (p->Tp - t1 - t2) / 4; //作用时间分配
	Tb = Ta + t1 / 2;
	Tc = Tb + t2 / 2;

	switch (Sector) {
	case 1:
		p->Tcmpa = Ta;
		p->Tcmpb = Tb;
		p->Tcmpc = Tc;
		break;
	case 2:
		p->Tcmpa = Tb;
		p->Tcmpb = Ta;
		p->Tcmpc = Tc;
		break;
	case 3:
		p->Tcmpa = Tc;
		p->Tcmpb = Ta;
		p->Tcmpc = Tb;
		break;
	case 4:
		p->Tcmpa = Tc;
		p->Tcmpb = Tb;
		p->Tcmpc = Ta;
		break;
	case 5:
		p->Tcmpa = Tb;
		p->Tcmpb = Tc;
		p->Tcmpc = Ta;
		break;
	case 6:
		p->Tcmpa = Ta;
		p->Tcmpb = Tc;
		p->Tcmpc = Tb;
		break;
	default:
		;
	}
	p->T_circleA = (uint8_t)(p->Tcmpa / p->Tp * 100);
	p->T_circleB = (uint8_t)(p->Tcmpb / p->Tp * 100);
	p->T_circleC = (uint8_t)(p->Tcmpc / p->Tp * 100);
}

void updata_PWM(SVPWM_T *p) {
	FTM_UpdateChnlEdgeLevelSelect(FTM3_PERIPHERAL, kFTM_Chnl_0 | kFTM_Chnl_2 | kFTM_Chnl_4, 0u);

	//Update duty cycle
	FTM_UpdatePwmDutycycle(FTM3_PERIPHERAL, kFTM_Chnl_0, kFTM_CenterAlignedPwm, p->T_circleA);
	FTM_UpdatePwmDutycycle(FTM3_PERIPHERAL, kFTM_Chnl_1, kFTM_CenterAlignedPwm, 0);
	FTM_UpdatePwmDutycycle(FTM3_PERIPHERAL, kFTM_Chnl_2, kFTM_CenterAlignedPwm, p->T_circleB);
	FTM_UpdatePwmDutycycle(FTM3_PERIPHERAL, kFTM_Chnl_3, kFTM_CenterAlignedPwm, 0);
	FTM_UpdatePwmDutycycle(FTM3_PERIPHERAL, kFTM_Chnl_4, kFTM_CenterAlignedPwm, p->T_circleC);
	FTM_UpdatePwmDutycycle(FTM3_PERIPHERAL, kFTM_Chnl_5, kFTM_CenterAlignedPwm, 0);

//Software trigger
	FTM_SetSoftwareTrigger(FTM3_PERIPHERAL, true);

	FTM_UpdateChnlEdgeLevelSelect(FTM3_PERIPHERAL, kFTM_Chnl_0 | kFTM_Chnl_2 | kFTM_Chnl_4, kFTM_HighTrue);

}

