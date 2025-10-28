
// ****************************************************************************
//
//                         ADC Analog-to-digital converter
//
// ****************************************************************************
// 10-bit conversion, max. 24MHz input clock, 8+2 channels (channel 8: reference
//  voltage 1.2V, channel 9: calibration voltage)
// Conversion time Tconv = sampling_time + 11Tadcclk
// - Rule conversion group: conversion order of the channels is set in the ADC_RSQRx register (up to 16 conversions).
// - Injection conversion group: conversion order is set in the ADC_ISQR register (up to 4 conversions).

#if USE_ADC		// 1=use ADC peripheral

#ifndef _SDK_ADC_H
#define _SDK_ADC_H

#ifdef __cplusplus
extern "C" {
#endif

// ADC clock divider: 1-16 (default 1)
#ifndef ADCCLK_DIV
#define ADCCLK_DIV	8		// max. 8 MHz (48/8 = 6 MHz)
#endif

// ADC max. value
#define ADC_MAXVAL	0xfff		// = 4095

// ADC registers
typedef struct {
	io32	STATR;		// 0x00: status register
	io32	CTLR1;		// 0x04: control register 1
	io32	CTLR2;		// 0x08: control register 2
	io32	SAMPTR1;	// 0x0C: sample time register 1
	io32	SAMPTR2;	// 0x10: sample time register 2
	io32	IOFR1;		// 0x14: inject channel data offset register 1
	io32	IOFR2;		// 0x18: inject channel data offset register 2
	io32	IOFR3;		// 0x1C: inject channel data offset register 3
	io32	IOFR4;		// 0x20: inject channel data offset register 4
	io32	WDHTR;		// 0x24: watchdog high threshold register
	io32	WDLTR;		// 0x28: watchdog low threshold register
	io32	RSQR1;		// 0x2C: regular sequence register 1
	io32	RSQR2;		// 0x30: regular sequence register 2
	io32	RSQR3;		// 0x34: regular sequence register 3
	io32	ISQR;		// 0x38: injected sequence register
	io32	IDATAR1;	// 0x3C: injected data register 1
	io32	IDATAR2;	// 0x40: injected data register 2
	io32	IDATAR3;	// 0x44: injected data register 3
	io32	IDATAR4;	// 0x48: injected data register 4
	io32	RDATAR;		// 0x4C: regular data register
	io32	DLYR;		// 0x50: delayed data register
} ADC_t;
STATIC_ASSERT(sizeof(ADC_t) == 0x54, "Incorrect ADC_t!");
#define ADC1	((ADC_t*)ADC1_BASE)	// 0x40012400

// ADC calibration voltage selection
#define ADC_CAL_24	1	// calibration voltage 2/4 AVDD
#define ADC_CAL_34	2	// calibration voltage 3/4 AVDD

// external trigger event selection for initiating injection channel conversion
#define ADC_JEXT_T1_CC3		0	// CC3 event of timer 1
#define ADC_JEXT_T1_CC4		1	// CC4 event of timer 1
#define ADC_JEXT_T2_CC3		2	// CC3 event of timer 2
#define ADC_JEXT_T2_CC4		3	// CC4 event of timer 2
#define ADC_JEXT_PD1_PA2	6	// PD1/PA2
#define ADC_JEXT_JSWSTART	7	// JSWSTART software trigger

// external trigger event selection for initiating rule channel conversion
#define ADC_EXT_T1_TRGO		0	// TRGO event of timer 1
#define ADC_EXT_T1_CC1		1	// CC1 event of timer 1
#define ADC_EXT_T1_CC2		2	// CC2 event of timer 1
#define ADC_EXT_T2_TRGO		3	// TRGO event of timer 2
#define ADC_EXT_T2_CC1		4	// CC1 event of timer 2
#define ADC_EXT_T2_CC2		5	// CC2 event of timer 2
#define ADC_EXT_PD3_PC2		6	// PD3/PC2
#define ADC_EXT_SWSTART		7	// SWSTART software trigger

// === ADC status

// Check/Clear analog watchdog event (register STATR.AWD)
INLINE Bool ADCx_AWDGet(ADC_t* adc) { return (adc->STATR & B0) != 0; }
INLINE Bool ADC1_AWDGet(void) { return ADCx_AWDGet(ADC1); }

INLINE void ADCx_AWDClr(ADC_t* adc) { adc->STATR &= ~B0; }
INLINE void ADC1_AWDClr(void) { ADCx_AWDClr(ADC1); }

// Check/Clear end of conversion (register STATR.EOC)
INLINE Bool ADCx_EndGet(ADC_t* adc) { return (adc->STATR & B1) != 0; }
INLINE Bool ADC1_EndGet(void) { return ADCx_EndGet(ADC1); }

INLINE void ADCx_EndClr(ADC_t* adc) { adc->STATR &= ~B1; }
INLINE void ADC1_EndClr(void) { ADCx_EndClr(ADC1); }

// Check/Clear end of conversion of injection group (register STATR.JEOC)
INLINE Bool ADCx_JEndGet(ADC_t* adc) { return (adc->STATR & B2) != 0; }
INLINE Bool ADC1_JEndGet(void) { return ADCx_JEndGet(ADC1); }

INLINE void ADCx_JEndClr(ADC_t* adc) { adc->STATR &= ~B2; }
INLINE void ADC1_JEndClr(void) { ADCx_JEndClr(ADC1); }

// Check/Clear start of conversion of injection group (register STATR.JSTRT)
INLINE Bool ADCx_JStartGet(ADC_t* adc) { return (adc->STATR & B3) != 0; }
INLINE Bool ADC1_JStartGet(void) { return ADCx_JStartGet(ADC1); }

INLINE void ADCx_JStartClr(ADC_t* adc) { adc->STATR &= ~B3; }
INLINE void ADC1_JStartClr(void) { ADCx_JStartClr(ADC1); }

// Check/Clear start of conversion of rule group (register STATR.STRT)
INLINE Bool ADCx_StartGet(ADC_t* adc) { return (adc->STATR & B4) != 0; }
INLINE Bool ADC1_StartGet(void) { return ADCx_StartGet(ADC1); }

INLINE void ADCx_StartClr(ADC_t* adc) { adc->STATR &= ~B4; }
INLINE void ADC1_StartClr(void) { ADCx_StartClr(ADC1); }

// === ADC setup

// Select analog watchdog channel 0..9 (default 0; register CTLR1.AWDCH[4:0])
// - Single channel mode must be selected with ADCx_AWDSingle().
INLINE void ADCx_AWDChan(ADC_t* adc, int ch) { adc->CTLR1 = (adc->CTLR1 & ~0x0f) | ch; }
INLINE void ADC1_AWDChan(int ch) { ADCx_AWDChan(ADC1, ch); }

// Enable/Disable scan mode - conversion of all selected channels (default disabled; register CTLR1.SCAN)
INLINE void ADCx_ScanEnable(ADC_t* adc) { adc->CTLR1 |= B8; }
INLINE void ADC1_ScanEnable(void) { ADCx_ScanEnable(ADC1); }

INLINE void ADCx_ScanDisable(ADC_t* adc) { adc->CTLR1 &= ~B8; }
INLINE void ADC1_ScanDisable(void) { ADCx_ScanDisable(ADC1); }

// Select analog watchdog in scan mode to single channel ADCx_AWDChan() or all channels (default all channels; register CTLR1.AWDSGL)
INLINE void ADCx_AWDSingle(ADC_t* adc) { adc->CTLR1 |= B9; }
INLINE void ADC1_AWDSingle(void) { ADCx_AWDSingle(ADC1); }

INLINE void ADCx_AWDAll(ADC_t* adc) { adc->CTLR1 &= ~B9; }
INLINE void ADC1_AWDAll(void) { ADCx_AWDAll(ADC1); }

// Enable/Disable automatic injection switching after rule channel completed (default disabled; register CTLR1.JAUTO)
INLINE void ADCx_JAutoEnable(ADC_t* adc) { adc->CTLR1 |= B10; }
INLINE void ADC1_JAutoEnable(void) { ADCx_JAutoEnable(ADC1); }

INLINE void ADCx_JAutoDisable(ADC_t* adc) { adc->CTLR1 &= ~B10; }
INLINE void ADC1_JAutoDisable(void) { ADCx_JAutoDisable(ADC1); }

// Enable/Disable intermittent mode on rule channel (default disabled; register CTLR1.DISCEN)
INLINE void ADCx_IntermEnable(ADC_t* adc) { adc->CTLR1 |= B11; }
INLINE void ADC1_IntermEnable(void) { ADCx_IntermEnable(ADC1); }

INLINE void ADCx_IntermDisable(ADC_t* adc) { adc->CTLR1 &= ~B11; }
INLINE void ADC1_IntermDisable(void) { ADCx_IntermDisable(ADC1); }

// Enable/Disable intermittent mode on injection channel (default disabled; register CTLR1.JDISCEN)
INLINE void ADCx_JIntermEnable(ADC_t* adc) { adc->CTLR1 |= B12; }
INLINE void ADC1_JIntermEnable(void) { ADCx_JIntermEnable(ADC1); }

INLINE void ADCx_JIntermDisable(ADC_t* adc) { adc->CTLR1 &= ~B12; }
INLINE void ADC1_JIntermDisable(void) { ADCx_JIntermDisable(ADC1); }

// Set number of rule channels 1..8 to be converted after exernal triggering in intermittent mode (default 1 channel; register CTLR1.DISCNUM[2:0])
INLINE void ADCx_DiscNum(ADC_t* adc, int num) { adc->CTLR1 = (adc->CTLR1 & ~(7<<13)) | ((num-1)<<13); }
INLINE void ADC1_DiscNum(int num) { ADCx_DiscNum(ADC1, num); }

// Enable/Disable analog watchdog on injection channel (default disable; register CTLR1.JAWDEN)
INLINE void ADCx_JAWDEnable(ADC_t* adc) { adc->CTLR1 |= B22; }
INLINE void ADC1_JAWDEnable(void) { ADCx_JAWDEnable(ADC1); }

INLINE void ADCx_JAWDDisable(ADC_t* adc) { adc->CTLR1 &= ~B22; }
INLINE void ADC1_JAWDDisable(void) { ADCx_JAWDDisable(ADC1); }

// Enable/Disable analog watchdog on rule channel (default disable; register CTLR1.AWDEN)
INLINE void ADCx_AWDEnable(ADC_t* adc) { adc->CTLR1 |= B23; }
INLINE void ADC1_AWDEnable(void) { ADCx_AWDEnable(ADC1); }

INLINE void ADCx_AWDDisable(ADC_t* adc) { adc->CTLR1 &= ~B23; }
INLINE void ADC1_AWDDisable(void) { ADCx_AWDDisable(ADC1); }

// Enable/Disable TKEY module (default disable; register CTLR1.TKENABLE)
//INLINE void ADCx_TKEnable(ADC_t* adc) { adc->CTLR1 |= B24; }
//INLINE void ADC1_TKEnable(void) { ADCx_TKEnable(ADC1); }

//INLINE void ADCx_TKDisable(ADC_t* adc) { adc->CTLR1 &= ~B24; }
//INLINE void ADC1_TKDisable(void) { ADCx_TKDisable(ADC1); }

// Set calibration voltage selection ADC_CAL_* (default 2/4; register CTLR1.CALVOL[1:0])
INLINE void ADCx_CalVol(ADC_t* adc, int calvol) { adc->CTLR1 = (adc->CTLR1 & ~(3<<25)) | (calvol<<25); }
INLINE void ADC1_CalVol(int calvol) { ADCx_CalVol(ADC1, calvol); }

// Select touchkey current to HIGH 35uA or LOW 17.5uA (default HIGH 35uA; register CTLR1.TKITUNE)
//INLINE void ADCx_TKITuneHigh(ADC_t* adc) { adc->CTLR1 &= ~B25; }
//INLINE void ADC1_TKITuneHigh(void) { ADCx_TKITuneHigh(ADC1); }

//INLINE void ADCx_TKITuneLow(ADC_t* adc) { adc->CTLR1 |= B25; }
//INLINE void ADC1_TKITuneLow(void) { ADCx_TKITuneLow(ADC1); }

// Enable/Disable ADC BUF (default disable; register CTLR1.BUFEN)
//INLINE void ADCx_BufEnable(ADC_t* adc) { adc->CTLR1 |= B26; }
//INLINE void ADC1_BufEnable(void) { ADCx_BufEnable(ADC1); }

//INLINE void ADCx_BufDisable(ADC_t* adc) { adc->CTLR1 &= ~B26; }
//INLINE void ADC1_BufDisable(void) { ADCx_BufDisable(ADC1); }

// Enable/Disable ADC (default disable; register CTLR2.ADON)
// - Disable will turn off ADC and enter power-down mode.
// - Enable from disable state will wake up ADC from power-down mode. Delay Tstab is required to stabilize.
// - Enable from enable state will start the conversion - only if no other CTLR2 bit is changed at the same time.
INLINE void ADCx_Enable(ADC_t* adc) { adc->CTLR2 |= B0; }
INLINE void ADC1_Enable(void) { ADCx_Enable(ADC1); }

INLINE void ADCx_Disable(ADC_t* adc) { adc->CTLR2 &= ~B0; }
INLINE void ADC1_Disable(void) { ADCx_Disable(ADC1); }

// Set single or continuous conversion mode (default single; register CTLR2.CONT)
// - In continuous mode, the conversion will continue until switch to single mode.
INLINE void ADCx_Single(ADC_t* adc) { adc->CTLR2 &= ~B1; }
INLINE void ADC1_Single(void) { ADCx_Single(ADC1); }

INLINE void ADCx_Cont(ADC_t* adc) { adc->CTLR2 |= B1; }
INLINE void ADC1_Cont(void) { ADCx_Cont(ADC1); }

// Start/Check calibration (register CTLR2.CAL)
// - Calibration is initiated by software and terminated by hardware.
INLINE void ADCx_CalibStart(ADC_t* adc) { adc->CTLR2 |= B2; }
INLINE void ADC1_CalibStart(void) { ADCx_CalibStart(ADC1); }

INLINE Bool ADCx_CalibBusy(ADC_t* adc) { return (adc->CTLR2 & B2) != 0; }
INLINE Bool ADC1_CalibBusy(void) { return ADCx_CalibBusy(ADC1); }

// Start/Check reset calibration (register CTLR2.RSTCAL)
// - Reset calibration is initiated by software and terminated by hardware.
INLINE void ADCx_RstCalibStart(ADC_t* adc) { adc->CTLR2 |= B3; }
INLINE void ADC1_RstCalibStart(void) { ADCx_RstCalibStart(ADC1); }

INLINE Bool ADCx_RstCalibBusy(ADC_t* adc) { return (adc->CTLR2 & B3) != 0; }
INLINE Bool ADC1_RstCalibBusy(void) { return ADCx_RstCalibBusy(ADC1); }

// Select external trigger event of rule channel conversion to PD3/PC2 or OPA (default PD3/PC2; register CTLR2.TGREGU)
//INLINE void ADCx_TgRegPd3Pc2(ADC_t* adc) { adc->CTLR2 &= ~B4; }
//INLINE void ADC1_TgRegPd3Pc2(void) { ADCx_TgRegPd3Pc2(ADC1); }

//INLINE void ADCx_TgRegOpa(ADC_t* adc) { adc->CTLR2 |= B4; }
//INLINE void ADC1_TgRegOpa(void) { ADCx_TgRegOpa(ADC1); }

// Select external trigger event of injection channel conversion to PD1/PA2 or OPA (default PD1/PA2; register CTLR2.TGINJE)
//INLINE void ADCx_TgInjPd1Pa2(ADC_t* adc) { adc->CTLR2 &= ~B5; }
//INLINE void ADC1_TgInjPd1Pa2(void) { ADCx_TgInjPd1Pa2(ADC1); }

//INLINE void ADCx_TgInjOpa(ADC_t* adc) { adc->CTLR2 |= B5; }
//INLINE void ADC1_TgInjOpa(void) { ADCx_TgInjOpa(ADC1); }

// Enable/Disable DMA mode (register CTLR2.DMA)
INLINE void ADCx_DMAEnable(ADC_t* adc) { adc->CTLR2 |= B8; }
INLINE void ADC1_DMAEnable(void) { ADCx_DMAEnable(ADC1); }

INLINE void ADCx_DMADisable(ADC_t* adc) { adc->CTLR2 &= ~B8; }
INLINE void ADC1_DMADisable(void) { ADCx_DMADisable(ADC1); }

// Set data alignment to left to 16-bits or right (default right-aligned; register CTLR2.ALIGN)
INLINE void ADCx_AlignLeft(ADC_t* adc) { adc->CTLR2 |= B11; }
INLINE void ADC1_AlignLeft(void) { ADCx_AlignLeft(ADC1); }

INLINE void ADCx_AlignRight(ADC_t* adc) { adc->CTLR2 &= ~B11; }
INLINE void ADC1_AlignRight(void) { ADCx_AlignRight(ADC1); }

// Select external trigger event for initiating injection channel conversion ADC_JEXT_* (default CC3 of timer 1; register CTLR2.JEXTSEL[2:0])
INLINE void ADCx_JExtSel(ADC_t* adc, int ext) { adc->CTLR2 = (adc->CTLR2 & ~(7 << 12)) | (ext << 12); }
INLINE void ADC1_JExtSel(int ext) { ADCx_JExtSel(ADC1, ext); }

// Enable/Disable externally triggered conversion for injected channels (register CTLR2.JEXTTRIG)
INLINE void ADCx_JExtTrigEnable(ADC_t* adc) { adc->CTLR2 |= B15; }
INLINE void ADC1_JExtTrigEnable(void) { ADCx_JExtTrigEnable(ADC1); }

INLINE void ADCx_JExtTrigDisable(ADC_t* adc) { adc->CTLR2 &= ~B15; }
INLINE void ADC1_JExtTrigDisable(void) { ADCx_JExtTrigDisable(ADC1); }

// Select external trigger event for initiating rule channel conversion ADC_EXT_* (default TRGO of timer 1; register CTLR2.EXTSEL[2:0])
INLINE void ADCx_ExtSel(ADC_t* adc, int ext) { adc->CTLR2 = (adc->CTLR2 & ~(7 << 17)) | (ext << 17); }
INLINE void ADC1_ExtSel(int ext) { ADCx_ExtSel(ADC1, ext); }

// Enable/Disable externally triggered conversion for rule channels (default disable; register CTLR2.EXTTRIG)
INLINE void ADCx_ExtTrigEnable(ADC_t* adc) { adc->CTLR2 |= B20; }
INLINE void ADC1_ExtTrigEnable(void) { ADCx_ExtTrigEnable(ADC1); }

INLINE void ADCx_ExtTrigDisable(ADC_t* adc) { adc->CTLR2 &= ~B20; }
INLINE void ADC1_ExtTrigDisable(void) { ADCx_ExtTrigDisable(ADC1); }

// Software start injection channel transition (register CTLR2.JSWSTART)
INLINE void ADCx_JSwStart(ADC_t* adc) { adc->CTLR2 |= B21; }
INLINE void ADC1_JSwStart(void) { ADCx_JSwStart(ADC1); }

// Software start rule channel transition (register CTLR2.SWSTART)
INLINE void ADCx_SwStart(ADC_t* adc) { adc->CTLR2 |= B22; }
INLINE void ADC1_SwStart(void) { ADCx_SwStart(ADC1); }

// Set sampling time 0..7 for channel 0-9 (default 0 = 3.5 cycles; register SAMPTR2)
//  0 ... 3 cycles
//  1 ... 9 cycles
//  2 ... 15 cycles
//  3 ... 30 cycles
//  4 ... 43 cycles
//  5 ... 57 cycles
//  6 ... 73 cycles
//  7 ... 241 cycles
INLINE void ADCx_SampTime(ADC_t* adc, int chan, int samp) { chan *= 3; adc->SAMPTR2 = (adc->SAMPTR2 & ~(7 << chan)) | (samp << chan); }
INLINE void ADC1_SampTime(int chan, int samp) { ADCx_SampTime(ADC1, chan, samp); }

// Set 10-bit data offset of injected channel 1/2/3/4 (default 0; register IOFR1/IOFR2/IOFR3/IOFR4)
INLINE void ADCx_JOff1(ADC_t* adc, int off) { adc->IOFR1 = off; }
INLINE void ADCx_JOff2(ADC_t* adc, int off) { adc->IOFR2 = off; }
INLINE void ADCx_JOff3(ADC_t* adc, int off) { adc->IOFR3 = off; }
INLINE void ADCx_JOff4(ADC_t* adc, int off) { adc->IOFR4 = off; }
INLINE void ADCx_JOff(ADC_t* adc, int ch, int off) { (&adc->IOFR1)[ch-1] = off; }
INLINE void ADC1_JOff1(int off) { ADCx_JOff1(ADC1, off); }
INLINE void ADC1_JOff2(int off) { ADCx_JOff2(ADC1, off); }
INLINE void ADC1_JOff3(int off) { ADCx_JOff3(ADC1, off); }
INLINE void ADC1_JOff4(int off) { ADCx_JOff4(ADC1, off); }
INLINE void ADC1_JOff(int ch, int off) { ADCx_JOff(ADC1, ch, off); }

// Set 10-bit watchdog 0 high threshold (default 0x3ff; register WDHTR)
INLINE void ADCx_WDH(ADC_t* adc, int high) { adc->WDHTR = high; }
INLINE void ADC1_WDH(int high) { ADCx_WDH(ADC1, high); }

// Set 12-bit watchdog 0 low threshold (default 0; register WDLTR)
INLINE void ADCx_WDL(ADC_t* adc, int low) { adc->WDLTR = low; }
INLINE void ADC1_WDL(int low) { ADCx_WDL(ADC1, low); }

// Set analog watchdog 1..3 threshold low and high, 12-bit values (default 0x000 and 0xFFF; register WDTR1/WDTR2)
//INLINE void ADCx_WD1(ADC_t* adc, int low, int high) { adc->WDTR1 = low | (high << 16); }
//INLINE void ADCx_WD2(ADC_t* adc, int low, int high) { adc->WDTR2 = low | (high << 16); }

//INLINE void ADC1_WD1(int low, int high) { ADCx_WD1(ADC1, low, high); }
//INLINE void ADC1_WD2(int low, int high) { ADCx_WD2(ADC1, low, high); }

// Set number of channels to be converted in a regular channel conversion sequence, set 1..16 (default 1; register RSQR1.L[3:0])
INLINE void ADCx_RNum(ADC_t* adc, int num) { adc->RSQR1 = (adc->RSQR1 & ~(0x0f << 20)) | ((num-1) << 20); }
INLINE void ADC1_RNum(int num) { ADCx_RNum(ADC1, num); }

// Select ADC channel chan=0..9 to be converted on the rule sequence seq=1..16 (default 0; register RSQR1/RSQR2/RSQR3)
// - If the number of rule conversions is less than 16, the sequence order of
//   conversion starts from seq=1, in direction to higher sequence number.
void ADCx_RSeq(ADC_t* adc, int seq, int chan);
INLINE void ADC1_RSeq(int seq, int chan) { ADCx_RSeq(ADC1, seq, chan); }

// Set number of channels to be converted in a inject channel conversion sequence, set 1..4 (default 1; register ISQR.JL[1:0])
INLINE void ADCx_JNum(ADC_t* adc, int num) { adc->ISQR = (adc->ISQR & ~(0x03 << 20)) | ((num-1) << 20); }
INLINE void ADC1_JNum(int num) { ADCx_JNum(ADC1, num); }

// Select ADC channel chan=0..9 to be converted on the injected sequence seq=1..4 (default 0; register ISQR)
// - Unlike the regular conversion sequence, if the number of injected conversions is less than 4,
//   the sequence order of conversion starts from seq=4, in direction to lower sequence number.
INLINE void ADCx_JSeq(ADC_t* adc, int seq, int chan)
{
	seq = (seq - 1) * 5;
	adc->ISQR = (adc->ISQR & ~(0x1f << seq)) | (chan << seq);
}
INLINE void ADC1_JSeq(int seq, int chan) { ADCx_JSeq(ADC1, seq, chan); }

// Set ADC frequency division 1-16 (default 1; register CTLR3.CLK_DIV[3:0])
//INLINE void ADCx_ClkDiv(ADC_t* adc, int div) { adc->CTLR3 = (adc->CTLR3 & ~0x0f) | (div-1); }
//INLINE void ADC1_ClkDiv(int div) { ADCx_ClkDiv(ADC1, div); }

// Select high power mode (> 1M sampling rate) or low power mode (< 1M sampling rate) (default low power mode; register CTLR3.ADC_LP)
//INLINE void ADCx_HP(ADC_t* adc) { adc->CTLR3 &= ~B0; }
//INLINE void ADC1_HP(void) { ADCx_HP(ADC1); }

//INLINE void ADCx_LP(ADC_t* adc) { adc->CTLR3 |= B0; }
//INLINE void ADC1_LP(void) { ADCx_HP(ADC1); }

// Select ADC duty cycle to delay or RCC (default RCC; register CTLR3.DUTYEN)
//INLINE void ADCx_DutyDelay(ADC_t* adc) { adc->CTLR3 |= B1; }
//INLINE void ADC1_DutyDelay(void) { ADCx_DutyDelay(ADC1); }

//INLINE void ADCx_DutyRCC(ADC_t* adc) { adc->CTLR3 &= ~B1; }
//INLINE void ADC1_DutyRCC(void) { ADCx_DutyRCC(ADC1); }

// Enable/Disable touchkey multi-mask (default disable; register CTLR3.DRVEN)
//INLINE void ADCx_TkDrvEnable(ADC_t* adc) { adc->CTLR3 |= B2; }
//INLINE void ADC1_TkDrvEnable(void) { ADCx_TkDrvEnable(ADC1); }

//INLINE void ADCx_TkDrvDisable(ADC_t* adc) { adc->CTLR3 &= ~B2; }
//INLINE void ADC1_TkDrvDisable(void) { ADCx_TkDrvDisable(ADC1); }

// Enable/Disable analog watchdog scanning (default disable; register CTLR3.AWD_SCAN)
//INLINE void ADCx_AwdScanEnable(ADC_t* adc) { adc->CTLR3 |= B3; }
//INLINE void ADC1_AwdScanEnable(void) { ADCx_AwdScanEnable(ADC1); }

//INLINE void ADCx_AwdScanDisable(ADC_t* adc) { adc->CTLR3 &= ~B3; }
//INLINE void ADC1_AwdScanDisable(void) { ADCx_AwdScanDisable(ADC1); }

// Enable/Disable watchdog inx=0..2 output reset (default disable; register CTLR3.AWDx_RST_EN)
//INLINE void ADCx_AwdRstEnable(ADC_t* adc, int inx) { adc->CTLR3 |= BIT(inx+4); }
//INLINE void ADC1_AwdRstEnable(int inx) { ADCx_AwdRstEnable(ADC1, inx); }

//INLINE void ADCx_AwdRstDisable(ADC_t* adc, int inx) { adc->CTLR3 &= ~BIT(inx+4); }
//INLINE void ADC1_AwdRstDisable(int inx) { ADCx_AwdRstDisable(ADC1, inx); }

// Check/clear analog watchdog inx=0..2 comparison result - value is out of threshold values (register CTLR3.AWDx_RES)
//INLINE Bool ADCx_AwdRes(ADC_t* adc, int inx) { return (adc->CTLR3 & BIT(inx + 8)) != 0; }
//INLINE Bool ADC1_AwdRes(int inx) { return ADCx_AwdRes(ADC1, inx); }

//INLINE void ADCx_AwdResClr(ADC_t* adc, int inx) { adc->CTLR3 &= ~BIT(inx + 8); }
//INLINE void ADC1_AwdResClr(int inx) { ADCx_AwdResClr(ADC1, inx); }

// Enable/Disable touchkey multi-mask channel 0..7 (default disable; register CTLR3.DRV_OUTEN)
//INLINE void ADCx_TkOutEnable(ADC_t* adc, int inx) { adc->CTLR3 |= BIT(inx+16); }
//INLINE void ADC1_TkOutEnable(int inx) { ADCx_TkOutEnable(ADC1, inx); }

//INLINE void ADCx_TkOutDisable(ADC_t* adc, int inx) { adc->CTLR3 &= ~BIT(inx+16); }
//INLINE void ADC1_TkOutDisable(int inx) { ADCx_TkOutDisable(ADC1, inx); }

// set external trigger delay data in ADC clock cycles 0..511, select rule channel (default 0; register ADC_DLYR)
INLINE void ADCx_Dly(ADC_t* adc, int val) { adc->DLYR = val; }
INLINE void ADC1_Dly(int val) { ADCx_Dly(ADC1, val); }

// set external trigger delay data in ADC clock cycles 0..511, select injection channel (default 0; register ADC_DLYR)
INLINE void ADCx_DlyJ(ADC_t* adc, int val) { adc->DLYR = val | B9; }
INLINE void ADC1_DlyJ(int val) { ADCx_DlyJ(ADC1, val); }

// === Interrupt

// Enable/Disable interrupt on end of conversion (rule or injection; default disabled; register CTLR1.EOCIE)
INLINE void ADCx_EndIntEnable(ADC_t* adc) { adc->CTLR1 |= B5; }
INLINE void ADC1_EndIntEnable(void) { ADCx_EndIntEnable(ADC1); }

INLINE void ADCx_EndIntDisable(ADC_t* adc) { adc->CTLR1 &= ~B5; }
INLINE void ADC1_EndIntDisable(void) { ADCx_EndIntDisable(ADC1); }

// Enable/Disable analog watchdog interrupt (default disabled; register CTLR1.AWDIE)
INLINE void ADCx_AWDIntEnable(ADC_t* adc) { adc->CTLR1 |= B6; }
INLINE void ADC1_AWDIntEnable(void) { ADCx_AWDIntEnable(ADC1); }

INLINE void ADCx_AWDIntDisable(ADC_t* adc) { adc->CTLR1 &= ~B6; }
INLINE void ADC1_AWDIntDisable(void) { ADCx_AWDIntDisable(ADC1); }

// Enable/Disable interrupt on end of conversion of injection group (default disabled; register CTLR1.JEOCIE)
INLINE void ADCx_JEndIntEnable(ADC_t* adc) { adc->CTLR1 |= B7; }
INLINE void ADC1_JEndIntEnable(void) { ADCx_JEndIntEnable(ADC1); }

INLINE void ADCx_JEndIntDisable(ADC_t* adc) { adc->CTLR1 &= ~B7; }
INLINE void ADC1_JEndIntDisable(void) { ADCx_JEndIntDisable(ADC1); }

// === Data

// Get result of injection conversion channel 1..4, data left-aligned to 16-bit or right-aligned (register IDATAR1/IDATAR2/IDATAR3/IDATAR4)
INLINE u16 ADCx_IData1(ADC_t* adc) { return (u16)adc->IDATAR1; }
INLINE u16 ADCx_IData2(ADC_t* adc) { return (u16)adc->IDATAR2; }
INLINE u16 ADCx_IData3(ADC_t* adc) { return (u16)adc->IDATAR3; }
INLINE u16 ADCx_IData4(ADC_t* adc) { return (u16)adc->IDATAR4; }
INLINE u16 ADCx_IData(ADC_t* adc, int ch) { return (u16)(&adc->IDATAR1)[ch-1]; }
INLINE u16 ADC1_IData1() { return ADCx_IData1(ADC1); }
INLINE u16 ADC1_IData2() { return ADCx_IData2(ADC1); }
INLINE u16 ADC1_IData3() { return ADCx_IData3(ADC1); }
INLINE u16 ADC1_IData4() { return ADCx_IData4(ADC1); }
INLINE u16 ADC1_IData(int ch) { return (u16)ADCx_IData(ADC1, ch); }

// Get result of regular conversion, data left-aligned to 16-bit or right-aligned (register RDATAR)
INLINE u16 ADCx_Data(ADC_t* adc) { return (u16)adc->RDATAR; }
INLINE u16 ADC1_Data() { return ADCx_Data(ADC1); }

// Initialize ADC single conversion mode
// - Sampling time is not set, you can use ADCx_SampTime() to set it.
// - Get conversion result with ADCx_GetSingle().
void ADCx_InitSingle(ADC_t* adc);
INLINE void ADC1_InitSingle(void) { ADCx_InitSingle(ADC1); }

// Get single conversion (chan = channel 0..9)
// - Conversion must be initialized using ADCx_InitSingle().
// - Before use, set the appropriate GPIO pin to analog input mode GPIO_MODE_AIN.
u16 ADCx_GetSingle(ADC_t* adc, int chan);
INLINE u16 ADC1_GetSingle(int chan) { return ADCx_GetSingle(ADC1, chan); }

// Get sum of multiple single conversions (chan = channel 0..9, num = number of samples)
// - Conversion must be initialized using ADCx_InitSingle().
// - Before use, set the appropriate GPIO pin to analog input mode GPIO_MODE_AIN.
int ADCx_GetSingleMul(ADC_t* adc, int chan, int num);
INLINE int ADC1_GetSingleMul(int chan, int num) { return ADCx_GetSingleMul(ADC1, chan, num); }

#ifdef __cplusplus
}
#endif

#endif // _SDK_ADC_H

#endif // USE_ADC
