
// ****************************************************************************
//
//                               Power Control
//
// ****************************************************************************

#include "../../includes.h"	// globals

#if USE_PWR		// 1=use power control

// Enter sleep mode (use_wfi: True=use WFI wakeup, False=use WFE wakeup)
void PWR_EnterSleep(Bool use_wfi)
{
	// select Sleep mode
	PWR_PDDSSleep();

	// set Sleep mode
	NVIC_Sleep();

	// wait
	if (use_wfi)
		wfi_ins();
	else
		wfe();
}

// Enter standby mode (use_wfi: True=use WFI wakeup, False=use WFE wakeup)
void PWR_EnterStandby(Bool use_wfi)
{
	// select Standby mode
	PWR_PDDSStandby();

	// set DeepSleep mode
	NVIC_DeepSleep();

	// wait
	if (use_wfi)
		wfi_ins();
	else
		wfe();

	// return to normal mode
	NVIC_Sleep();
}

#endif // USE_PWR
