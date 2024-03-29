/**
 * @file    MVK56second.c
 * @brief   Application entry point.
 */
#include "MKV56F24.h"
#include "board.h"
#include "clock_config.h"
#include "fsl_common.h"
#include "fsl_debug_console.h"
#include "fsl_gpio.h"
#include "fsl_pwm.h"
#include "peripherals.h"
#include "pin_mux.h"

/* insert other include files here. */
#include "default.h"
/* insert other definitions and declarations here. */

/* Control Input init */

/* 前馈的给定参考值 */
#define N_TARGET 100
/*======================flag======================*/
volatile bool ftmIrqFlag = false;
volatile int test1 = 0;
double Iq_test = 0;
double Uq_test = 0;
/* The ftm0 interrupt timer is 2ms
 * 其中还包括了电机的ADC采样基准值的计算
 */
void FTM0_IRQHandler() {
	ftmIrqFlag = true;
	uart_Read(&posGet_struct);  // 通过UART读取编码器值
	pos_Calu(&posGet_struct);  // 通过读取的编码器值计算电机的机械角度和电角度
	test1++;
	adc_Udc_result(&adcGet_struct);   // 通过ADC采集直流电压
	adc_Iuvw_result(&adcGet_struct);  // 通过ADC采集uv相电流值
	FTM_ClearStatusFlags(FTM0, kFTM_TimeOverflowFlag);
	__DSB();
}

void FTM1_IRQHandler() {
	speed_Calu(&posGet_struct, &speed_struct, ftmIrqFlag);  // 通过中断计算转速

	Udq_to_AlphaBeta.Theta_e = posGet_struct.theta_e;  // 将电角度传给电压电流计算结构体
	IAlphaBeta_to_dq.Theta_e = posGet_struct.theta_e;

	N_PI.InMeas = speed_struct.Nr;
	N_PI.Inref = N_TARGET;
	PI_Calu(&Iq_PI.Inref, &N_PI,
	Nr_Select_Flag);  // 转速PI控制模块，通过给定转速与实际转速的比得到数值
	//		N_STW.In_meas = speed_struct.Nr;
	//		N_STW.In_ref = N_TARGET;
	//		STW_SMC_Loop(&Iq_PI.Inref, &N_STW, Nr_Select_Flag);

	IAlphaBeta_to_dq.As = adcGet_struct.Ia;
	IAlphaBeta_to_dq.Bs = adcGet_struct.Ib;
	IAlphaBeta_to_dq.Cs = adcGet_struct.Ic;

	clarke_Transf(&IAlphaBeta_to_dq);
	park_Transf(&IAlphaBeta_to_dq);
	/*--------------------------------------------------------------------------------
	 * -----------------------------------Iq Loop-------------------------------------
	 *--------------------------------------------------------------------------------
	 */
	//		Iq_PI.InMeas = - IAlphaBeta_to_dq.Qs;
	//		PI_Calu(&Uq_test,&Iq_PI, Iq_Select_Flag);
	//		PID_Calu(&Uq_test, &Iq_PID, Iq_Select_Flag);
	////转速PI控制模块，通过给定转速与实际转速的比得到数值 		Udq_to_AlphaBeta.Qs =
	//Uq_test;
	Iq_STW.In_meas = IAlphaBeta_to_dq.Qs;
	Iq_STW.In_ref = Iq_PI.Inref;
	STW_SMC_Loop(&Udq_to_AlphaBeta.Qs, &Iq_STW, Iq_Select_Flag);

	/*---------------------------------------------------------------------------------
	 * --------------------------------Id  PID Loop-----------------------------------
	 * --------------------------------------------------------------------------------
	 */
	Id_STW.In_meas = IAlphaBeta_to_dq.Ds;
	Id_STW.In_ref = 0;
	STW_SMC_Loop(&Udq_to_AlphaBeta.Ds, &Id_STW, Id_Select_Flag);
	//		Id_PI.InMeas = - IAlphaBeta_to_dq.Ds;
	//		Id_PI.Inref = 0;
	//		PI_Calu(&Udq_to_AlphaBeta.Ds, &Id_PI, Id_Select_Flag);
	//		Udq_to_AlphaBeta.Qs = 3;
	//		Udq_to_AlphaBeta.Ds = 0;

	ipark_Transf(&Udq_to_AlphaBeta);  // 反PARK变换
	svpwm_init(&svpwm_struct);

	svpwm_calc_t(&svpwm_struct);  // PI输出的电压进入前馈环进入SVPWM部分

	updata_PWM(&svpwm_struct);  // 更新FTM的PWM输出占空比
	__DSB();
}

/*
 * @brief   Application entry point.
 */
void main(void) {
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

	while (1) {

	}
}
