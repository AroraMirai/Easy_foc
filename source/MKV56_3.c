/**
 * @file    MVK56second.c
 * @brief   Application entry point.
 */
#include "fsl_common.h"
#include "board.h"
#include "fsl_gpio.h"
#include "fsl_pwm.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKV56F24.h"
#include "fsl_debug_console.h"

/* insert other include files here. */
#include <math.h>
#include "default.h"
/* insert other definitions and declarations here. */

/* Control Input init */

/* 前馈的给定参考值 */
#define N_TARGET 5
/*======================flag======================*/
volatile bool ftmIrqFlag = false;
volatile int test1 = 0;
/* The ftm0 interrupt timer is 2ms
 * 其中还包括了电机的ADC采样基准值的计算
 */
void FTM0_IRQHandler()
{
	ftmIrqFlag = true;
	uart_Read(&posGet_struct);									//通过UART读取编码器值
	pos_Calu(&posGet_struct);									//通过读取的编码器值计算电机的机械角度和电角度
	test1++;
	FTM_ClearStatusFlags(FTM0, kFTM_TimeOverflowFlag);
	__DSB();
}

/*
 * @brief   Application entry point.
 */
void main(void)
{
	/* Init board hardware. */
	BOARD_InitBootPins();
	BOARD_InitBootClocks();
	BOARD_InitBootPeripherals();
#ifndef BOARD_INIT_DEBUG_CONSOLE_PERIPHERAL
	/* Init FSL debug console. */
	BOARD_InitDebugConsole();
#endif

//	ADC0_init();
	pos_t_Init(&posGet_struct);
	speed_t_Init(&speed_struct);
	PARK_CLARKE_Init(&IAlphaBeta_to_dq);
	PARK_CLARKE_Init(&Udq_to_AlphaBeta);
	adc_struct_Init(&adcGet_struct);

	while (1)
	{
		speed_Calu(&posGet_struct, &speed_struct, ftmIrqFlag);	//通过中断计算转速

		Udq_to_AlphaBeta.Theta_e = posGet_struct.theta_e;		//将电角度传给电压电流计算结构体
		IAlphaBeta_to_dq.Theta_e = posGet_struct.theta_e;

		N_PI.InMeas = speed_struct.Nr;
		N_PI.Inref = N_TARGET;
		N_Loop(&Iq_PI.InMeas, &N_PI);							//转速PI控制模块，通过给定转速与实际转速的比得到数值
//		test2++;
//		if ( test2 == 1 || test2 % 5000 == 0)
//		{
//			adc_add_standard(&adcGet_struct);
//		}
	  	adc_Udc_result(&adcGet_struct);							//通过ADC采集直流电压
		adc_Iuvw_result(&adcGet_struct);						//通过ADC采集uv相电流值

		IAlphaBeta_to_dq.As = adcGet_struct.Ia;
		IAlphaBeta_to_dq.Bs = adcGet_struct.Ib;
		IAlphaBeta_to_dq.Cs = adcGet_struct.Ic;

		clarke_Transf(&IAlphaBeta_to_dq);
		park_Transf(&IAlphaBeta_to_dq);

		Iq_PI.InMeas = - IAlphaBeta_to_dq.Qs;
		PID_Calu(&Udq_to_AlphaBeta.Qs,&Iq_PI, Iq_Select_Flag);

		Id_PI.InMeas = - IAlphaBeta_to_dq.Ds;
		Id_PI.Inref = 0;
		PID_Calu(&Udq_to_AlphaBeta.Ds, &Id_PI, Id_Select_Flag);

		ipark_Transf(&Udq_to_AlphaBeta);						//反PARK变换
		svpwm_init(&svpwm_struct);

		svpwm_calc_t(&svpwm_struct);							//PI输出的电压进入前馈环进入SVPWM部分

		updata_PWM(&svpwm_struct);								//更新FTM的PWM输出占空比
	}
}

