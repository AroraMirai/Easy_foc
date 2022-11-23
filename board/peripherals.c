/***********************************************************************************************************************
 * This file was generated by the MCUXpresso Config Tools. Any manual edits made to this file
 * will be overwritten if the respective MCUXpresso Config Tools is used to update this file.
 **********************************************************************************************************************/

/* clang-format off */
/* TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
!!GlobalInfo
product: Peripherals v11.0
processor: MKV56F512xxx24
package_id: MKV56F512VLL24
mcu_data: ksdk2_0
processor_version: 12.0.0
functionalGroups:
- name: BOARD_InitPeripherals
  UUID: 6bd4bc25-bf09-4566-9af3-96c017c984d7
  called_from_default_init: true
  selectedCore: core0
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS **********/

/* TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
component:
- type: 'system'
- type_id: 'system_54b53072540eeeb8f8e9343e71f28176'
- global_system_definitions:
  - user_definitions: ''
  - user_includes: ''
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS **********/

/* TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
component:
- type: 'uart_cmsis_common'
- type_id: 'uart_cmsis_common_9cb8e302497aa696fdbb5a4fd622c2a8'
- global_USART_CMSIS_common:
  - quick_selection: 'default'
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS **********/

/* TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
component:
- type: 'gpio_adapter_common'
- type_id: 'gpio_adapter_common_57579b9ac814fe26bf95df0a384c36b6'
- global_gpio_adapter_common:
  - quick_selection: 'default'
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS **********/
/* clang-format on */

/***********************************************************************************************************************
 * Included files
 **********************************************************************************************************************/
#include "peripherals.h"

/***********************************************************************************************************************
 * BOARD_InitPeripherals functional group
 **********************************************************************************************************************/
/***********************************************************************************************************************
 * NVIC initialization code
 **********************************************************************************************************************/
/* clang-format off */
/* TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
instance:
- name: 'NVIC'
- type: 'nvic'
- mode: 'general'
- custom_name_enabled: 'false'
- type_id: 'nvic_57b5eef3774cc60acaede6f5b8bddc67'
- functional_group: 'BOARD_InitPeripherals'
- peripheral: 'NVIC'
- config_sets:
  - nvic:
    - interrupt_table:
      - 0: []
    - interrupts: []
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS **********/
/* clang-format on */

/* Empty initialization function (commented out)
static void NVIC_init(void) {
} */

/***********************************************************************************************************************
 * FTM3 initialization code
 **********************************************************************************************************************/
