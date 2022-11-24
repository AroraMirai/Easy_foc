#ifndef __SVPWM_H
#define __SVPWM_H
#include "default.h"


typedef struct
{
	double Ualpha; // Input: reference alpha-axis phase voltage
	double Ubeta;  // Input: reference beta-axis phase voltage
	double Vdc;    // Input: DC voltage
	double Tp;     // Input: PWM Modulation Period

	double Tcmpa;  // Output: reference phase-a switching function
	double Tcmpb;  // Output: reference phase-b switching function
	double Tcmpc;  // Output: reference phase-c switching function
					// void (*calc)();     // Pointer to calculation function
	uint8_t T_circleA;
	uint8_t T_circleB;
	uint8_t T_circleC;
} SVPWM_T;

extern SVPWM_T svpwm_struct;

void svpwm_init();

void svpwm_calc_t(SVPWM_T *p);

void updata_PWM(SVPWM_T *p);

#endif
