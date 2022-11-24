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

void uart_Read(pos_Get_t *p)
{
	GPIO_PinWrite(BOARD_INITPINS_CODE_ORDER_GPIO, BOARD_INITPINS_CODE_ORDER_PIN, 1);

	UART_WriteBlocking(UART1_PERIPHERAL, txbuff_t, sizeof(txbuff_t) / sizeof(txbuff_t[0]));

	GPIO_PinWrite(BOARD_INITPINS_CODE_ORDER_GPIO, BOARD_INITPINS_CODE_ORDER_PIN, 0);

	UART_ReadBlocking(UART1_PERIPHERAL, p->transbuff_t, sizeof(p->transbuff_t) / sizeof(p->transbuff_t[0]));
}

/*
 * @brief	根据编码器值得到电机位置信息
 */

void pos_Calu(pos_Get_t *p)
{
	uint32_t pos_code_l, pos_code_m, pos_code_h, pos_code = 0;

	if (p->transbuff_t[0] == 0x1A && p->transbuff_t[1] == 0x0)
	{
		pos_code_l = p->transbuff_t[2];
		pos_code_m = p->transbuff_t[3];
		pos_code_h = p->transbuff_t[4];
		pos_code = pos_code_l + (pos_code_m << 8) + (pos_code_h << 16);
	}

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
		//反向运行
		if (p->pos_last < p->pos_prev)
		{
			s->delta_Pos = - p->pos_last + p->pos_prev;
			if (s->delta_Pos < 0)
			{
				s->delta_Pos = (p->pos_prev + 360) - p->pos_last;
			}
		}

		//正向运行
		if (p->pos_last >= p->pos_prev)
		{
			s->delta_Pos = p->pos_last - p->pos_prev;
			if (s->delta_Pos < 0)
			{
				s->delta_Pos = (p->pos_last + 360) - p->pos_prev;
			}
		}

		ftmIrqFlag = false;
	}

	s->omega_m = s->delta_Pos / s->T_speed;				//omega_m的单位为rad/s
	double circle = 2 * PI;
	s->Nr = s->omega_m / circle;								//Nr的单位为r/s
}