/* clang-format off */
/* TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
instance:
- name: 'FTM3'
- type: 'ftm'
- mode: 'CenterAligned'
- custom_name_enabled: 'false'
- type_id: 'ftm_cf73470dab578a761c1bb272554a7d11'
- functional_group: 'BOARD_InitPeripherals'
- peripheral: 'FTM3'
- config_sets:
  - ftm_main_config:
    - ftm_config:
      - clockSource: 'kFTM_SystemClock'
      - clockSourceFreq: 'BOARD_BootClockRUN'
      - timerPrescaler: '1'
      - timerOutputFrequency: '200'
      - systemClockSource: 'BusInterfaceClock'
      - systemClockSourceFreq: 'mirrored_value'
      - faultMode: 'kFTM_Fault_Disable'
      - inputFilterPeriod: '1'
      - faultInputs:
        - 0:
          - enableFaultInput: 'false'
          - faultLevelVal: 'low'
          - useFaultFilter: 'false'
        - 1:
          - enableFaultInput: 'false'
          - faultLevelVal: 'low'
          - useFaultFilter: 'false'
        - 2:
          - enableFaultInput: 'false'
          - faultLevelVal: 'low'
          - useFaultFilter: 'false'
        - 3:
          - enableFaultInput: 'false'
          - faultLevelVal: 'low'
          - useFaultFilter: 'false'
      - deadTimePrescale: 'kFTM_Deadtime_Prescale_1'
      - deadTimePeriod: '0'
      - pwmSyncMode: 'kFTM_SoftwareTrigger'
      - reloadPoints: ''
      - extTriggers: ''
      - chnlInitState: ''
      - chnlPolarity: ''
      - bdmMode: 'kFTM_BdmMode_0'
      - useGlobalTimeBase: 'false'
    - timer_interrupts: ''
    - enable_irq: 'false'
    - ftm_interrupt:
      - IRQn: 'FTM3_IRQn'
      - enable_interrrupt: 'enabled'
      - enable_priority: 'false'
      - priority: '0'
      - enable_custom_name: 'false'
    - EnableTimerInInit: 'true'
  - ftm_center_aligned_mode:
    - ftm_center_aligned_channels_config:
      - 0:
        - channelId: ''
        - chnlNumber: 'kFTM_Chnl_0'
        - level: 'kFTM_HighTrue'
        - dutyValueStr: '0'
        - enable_chan_irq: 'false'
      - 1:
        - channelId: ''
        - chnlNumber: 'kFTM_Chnl_1'
        - level: 'kFTM_HighTrue'
        - dutyValueStr: '0'
        - enable_chan_irq: 'false'
      - 2:
        - channelId: ''
        - chnlNumber: 'kFTM_Chnl_2'
        - level: 'kFTM_HighTrue'
        - dutyValueStr: '0'
        - enable_chan_irq: 'false'
      - 3:
        - channelId: ''
        - chnlNumber: 'kFTM_Chnl_3'
        - level: 'kFTM_HighTrue'
        - dutyValueStr: '0'
        - enable_chan_irq: 'false'
      - 4:
        - channelId: ''
        - chnlNumber: 'kFTM_Chnl_4'
        - level: 'kFTM_HighTrue'
        - dutyValueStr: '0'
        - enable_chan_irq: 'false'
      - 5:
        - channelId: ''
        - chnlNumber: 'kFTM_Chnl_5'
        - level: 'kFTM_HighTrue'
        - dutyValueStr: '0'
        - enable_chan_irq: 'false'
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS **********/
/* clang-format on */
const ftm_config_t FTM3_config = {
  .prescale = kFTM_Prescale_Divide_1,
  .faultMode = kFTM_Fault_Disable,
  .faultFilterValue = 0,
  .deadTimePrescale = kFTM_Deadtime_Prescale_1,
  .deadTimeValue = 0,
  .pwmSyncMode = kFTM_SoftwareTrigger,
  .reloadPoints = 0,
  .extTriggers = 0,
  .chnlInitState = 0,
  .chnlPolarity = 0,
  .bdmMode = kFTM_BdmMode_0,
  .useGlobalTimeBase = false
};
const ftm_chnl_pwm_config_param_t FTM3_centerPwmSignalParams[] = { 
  {
    .chnlNumber = kFTM_Chnl_0,
    .level = kFTM_HighTrue,
    .dutyValue = 0,
  },
  {
    .chnlNumber = kFTM_Chnl_1,
    .level = kFTM_HighTrue,
    .dutyValue = 0,
  },
  {
    .chnlNumber = kFTM_Chnl_2,
    .level = kFTM_HighTrue,
    .dutyValue = 0,
  },
  {
    .chnlNumber = kFTM_Chnl_3,
    .level = kFTM_HighTrue,
    .dutyValue = 0,
  },
  {
    .chnlNumber = kFTM_Chnl_4,
    .level = kFTM_HighTrue,
    .dutyValue = 0,
  },
  {
    .chnlNumber = kFTM_Chnl_5,
    .level = kFTM_HighTrue,
    .dutyValue = 0,
  }
};

static void FTM3_init(void) {
  FTM_Init(FTM3_PERIPHERAL, &FTM3_config);
  FTM_SetTimerPeriod(FTM3_PERIPHERAL, FTM3_TIMER_MODULO_VALUE);
  FTM_SetupPwmMode(FTM3_PERIPHERAL, FTM3_centerPwmSignalParams, sizeof(FTM3_centerPwmSignalParams) / sizeof(ftm_chnl_pwm_config_param_t), kFTM_CenterAlignedPwm);
  FTM_StartTimer(FTM3_PERIPHERAL, kFTM_SystemClock);
}

/***********************************************************************************************************************
 * UART1 initialization code
 **********************************************************************************************************************/
/* clang-format off */
/* TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
instance:
- name: 'UART1'
- type: 'uart'
- mode: 'polling'
- custom_name_enabled: 'false'
- type_id: 'uart_88ab1eca0cddb7ee407685775de016d5'
- functional_group: 'BOARD_InitPeripherals'
- peripheral: 'UART1'
- config_sets:
  - uartConfig_t:
    - uartConfig:
      - clockSource: 'BusInterfaceClock'
      - clockSourceFreq: 'GetFreq'
      - baudRate_Bps: '2500000'
      - parityMode: 'kUART_ParityDisabled'
      - stopBitCount: 'kUART_OneStopBit'
      - txFifoWatermark: '0'
      - rxFifoWatermark: '1'
      - idleType: 'kUART_IdleTypeStartBit'
      - enableTx: 'true'
      - enableRx: 'true'
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS **********/
/* clang-format on */
const uart_config_t UART1_config = {
  .baudRate_Bps = 2500000UL,
  .parityMode = kUART_ParityDisabled,
  .stopBitCount = kUART_OneStopBit,
  .txFifoWatermark = 0U,
  .rxFifoWatermark = 1U,
  .idleType = kUART_IdleTypeStartBit,
  .enableTx = true,
  .enableRx = true
};

