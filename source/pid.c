/*
 * pid.c
 *
 *  Created on: 2022年10月18日
 *      Author: HUAWEI
 */

#include "pid.h"

PI_CONTROL_t theta_PI;
PI_CONTROL_t N_PI;
PI_CONTROL_t Id_PI;
PI_CONTROL_t Iq_PI;
PI_CONTROL_t Theta_PI;

void PI_Calc(PI_CONTROL_t *p)
{
	p->cError = p->Inref - p->InMeas;
	p->U = p->cError * p->Ki;

	p->dSum = p->dSum + p->U;

	if (p->dSum > p->OutMax)
		p->dSum = p->OutMax;
	if (p->dSum < p->OutMin)
		p->dSum = p->OutMin;

	p->U = p->cError * p->Kp;

	p->U = p->dSum + p->U;

	if (p->U > p->OutMax)
		p->Out = p->OutMax;
	if (p->U < p->OutMin)
		p->Out = p->OutMin;
	else
		p->Out = p->U;
}

void PID_real(PI_CONTROL_t *p) {
	int index;
	p->cError = p->Inref - p->InMeas;
	if (p->InMeas > p->OutMax)
	{
		if (abs(p->cError) > 200)
			index = 0;
		else
		{
			index = 1;
			if (p->cError < 0)
				p->dSum += p->cError;
		}
	}
	else if (p->InMeas < p->OutMin)
	{
		if (abs(p->cError) > 200)
			index = 0;
		else
		{
			index = 1;
			if (p->cError > 0)
				p->dSum += p->cError;
		}
	}
	else
	{
		if (abs(p->cError) > 200)
			index = 0;
		else
		{
			index = 1;
			p->dSum += p->cError;
		}
	}
	p->Out = p->Kp * p->cError + index * p->Ki * p->dSum
			+ p->Kd * (p->cError - p->cError_last);
	p->cError_last = p->cError;
}

double pid_realize(PI_CONTROL_t *pid)
{
	/*计算目标值与实际值的误差*/
	pid->cError = (pid->Inref - pid->InMeas) / 50;

	/* 设定闭环死区 */
//	if ((pid->cError >= -DEAD_ZONE) && (pid->cError <= DEAD_ZONE))
//	{
//		pid->cError = 0;
//		pid->dSum = 0;
//		pid->cError_last = 0;
//	}

	/*积分项，积分分离，偏差较大时去掉积分作用*/
	if (pid->cError > -INTEGRAL_ERR_ZONE && pid->cError < INTEGRAL_ERR_ZONE)
	{
		pid->dSum += pid->cError;
		/*积分范围限定，防止积分饱和*/
		if (pid->dSum > INTEGRAL_MAX_VAL)
		{
			pid->dSum = INTEGRAL_MAX_VAL;
		}
		else if (pid->dSum < - INTEGRAL_MAX_VAL)
		{
			pid->dSum = -INTEGRAL_MAX_VAL;
		}
	}

	/*PID算法实现*/
	pid->Out = pid->Kp * pid->cError + pid->Ki * pid->dSum
			 + pid->Kd * (pid->cError - pid->cError_last);

	/*误差传递*/
	pid->cError_last = pid->cError;

	/*返回当前实际值*/
	if (pid->Out > pid->OutMax)
			pid->Out = pid->OutMax;
	if (pid->Out < pid->OutMin)
			pid->Out = pid->OutMin;
	return pid->Out;
}


void N_Loop (double *output , PI_CONTROL_t *p)
{

	p->Kp = 0.01;
	p->Ki = 0.05;
	p->Kd = 0.02;
	p->OutMax = 800;
	p->OutMin = -800;
	*output = pid_realize(p);
}

void Iq_Loop (double *output , PI_CONTROL_t *p)
{

	p->Kp = 0.01;
	p->Ki = 0.05;
	p->Kd = 0;
	p->OutMax = 24;
	p->OutMin = -24;
	*output = pid_realize(p);
}

void Id_Loop (double *output , PI_CONTROL_t *p)
{

	p->Kp = 0.01;
	p->Ki = 0.05;
	p->Kd = 0;
	p->OutMax = 24;
	p->OutMin = -24;
	*output = pid_realize(p);
}

void T_Loop (double *output , PI_CONTROL_t *p)
{

	p->Kp = 0.01;
	p->Ki = 0.3;
	p->Kd = 0;
	p->OutMax = 24;
	p->OutMin = -24;
	*output = pid_realize(p);
}

void pos_Loop (double *output , PI_CONTROL_t *p)
{

	p->Kp = 0.01;
	p->Ki = 0.3;
	p->Kd = 0;
	p->OutMax = 24;
	p->OutMin = -24;
	*output = pid_realize(p);
}

void PID_Calu(double *output, PI_CONTROL_t *p, int SelectFlag) {
	switch(SelectFlag){

	case Nr_Select_Flag:
		N_Loop(output, p);
		break;

	case Iq_Select_Flag:
		Iq_Loop(output, p);
		break;

	case Id_Select_Flag:
		Id_Loop(output, p);
		break;

	case T_Select_Flag:
		T_Loop(output, p);
		break;

	case pos_Select_Flag:
		pos_Loop(output, p);
		break;
	}
}
