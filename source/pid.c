/*
 * pid.c
 *
 *  Created on: 2022年10月18日
 *      Author: HUAWEI
 */

#include "pid.h"

PI_CONTROL_t N_PI=PI_CONTROL_DEFAULTS;
PI_CONTROL_t Id_PI=PI_CONTROL_DEFAULTS;
PI_CONTROL_t Iq_PI=PI_CONTROL_DEFAULTS;
PI_CONTROL_t Theta_PI=PI_CONTROL_DEFAULTS;
PI_CONTROL_t weak_PI=PI_CONTROL_DEFAULTS;


double pid_realize(PI_CONTROL_t *pid)
{
	/*计算目标值与实际值的误差*/
	pid->cError = (pid->Inref - pid->InMeas) / 100;

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
	p->Ki = 0.2;
	p->Kd = 0.02;
	p->OutMax = 100;
	p->OutMin = -100;
	*output = pid_realize(p);
}

void Iq_Loop (double *output , PI_CONTROL_t *p)
{

	p->Kp = 0.02;
	p->Ki = 0.05;
	p->Kd = 0;
	p->OutMax = 24;
	p->OutMin = -24;
	*output = pid_realize(p);
}

void Id_Loop (double *output , PI_CONTROL_t *p)
{

	p->Kp = 0.2;
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

void weaken_Loop(double *output, PI_CONTROL_t *p)
{
	p->Kp = 0.01;
	p->Ki = 0.3;
	p->Kd = 0;
	p->OutMax = 24;
	p->OutMin = -24;
	*output = pid_realize(p);
}

void PID_Calu(double *output, PI_CONTROL_t *p, int SelectFlag) {
	switch(SelectFlag)
	{
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

	case weaken_Select_Flag:
		weaken_Loop(output, p);
		break;
	}
}
