/*
 * Current_ipark.h
 *
 *  Created on: 2022年10月27日
 *      Author: HUAWEI
 */

#ifndef PARK_CLARKE_H_
#define PARK_CLARKE_H_
#include "default.h"
typedef struct _PARK_CLARKE{
	double Alpha;
	double Beta;


	double Ds;
	double Qs;

	double As;
	double Bs;
	double Cs;

	double Theta_e;
	double the;
	double Udc;
} PARK_CLARKE_t;

extern PARK_CLARKE_t Udq_to_AlphaBeta;
extern PARK_CLARKE_t Iabc_to_AlphaBeta;
extern PARK_CLARKE_t IAlphaBeta_to_dq;


void PARK_CLARKE_Init(PARK_CLARKE_t *p);
void ipark_Transf(PARK_CLARKE_t *p);
void park_Transf(PARK_CLARKE_t *p);
void clarke_Transf(PARK_CLARKE_t *p);


#endif /* PARK_CLARKE_H_ */