static void UART1_init(void) {
  UART_Init(UART1_PERIPHERAL, &UART1_config, UART1_CLOCK_SOURCE);
}

/***********************************************************************************************************************
 * FTM0 initialization code
 **********************************************************************************************************************/
/* clang-format off */
/* TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
instance:
- name: 'FTM0'
- type: 'ftm'
- mode: 'EdgeAligned'
- custom_name_enabled: 'false'
- type_id: 'ftm_cf73470dab578a761c1bb272554a7d11'
- functional_group: 'BOARD_InitPeripherals'
- peripheral: 'FTM0'
- config_sets:
  - ftm_main_config:
    - ftm_config:
      - clockSource: 'kFTM_SystemClock'
      - clockSourceFreq: 'BOARD_BootClockRUN'
      - timerPrescaler: '32'
      - timerOutputFrequency: '500 hz'
      - systemClockSource: 'BusInterfaceClock'
      - systemClockSourceFreq: 'mirrored_value'
      - faultMode: 'kFTM_Fault_Disable'
      - inputFilterPeriod: '1'
      - faultInputs:
        - 0:
          - enableFaultInput: 'false'
          - faultLevelVal: 'low'
          - useFaultFilter: 'false'
        - 1:
          - enableFaultInput: 'false'
          - faultLevelVal: 'low'
          - useFaultFilter: 'false'
        - 2:
          - enableFaultInput: 'false'
          - faultLevelVal: 'low'
          - useFaultFilter: 'false'
        - 3:
          - enableFaultInput: 'false'
          - faultLevelVal: 'low'
          - useFaultFilter: 'false'
      - deadTimePrescale: 'kFTM_Deadtime_Prescale_1'
      - deadTimePeriod: '0'
      - pwmSyncMode: 'kFTM_SoftwareTrigger'
      - reloadPoints: ''
      - extTriggers: ''
      - chnlInitState: ''
      - chnlPolarity: ''
      - bdmMode: 'kFTM_BdmMode_0'
      - useGlobalTimeBase: 'false'
    - timer_interrupts: 'kFTM_TimeOverflowInterruptEnable'
    - enable_irq: 'true'
    - ftm_interrupt:
      - IRQn: 'FTM0_IRQn'
      - enable_interrrupt: 'enabled'
      - enable_priority: 'false'
      - priority: '0'
      - enable_custom_name: 'false'
    - EnableTimerInInit: 'true'
  - ftm_edge_aligned_mode:
    - ftm_edge_aligned_channels_config: []
    - quick_selection: 'default'
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS **********/
/* clang-format on */
const ftm_config_t FTM0_config = {
  .prescale = kFTM_Prescale_Divide_32,
  .faultMode = kFTM_Fault_Disable,
  .faultFilterValue = 0,
  .deadTimePrescale = kFTM_Deadtime_Prescale_1,
  .deadTimeValue = 0,
  .pwmSyncMode = kFTM_SoftwareTrigger,
  .reloadPoints = 0,
  .extTriggers = 0,
  .chnlInitState = 0,
  .chnlPolarity = 0,
  .bdmMode = kFTM_BdmMode_0,
  .useGlobalTimeBase = false
};

static void FTM0_init(void) {
  FTM_Init(FTM0_PERIPHERAL, &FTM0_config);
  FTM_SetTimerPeriod(FTM0_PERIPHERAL, FTM0_TIMER_MODULO_VALUE);
  FTM_EnableInterrupts(FTM0_PERIPHERAL, kFTM_TimeOverflowInterruptEnable);
  /* Enable interrupt FTM0_IRQn request in the NVIC. */
  EnableIRQ(FTM0_IRQN);
  FTM_StartTimer(FTM0_PERIPHERAL, kFTM_SystemClock);
}

/***********************************************************************************************************************
 * ADC0 initialization code
 **********************************************************************************************************************/
