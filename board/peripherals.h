/***********************************************************************************************************************
 * This file was generated by the MCUXpresso Config Tools. Any manual edits made to this file
 * will be overwritten if the respective MCUXpresso Config Tools is used to update this file.
 **********************************************************************************************************************/

#ifndef _PERIPHERALS_H_
#define _PERIPHERALS_H_

/***********************************************************************************************************************
 * Included files
 **********************************************************************************************************************/
#include "fsl_common.h"
#include "fsl_clock.h"
#include "fsl_ftm.h"
#include "fsl_uart.h"
#include "fsl_adc16.h"

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

/***********************************************************************************************************************
 * Definitions
 **********************************************************************************************************************/
/* Definitions for BOARD_InitPeripherals functional group */
/* Definition of peripheral ID */
#define FTM3_PERIPHERAL FTM3
/* Definition of the clock source frequency */
#define FTM3_CLOCK_SOURCE 47988736UL
/* Definition of the clock source frequency */
#define FTM3_TIMER_MODULO_VALUE 99
/* Definition of peripheral ID */
#define UART1_PERIPHERAL UART1
/* Definition of the clock source frequency */
#define UART1_CLOCK_SOURCE CLOCK_GetFreq(UART1_CLK_SRC)
/* Definition of peripheral ID */
#define FTM0_PERIPHERAL FTM0
/* Definition of the clock source frequency */
#define FTM0_CLOCK_SOURCE 47988736UL
/* Definition of the clock source frequency */
#define FTM0_TIMER_MODULO_VALUE 2998
/* FTM0 interrupt vector ID (number). */
#define FTM0_IRQN FTM0_IRQn
/* FTM0 interrupt handler identifier. */
#define FTM0_IRQHANDLER FTM0_IRQHandler
/* Alias for ADC0 peripheral */
#define ADC0_PERIPHERAL ADC0
/* ADC0 interrupt vector ID (number). */
#define ADC0_IRQN ADC0_IRQn
/* ADC0 interrupt handler identifier. */
#define ADC0_IRQHANDLER ADC0_IRQHandler
/* Channel 0 (SE.2) conversion control group. */
#define ADC0_CH0_CONTROL_GROUP 0
/* Channel 1 (SE.5a) conversion control group. */
#define ADC0_CH1_CONTROL_GROUP 0
/* Channel 2 (SE.6a) conversion control group. */
#define ADC0_CH2_CONTROL_GROUP 0
/* Definition of peripheral ID */
#define FTM1_PERIPHERAL FTM1
/* Definition of the clock source frequency */
#define FTM0_CLOCK_SOURCE 47988736UL
/* Definition of the clock source frequency */
#define FTM0_TIMER_MODULO_VALUE 1070
/* FTM0 interrupt vector ID (number). */
#define FTM0_IRQN FTM0_IRQn
/* FTM0 interrupt handler identifier. */
#define FTM0_IRQHANDLER FTM0_IRQHandler

/***********************************************************************************************************************
 * Global variables
 **********************************************************************************************************************/
extern const ftm_config_t FTM3_config;
extern const uart_config_t UART1_config;
extern const ftm_config_t FTM0_config;
extern adc16_channel_config_t ADC0_channelsConfig[3];
extern const adc16_config_t ADC0_config;
extern const adc16_channel_mux_mode_t ADC0_muxMode;
extern const adc16_hardware_average_mode_t ADC0_hardwareAverageMode;
extern const ftm_config_t FTM1_config;

/***********************************************************************************************************************
 * Initialization functions
 **********************************************************************************************************************/

void BOARD_InitPeripherals(void);

/***********************************************************************************************************************
 * BOARD_InitBootPeripherals function
 **********************************************************************************************************************/
void BOARD_InitBootPeripherals(void);

#if defined(__cplusplus)
}
#endif

#endif /* _PERIPHERALS_H_ */
