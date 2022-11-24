/*
 * ADC_get.h
 *
 *  Created on: 2022年11月2日
 *      Author: HUAWEI
 */

#ifndef ADC_GET_H_
#define ADC_GET_H_
#define Standard_N 1000
#define FILTER_N 5
#include "default.h"
#include "fsl_adc16.h"

typedef struct _adc
{
	double Udc;
	double Ia;
	double Ib;
	double Ic;
	double Ia_standard;
	double Ib_standard;
} ADCresult_t;

extern ADCresult_t adcGet_struct;


void adc_struct_Init(ADCresult_t *p);
//void ADC0_init(void);
void adc_channel_init(ADC_Type *base, uint32_t channelGroup, const adc16_channel_config_t *config);

uint32_t adc_get(ADC_Type *base, uint32_t channelGroup);

double adc_filter_result(ADC_Type *base, uint32_t channelGroup, const adc16_channel_config_t *config);
double get_ADC_standard(ADC_Type *base, uint32_t channelGroup, const adc16_channel_config_t *config);
void adc_add_standard(ADCresult_t *p);

void adc_Udc_result(ADCresult_t *);
void adc_Iuvw_result(ADCresult_t *);


#endif /* ADC_GET_H_ */
