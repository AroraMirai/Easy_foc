/*
 * uart_pos.c
 *
 *  Created on: 2022年11月18日
 *      Author: HUAWEI
 */

#include "uart_pos.h"
uint8_t txbuff_t[] = { 0x1A };
pos_Get_t posGet_struct;
speed_Calu_t speed_struct;

void swap_data(volatile double *a, volatile double *b)
{
	uint32_t tmp;
	tmp = *a;
	*a = *b;
	*b = tmp;
}

void pos_t_Init(pos_Get_t *p)
{
	p->transbuff_t[11] = 0;
	p->motor_Pos = 0;
	p->pos_last = 0;
	p->pos_prev = 0;
	p->theta = 0;
	p->theta_e = 0;
}

void speed_t_Init(speed_Calu_t *p)
{
	p->Nr = 0;
	p->T_speed = 0.002;
	p->delta_Pos = 0;
	p->omega_m = 0;
}

uint32_t uart_Read(pos_Get_t *p)
{
	return Uart_ReadCode();
}

void pos_Calu(pos_Get_t *p)
{
	uint32_t pos_code_l, pos_code_m, pos_code_h, pos_code = 0;

	pos_code = uart_Read();

	uint32_t test_pos_code = pos_code * 4096 * 5 / 131072;
	p->motor_Pos = (((test_pos_code & 0xfff) - 2051) & 0xfff);

	p->theta = (double)pos_code * 360 / 131072;
	p->theta_e = (double)p->motor_Pos * 360 / 4096;

	swap_data(&p->pos_prev, &p->pos_last);
	p->pos_last = p->theta;
}

/*
 * @brief	电机转速的计算
 *
 * @param	pos_Get_t *p	电机位置读取的结构体，通过电机位置计算电机速度
 * @param	speed_Calu_t *s 电机转速相关计算的结构体
 * @param	ftmIrqFlag		FTM计数中断标志，当进入标志位之后 ftmIrqFlag = true
 *
 * return	void
 */
void speed_Calu(pos_Get_t *p, speed_Calu_t *s, bool ftmIrqFlag)
{
	if (true == ftmIrqFlag)
	{
		s->delta_Pos = p->pos_last - p->pos_prev;
		if (s->delta_Pos < 0)
		{
			s->delta_Pos = (p->pos_last + 360) - p->pos_prev;
		}
		ftmIrqFlag = false;
	}

	s->omega_m = (double)s->delta_Pos / s->T_speed;				//omega_m的单位为rad/s

	s->Nr = s->omega_m / 360;									//Nr的单位为r/s
}
