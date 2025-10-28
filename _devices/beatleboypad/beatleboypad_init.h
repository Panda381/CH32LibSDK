
// ****************************************************************************
//
//                        BeatleBoyPad - Device init
//
// ****************************************************************************

#ifndef _DEVINIT_H
#define _DEVINIT_H

#ifdef __cplusplus
extern "C" {
#endif

// device run mode
extern u8 RunMode;		// device run mode RUNMODE_* (0=OLED, 1=VGA)

// ADC measure
extern u8 Pad1AdcChan;		// PAD1 ADC channel (OLED: 6 from PD6, VGA: 5 from PD5)
extern volatile u8 SupplyVoltageCnt;	// counter of samples of supply voltage
extern volatile u8 KeyPressOld;		// previous state of presseed keys
extern volatile u8 KeyPressMap;		// currently pressed keys
extern volatile u16 PadCnt;		// PAD measure sample counter
extern volatile u32 SupplyVoltageAcc;	// supply voltage accumulator
extern volatile u32 SupplyVoltageVal;	// supply voltage value (voltage in [mV] = (1200 << (12 + SUPPLYADC_SHIFT)) / SupplyVoltage)
extern volatile u32 Pad1Acc;		// PAD1 voltage accumulator
extern volatile u32 Pad1Val;		// PAD1 value (value size PADADC_SHIFT+12 bits)
extern volatile u32 Pad2Acc;		// PAD2 voltage accumulator
extern volatile u32 Pad2Val;		// PAD2 value (value size PADADC_SHIFT+12 bits)

// ADC PAD thresholds
extern u32 PadThreshold[7];

// Get supply voltage in [mV]
int GetSupply(void);

// Initialize device
void DevInit(void);

// Terminate device
void DevTerm(void);

#ifdef __cplusplus
}
#endif

#endif // _DEVINIT_H
