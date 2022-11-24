/*
 * Weak_control.h
 *
 *  Created on: 2022年11月23日
 *      Author: HUAWEI
 */

#ifndef WEAK_CONTROL_H_
#define WEAK_CONTROL_H_
#include "default.h"

typedef struct _MTPA_loop
{
	double Udc_max;
	double Is_max;
	double Us;
	double Is;
	double id_weaken;
	double iq_weaken;
} MTPA_Loop_t;

typedef struct _weaken_loop
{
	double Udc_max;
	double Is_max;
	double Us;
	double Is;
	double id_weaken;
	double iq_weaken;
} weaken_Loop_t;

extern weaken_Loop_t weaken_Loop_struct;
extern MTPA_Loop_t MTPA_Loop_struct;


void MTPA_loop(MTPA_Loop_t *p, double Iq_ref);
void weak_loop_preAngel(weaken_Loop_t *, double Iq_ref);


#endif /* WEAK_CONTROL_H_ */
