/*
 * pid.h
 *
 *  Created on: 2022年10月18日
 *      Author: HUAWEI
 */

#ifndef PID_H_
#define PID_H_

#define DEAD_ZONE 0 			/*死区*/
#define INTEGRAL_ERR_ZONE 80	/*积分分离时对应的误差范围*/
#define INTEGRAL_MAX_VAL 2000   	/*积分范围限定，防止积分饱和*/
#define LIMIT_MIN_MAX(X,min,max) (x) = (((x)<=(min)) ? (min) :(((x) >= (max))? (max) : (x)))

#define Nr_Select_Flag 	0
#define Iq_Select_Flag 	1
#define Id_Select_Flag 	2
#define T_Select_Flag 	3
#define pos_Select_Flag 4
#define weaken_Select_Flag 5

#include "fsl_common.h"

typedef struct {
	double dSum; 				//Integrator sum
	double cError; 				// ERROR every calc;
	double cError_last;
	double U;
	double Kp;					//Proportional Gain;
	double Ki;					//Integral Gain
	double Kd;
	double OutMax;				//PI Output maximum limit
	double OutMin;				//PI output minimum limit
	double Inref;				//Input reference
	double InMeas;				//Input measure
	double Out;					//PID out
} PI_CONTROL_t;

extern PI_CONTROL_t N_PI;
extern PI_CONTROL_t Id_PI;
extern PI_CONTROL_t Iq_PI;
extern PI_CONTROL_t Theta_PI;
extern PI_CONTROL_t weak_PI;

double pid_realize(PI_CONTROL_t *pid);

void N_Loop (double *output , PI_CONTROL_t *p);
void Iq_Loop (double *output , PI_CONTROL_t *p);
void Id_Loop (double *output , PI_CONTROL_t *p);
void T_Loop (double *output , PI_CONTROL_t *p);
void pos_Loop (double *output , PI_CONTROL_t *p);
void weaken_Loop(double *output, PI_CONTROL_t *p);

void PID_Calu(double *output, PI_CONTROL_t *p, int SelectFlag);

#endif /* PID_H_ */
