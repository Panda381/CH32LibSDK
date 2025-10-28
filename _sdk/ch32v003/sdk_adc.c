
// ****************************************************************************
//
//                         ADC Analog-to-digital converter
//
// ****************************************************************************

#include "../_include.h"

#if USE_ADC		// 1=use ADC peripheral

// Select ADC channel chan=0..9 to be converted on the rule sequence seq=1..16 (default 0; register RSQR1/RSQR2/RSQR3)
void ADCx_RSeq(ADC_t* adc, int seq, int chan)
{
	if (seq <= 6)
	{
		seq = (seq - 1) * 5;
		adc->RSQR3 = (adc->RSQR3 & ~(0x1f << seq)) | (chan << seq);
	}
	else if (seq <= 12)
	{
		seq = (seq - 7) * 5;
		adc->RSQR2 = (adc->RSQR2 & ~(0x1f << seq)) | (chan << seq);
	}
	else
	{
		seq = (seq - 13) * 5;
		adc->RSQR1 = (adc->RSQR1 & ~(0x1f << seq)) | (chan << seq);
	}
}

// Initialize ADC single conversion mode
// - Sampling time is not set, you can use ADCx_SampTime() to set it.
// - Get conversion result with ADCx_GetSingle().
void ADCx_InitSingle(ADC_t* adc)
{
	// reset ADC module
	if (adc == ADC1)
	{
		// enable clock for ADC
		RCC_ADC1ClkEnable();

		// reset ADC module
		RCC_ADC1Reset();
	}

	// select software trigger of rule channel conversion
	ADCx_ExtSel(adc, ADC_EXT_SWSTART);

	// enable externally triggered conversion for rule channels
	ADCx_ExtTrigEnable(adc);

	// set number of channels to be converted in a regular channel conversion sequence
	ADCx_RNum(adc, 1);

	// wake-up ADC
	ADCx_Enable(adc);
	WaitMs(1);

	// select calibration voltage
	ADC1_CalVol(ADC_CAL_24);

	// reset calibration
	ADC1_RstCalibStart();
	while (ADC1_RstCalibBusy()) {}

	// start calibration
	ADC1_CalibStart();
	while (ADC1_CalibBusy()) {}
}

// Get single conversion (chan = channel 0..9)
// - Conversion must be initialized using ADCx_InitSingle().
// - Before use, set the appropriate GPIO pin to analog input mode GPIO_MODE_AIN.
u16 ADCx_GetSingle(ADC_t* adc, int chan)
{
	// select channel to be converted
	ADCx_RSeq(adc, 1, chan);

	// software start conversion
	ADCx_SwStart(adc);

	// wait end of conversion
	while (!ADCx_EndGet(adc)) {}

	// get conversion result (and clear "end of conversion" flag)
	return ADCx_Data(adc);
}

// Get sum of multiple single conversions (chan = channel 0..9, num = number of samples)
// - Conversion must be initialized using ADCx_InitSingle().
// - Before use, set the appropriate GPIO pin to analog input mode GPIO_MODE_AIN.
int ADCx_GetSingleMul(ADC_t* adc, int chan, int num)
{
	int sum = 0;
	for (; num > 0; num--) sum += ADCx_GetSingle(adc, chan);
	return sum;
}

#endif // USE_ADC