/* clang-format off */
/* TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
instance:
- name: 'ADC0'
- type: 'adc16'
- mode: 'ADC'
- custom_name_enabled: 'false'
- type_id: 'adc16_7a29cdeb84266e77f0c7ceac1b49fe2d'
- functional_group: 'BOARD_InitPeripherals'
- peripheral: 'ADC0'
- config_sets:
  - fsl_adc16:
    - adc16_config:
      - referenceVoltageSource: 'kADC16_ReferenceVoltageSourceVref'
      - clockSource: 'kADC16_ClockSourceAlt0'
      - enableAsynchronousClock: 'true'
      - clockDivider: 'kADC16_ClockDivider1'
      - resolution: 'kADC16_ResolutionSE12Bit'
      - longSampleMode: 'kADC16_LongSampleDisabled'
      - enableHighSpeed: 'false'
      - enableLowPower: 'false'
      - enableContinuousConversion: 'false'
    - adc16_channel_mux_mode: 'kADC16_ChannelMuxA'
    - adc16_hardware_compare_config:
      - hardwareCompareModeEnable: 'false'
    - doAutoCalibration: 'false'
    - offset: '0'
    - trigger: 'false'
    - hardwareAverageConfiguration: 'kADC16_HardwareAverageDisabled'
    - enable_dma: 'false'
    - enable_irq: 'false'
    - adc_interrupt:
      - IRQn: 'ADC0_IRQn'
      - enable_interrrupt: 'enabled'
      - enable_priority: 'false'
      - priority: '0'
      - enable_custom_name: 'false'
    - adc16_channels_config:
      - 0:
        - channelName: ''
        - enableDifferentialConversion: 'false'
        - channelNumber: 'SE.2'
        - enableInterruptOnConversionCompleted: 'false'
        - channelGroup: '0'
        - initializeChannel: 'false'
      - 1:
        - channelName: ''
        - enableDifferentialConversion: 'false'
        - channelNumber: 'SE.5a'
        - enableInterruptOnConversionCompleted: 'false'
        - channelGroup: '0'
        - initializeChannel: 'false'
      - 2:
        - channelName: ''
        - enableDifferentialConversion: 'false'
        - channelNumber: 'SE.6a'
        - enableInterruptOnConversionCompleted: 'false'
        - channelGroup: '0'
        - initializeChannel: 'false'
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS **********/
/* clang-format on */
adc16_channel_config_t ADC0_channelsConfig[3] = {
  {
    .channelNumber = 2U,
    .enableDifferentialConversion = false,
    .enableInterruptOnConversionCompleted = false,
  },
  {
    .channelNumber = 5U,
    .enableDifferentialConversion = false,
    .enableInterruptOnConversionCompleted = false,
  },
  {
    .channelNumber = 6U,
    .enableDifferentialConversion = false,
    .enableInterruptOnConversionCompleted = false,
  }
};
const adc16_config_t ADC0_config = {
  .referenceVoltageSource = kADC16_ReferenceVoltageSourceVref,
  .clockSource = kADC16_ClockSourceAlt0,
  .enableAsynchronousClock = true,
  .clockDivider = kADC16_ClockDivider1,
  .resolution = kADC16_ResolutionSE12Bit,
  .longSampleMode = kADC16_LongSampleDisabled,
  .enableHighSpeed = false,
  .enableLowPower = false,
  .enableContinuousConversion = false
};
const adc16_channel_mux_mode_t ADC0_muxMode = kADC16_ChannelMuxA;
const adc16_hardware_average_mode_t ADC0_hardwareAverageMode = kADC16_HardwareAverageDisabled;

static void ADC0_init(void) {
  /* Initialize ADC16 converter */
  ADC16_Init(ADC0_PERIPHERAL, &ADC0_config);
  /* Make sure, that software trigger is used */
  ADC16_EnableHardwareTrigger(ADC0_PERIPHERAL, false);
  /* Configure hardware average mode */
  ADC16_SetHardwareAverage(ADC0_PERIPHERAL, ADC0_hardwareAverageMode);
  /* Configure channel multiplexing mode */
  ADC16_SetChannelMuxMode(ADC0_PERIPHERAL, ADC0_muxMode);
}

/***********************************************************************************************************************
 * Initialization functions
 **********************************************************************************************************************/
void BOARD_InitPeripherals(void)
{
  /* Initialize components */
  FTM3_init();
  UART1_init();
  FTM0_init();
  ADC0_init();
}

/***********************************************************************************************************************
 * BOARD_InitBootPeripherals function
 **********************************************************************************************************************/
void BOARD_InitBootPeripherals(void)
{
  BOARD_InitPeripherals();
}
