/*
 * ADC_get.c
 *
 *  Created on: 2022年11月2日
 *      Author: HUAWEI
 */
#include "ADC_get.h"

ADCresult_t adcGet_struct;

void adc_struct_Init(ADCresult_t *p) {
	p->Udc = 0;
	p->Ia = 0;
	p->Ib = 0;
	p->Ic = 0;
	p->Ia_standard = 0;
	p->Ib_standard = 0;
}

/*
 * @brief ADC channel initialize
 *
 * @param base: ADC TYPE select
 * @param channelGroup: ADC channel group select. Group 0 or Group 1
 * @param config: adc configuration
 *
 * @return void
 */

void adc_channel_init(ADC_Type *base, uint32_t channelGroup, const adc16_channel_config_t *config)
{
	ADC16_SetChannelConfig(base, channelGroup, config);												//初始化ADC通道，同时初始化ADC采样结果寄存器
}

/*
 * @brief Get adc channel conversion value.
 *
 * @param base: ADC TYPE select
 * @param channelGroup: ADC channel group select. Group 0 or Group 1
 *
 * @return void
 */

uint32_t adc_get(ADC_Type *base, uint32_t channelGroup)
{
	uint32_t Sample = 0;																				//采样结果
	while (0u == (kADC16_ChannelConversionDoneFlag & ADC16_GetChannelStatusFlags(base, channelGroup)))	//等待通道采集结束

	{
	}

	Sample = ADC16_GetChannelConversionValue(base, channelGroup);										//将采集结果传递给结果变量
	return Sample;
}


/*
 * @brief get ADC conversion value and get ADC filter result
 *
 * @param base: ADC TYPE select
 * @param channelGroup: ADC channel group select. Group 0 or Group 1
 * @param config: adc configuration
 *
 * @return void
 */
double adc_filter_result(ADC_Type *base, uint32_t channelGroup,
		const adc16_channel_config_t *config)
{
	int i, j;
	double filter_temp, filter_sum = 0;
	double filter_buf[FILTER_N];
	for (i = 0; i < FILTER_N; i++)
	{
		adc_channel_init(base, channelGroup, config);
		filter_buf[i] = adc_get(base, channelGroup);
	}
// 采样值从小到大排列（冒泡法）
	for (j = 0; j < FILTER_N - 1; j++)
	{
		for (i = 0; i < FILTER_N - 1 - j; i++)
		{
			if (filter_buf[i] > filter_buf[i + 1])
			{
				filter_temp = filter_buf[i];
				filter_buf[i] = filter_buf[i + 1];
				filter_buf[i + 1] = filter_temp;
			}
		}
	}
// 去除最大最小极值后求平均
	for (i = 1; i < FILTER_N - 1; i++)
		filter_sum += filter_buf[i];
	return filter_sum / (FILTER_N - 2);
}


void adc_Udc_result(ADCresult_t *p)
{
	p->Udc = adc_filter_result(ADC0_PERIPHERAL, ADC0_CH0_CONTROL_GROUP, &ADC0_channelsConfig[0]);
}


double adc_get_standard(ADC_Type *base, uint32_t channelGroup, const adc16_channel_config_t *config)
{
	int i;
	double standard_sum = 0;
	double standard_buf[Standard_N];
	for (i = 0; i < Standard_N; i++)
	{
		adc_channel_init(base, channelGroup, config);
		standard_buf[i] = adc_get(base, channelGroup);
	}

	for (i = 0; i < Standard_N; i++)
	{
		standard_sum += (double)standard_buf[i];
	}
	return (standard_sum / Standard_N);
}


void adc_add_standard(ADCresult_t *p)
{
	p->Ia_standard = adc_get_standard(ADC0_PERIPHERAL, ADC0_CH1_CONTROL_GROUP, &ADC0_channelsConfig[1]);
	p->Ib_standard = adc_get_standard(ADC0_PERIPHERAL, ADC0_CH1_CONTROL_GROUP, &ADC0_channelsConfig[2]);
}


void adc_Iuvw_result(ADCresult_t *p)
{
	p->Ia = adc_filter_result(ADC0_PERIPHERAL, ADC0_CH1_CONTROL_GROUP, &ADC0_channelsConfig[1]) - 2006.1;
	p->Ib = adc_filter_result(ADC0_PERIPHERAL, ADC0_CH1_CONTROL_GROUP, &ADC0_channelsConfig[2]) - 1969.3;
//	p->Ia = adc_filter_result(ADC0_PERIPHERAL, ADC0_CH1_CONTROL_GROUP, &ADC0_channelsConfig[1]) - p->Ia_standard;
//	p->Ib = adc_filter_result(ADC0_PERIPHERAL, ADC0_CH1_CONTROL_GROUP, &ADC0_channelsConfig[2]) - p->Ib_standard;
	p->Ic = -(p->Ia + p->Ib);
}


