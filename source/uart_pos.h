/*
 * uart_pos.h
 *
 *  Created on: 2022年11月18日
 *      Author: HUAWEI
 */

#ifndef UART_POS_H_
#define UART_POS_H_
#include "default.h"

typedef struct _pos
{
	uint8_t transbuff_t[11];
	uint32_t motor_Pos;
	double theta;
	double theta_e;
	volatile double pos_prev;
	volatile double pos_last;
} pos_Get_t;

typedef struct _speed
{
	double T_speed;
	double delta_Pos;
	double Nr;
	double omega_m;
} speed_Calu_t;

extern pos_Get_t posGet_struct;
extern speed_Calu_t speed_struct;

void swap_data(volatile double *,volatile double *);
void pos_t_Init(pos_Get_t *p);
void uart_Read(pos_Get_t *p);
void pos_Calu(pos_Get_t *p);
void speed_t_Init(speed_Calu_t *p);
void speed_Calu(pos_Get_t *p, speed_Calu_t *s, bool ftmIrqFlag);

#endif /* UART_POS_H_ */
